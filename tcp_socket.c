#define _GNU_SOURCE
#include <sched.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "hwtimer.h"

#define BACKLOG 50
#define DEFAULT_PORT 9000
#define LATENCY_RUNS 10

#define die(msg)     \
    do {             \
        char str[100]; \
        snprintf(str, 100, "%s(%d): %s", __func__, __LINE__, msg); \
        perror(str); \
        exit(1);     \
    } while(0)       \

void set_affinity(int cpuid) {
    cpu_set_t set;

    CPU_ZERO(&set);
    CPU_SET(cpuid, &set);

    if (sched_setaffinity(getpid(), sizeof(set), &set) == -1)
        perror("sched_affinity");
}

void parent(int port, unsigned long int bufsize, int tput) {
    int fd, confd, flag = 1;
    struct sockaddr_in my;
    struct sockaddr_storage their;
    socklen_t sz = sizeof(their);
    int info;
    char *buffer = calloc(sizeof(char), bufsize);
    if (buffer == NULL) {
        die("cannot alloc memory for rx");
    }

    set_affinity(0);

    fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        die("Socket open failed");
    }

    // So that we dont have to wait for around 1min for OS
    // to recycle the socket
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&flag,
                    sizeof(int)) == -1) {
        close(fd);
        die("Unable to set REUSEADDR");
    } 

    my.sin_addr.s_addr = INADDR_ANY;
    my.sin_family = AF_INET;
    my.sin_port = htons(port);
    if (bind(fd, (struct sockaddr *)&my, sizeof(my)) != 0) {
        close(fd);
        die("Socket bind failed");
    }

    // We want the packet to be sent immediately, disable Nagle
    if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char *)&flag,
                         sizeof(int)) == -1) {
        close(fd);
        die("Cannot disable Nagle");
    }

    if (listen(fd, BACKLOG) == -1) {
        close(fd);
        die("Cannot listen");
    }

    confd = accept(fd, (struct sockaddr *)&their, &sz);

    if (confd == -1) {
        close(fd);
        die("cannot accept connection");
    }

    if (setsockopt(confd, IPPROTO_TCP, TCP_NODELAY, (char *)&flag,
                        sizeof(int)) == -1) {
        close(fd);
        close(confd);
        die("Cannot disable Nagle!");
    }

    if (tput == 0) {
        int i;

        for (i = 0; i < LATENCY_RUNS; i++) {
            ssize_t r = 0, ret;
            // maybe do buffer + r and bufsize -r here...
            while ((ret = recv(confd, buffer, bufsize, 0)) > 0) {
                r += ret;
                if (r == bufsize) {
                    send(confd, (void *)buffer, bufsize, 0);
                    break;
                }
            }

            if (ret == -1) {
                perror("Error in receiving packets");
            } else if (ret == 0) {
                printf("Remote connection closed\n");
            }
        }
    } else {
        // TPUT test, we will receive atleast a 100MB of data
        int num_pkts = (100 * 1024 * 1024) / bufsize;
        // avoid errors due to remainder
        int tot_size = num_pkts * bufsize;
        ssize_t r = 0, ret;

        // naive receive...
        while ((ret = recv(confd, buffer, bufsize, 0)) > 0) {
            r += ret;
            if (r == tot_size) {
                send(confd, (void *)buffer, 1, 0);
                break;
            }
        }

        if (ret == -1) {
            perror("Error in receiving packets");
        } else if (ret == 0) {
            printf("Remote connection closed\n");
        }
    }

    wait(&info);
    close(fd);
    close(confd);
}

