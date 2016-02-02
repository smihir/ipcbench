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

#define BACKLOG 50

#define die(msg)     \
    do {             \
        char str[100]; \
        snprintf(str, 100, "%s(%d): %s", __func__, __LINE__, msg); \
        perror(str); \
        exit(1);     \
    } while(0)       \

void parent(int port) {
    int fd, confd, flag = 1;
    struct sockaddr_in my;
    struct sockaddr_storage their;
    socklen_t sz = sizeof(their);
    int pid = -1;
    char buffer[100] = {'\0'};
    int len = 100;

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

    recv(confd, buffer, len, 0);
    printf("%s", buffer);
    close(fd);
    close(confd);
    pid = -1;
    wait(&pid);
}

void child(int port) {
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET_ADDRSTRLEN];
    int socketfd;
    int flag;
    char s_port[10];
    char *buffer = "lilili\n";

    snprintf(s_port, sizeof(s_port), "%d", port);
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    printf("port is %s\n", s_port);

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

        // convert the IP to a string and print it:
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf("Will connect to: %s\n", ipstr);
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
    send(socketfd, (void *)buffer, strlen(buffer), 0);
}

int main(int argc, char **argv) {
    int pid;

    pid = fork();
    if (pid == -1) {
        die("Unable to fork");
    } else if (pid == 0) {
        // In parent, do parent related stuff
        parent(15000);
    } else {
        // In child process

        sleep(2);
        child(15000);
    }

    return 0;
}