void child(int port, unsigned long int bufsize, int tput) {
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET_ADDRSTRLEN];
    int socketfd;
    int flag;
    char s_port[10];
    char *buffer = calloc(sizeof(char), bufsize);

    if (buffer == NULL) {
        die("cannot alloc memory for tx");
    }

    set_affinity(1);

    snprintf(s_port, sizeof(s_port), "%d", port);
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo("localhost", s_port, &hints, &res)) != 0) {
        printf("getaddrinfo: %s\n", gai_strerror(status));
        die("Cannot get remote address info");
    }

    for (p = res; p != NULL; p = p->ai_next) {
        void *addr;

        if (p->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *) p->ai_addr;
            addr = &(ipv4->sin_addr);
        } else {
            // Sorry, no IPV6
            continue;
        }

        // convert the IP to a string and print it if required
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        break;
    }

    socketfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (socketfd < 0) {
        die("Socket open failed");
    }

    int ret = setsockopt(socketfd, IPPROTO_TCP, TCP_NODELAY, (char *)&flag,
                         sizeof(int));
    if (ret < 0) {
        die("Cannot disable Nagle!");
    }

    if (connect(socketfd, p->ai_addr, p->ai_addrlen) == -1) {
        close(socketfd);
        die("client connect");
        return;
    }

    if (tput == 0) {
        int i;
        hwtimer_t tsc_t;
        uint64_t ns_time[LATENCY_RUNS];
        for (i = 0; i < LATENCY_RUNS; i++) {
            ssize_t r = 0, ret;

            init_timer(&tsc_t);
            start_timer(&tsc_t);

            if (send(socketfd, (void *)buffer, bufsize, 0) == -1) {
                perror("Send error in child");
            }

            // Do a round trip
            while ((ret = recv(socketfd, buffer, bufsize, 0)) > 0) {
                r += ret;
                if (r == bufsize)
                    break;
            }
            stop_timer(&tsc_t);
            ns_time[i]=get_timer_ns(&tsc_t)/2;

            if (ret == -1) {
                perror("Child: Error in receiving packets");
            } else if (ret == 0) {
                printf("Child: Remote connection closed\n");
            }
        }
        for (i = 0;i < LATENCY_RUNS; i++) {
            printf("%d %lu \n", i, ns_time[i]);
        }
    } else {
        // TPUT test, send atleast a 100MB of data
        int num_pkts = (100 * 1024 * 1024) / bufsize;
        int i = 0;
        ssize_t ret;
        hwtimer_t tsct;
        uint64_t ns_time;
        init_timer(&tsct);
        start_timer(&tsct);

        for (i = 0; i < num_pkts; i++) {
            if (send(socketfd, (void *)buffer, bufsize, 0) == -1) {
                perror("Send error in child");
                break;
            }
        }

        // receive ack
        if ((ret = recv(socketfd, buffer, bufsize, 0)) > 0) {
            // calculate timings
        }
        stop_timer(&tsct);
        ns_time = get_timer_ns(&tsct);
        printf("%lu \n", ns_time);
        if (ret == -1) {
            perror("Child: Error in receiving packets");
        } else if (ret == 0) {
            printf("Child: Remote connection closed\n");
        }
    }
}

int main(int argc, char **argv) {
    int pid;
    int ch;
    unsigned long int port = DEFAULT_PORT;
    int tput = 0;
    unsigned long int size = 4;

    // make provision to specify the port in case
    // DEFAULT_PORT(9000) does not work
    while ((ch = getopt(argc, argv, "p:s:t")) != -1) {
        switch (ch) {
            case 'p':
                port = strtoul(optarg, NULL, 10);
                if (port <= 1024 || port > 65536) {
                    printf("Invalid Port\n");
                    exit(1);
                }
                break;
            case 't':
                tput = 1;
                break;
            case 's':
                size = strtoul(optarg, NULL, 10);
                break;
            case '?':
            default:
                printf("Not enough arguments\n");
        }
    }

    //printf("Operating on port %lu, size %lu\n", port, size);

    pid = fork();
    if (pid == -1) {
        die("Unable to fork");
    } else if (pid != 0) {
        // In parent, do parent related stuff
        parent(port, size, tput);
    } else {
        // In child process
        // wait for parent to initialize the port
        // sleep(2);

        child(port, size, tput);
    }

    return 0;
}
