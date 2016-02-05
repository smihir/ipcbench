#define _GNU_SOURCE
#include <sched.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "hwtimer.h"

#define LATENCY_RUNS 100
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

void parent(int *fd, int *fd1, int size, int tput) {
    int info;
    char *buffer = calloc(sizeof(char), size);

    if (buffer == NULL) {
        die("cannot alloc memory for rx");
    }

    set_affinity(0);

    if (tput == 0) {
        int i;
        for (i = 0; i < LATENCY_RUNS; i++) {
            ssize_t r = 0, ret;
            while ((ret = read(fd[0], buffer, size)) > 0) {
                r += ret;
                if (r == size) {
                    write(fd1[1], (void *)buffer, size);
                    break;
                }
            }

            if (ret == -1)
                perror("Error in receiving packets");
        }
    } else {
        // TPUT test, we will receive atleast a 100MB of data
        int num_pkts = (100 * 1024 * 1024) / size;
        // avoid errors due to remainder
        ssize_t tot_size = num_pkts * size;
        ssize_t r = 0, ret;

        // naive receive...
        while ((ret = read(fd[0], buffer, size)) > 0) {
            r += ret;
            if (r == tot_size) {
                write(fd1[1], (void *)buffer, 1);
                break;
            }
        }

        if (ret == -1) {
            die("Error in receiving packets");
        }
    }
    wait(&info);
    free(buffer);
}

void child(int *fd, int *fd1, int size, int tput) {
    char *buffer = calloc(sizeof(char), size);

    if (buffer == NULL) {
        die("cannot alloc memory for tx");
    }

    set_affinity(1);

    if (tput == 0) {
        int i;
        hwtimer_t tsc_t;
        uint64_t ns_time[LATENCY_RUNS];
        for (i = 0; i < LATENCY_RUNS; i++) {
            ssize_t r = 0, ret;
            init_timer(&tsc_t);
            start_timer(&tsc_t);
            if (write(fd[1], (void *)buffer, size) == -1) {
                die("child: write error");
            }

            // Do a round trip
            while ((ret = read(fd1[0], buffer, size)) > 0) {
                r += ret;
                if (r == size) {
                    break;
                }
            }
            stop_timer(&tsc_t);
            ns_time[i]=get_timer_ns(&tsc_t)/2;
        }
        for (i = 0; i<LATENCY_RUNS;i++){
            printf("%lu", ns_time[i]);
            if(i!=LATENCY_RUNS-1){
                printf("\n");
            }
        }
    } else {
        // TPUT test, send atleast a 100MB of data
        int num_pkts = (100 * 1024 * 1024) / size;
        ssize_t tot_size = num_pkts * size;
        int i = 0;
        ssize_t ret;
        hwtimer_t tsc_t;
        uint64_t ns_time;
        init_timer(&tsc_t);
        start_timer(&tsc_t);
         for (i = 0; i < num_pkts; i++) {
            if (write(fd[1], (void *)buffer, size) == -1) {
                die("Send error in child");
            }
        }

        // receive ack
        if ((ret = read(fd1[0], buffer, size)) > 0) {
            // calculate timings
        }
        stop_timer(&tsc_t);
        ns_time=get_timer_ns(&tsc_t);
        printf("%f \n", (1000)*((float)tot_size/ns_time));
        if (ret == -1) {
            die("Child: Error in receiving ack");
        }
    }
    free(buffer);
}

int main(int argc, char **argv) {
    int pid;
    int ch;
    int tput = 0;
    unsigned long int size = 4;
    int fd[2], fd1[2];

    while ((ch = getopt(argc, argv, "p:s:t")) != -1) {
        switch (ch) {
            case 't':
                tput = 1;
                break;
            case 's':
                size = strtoul(optarg, NULL, 10);
                break;
            case '?':
            default:
                die("Not enough arguments");
        }
    }

    if (pipe(fd) == -1 || pipe(fd1) == -1)
        die("pipe");

    //printf("running pipe ipc for bufsize = %lu, tput = %d\n", size, tput);

    pid = fork();
    if (pid == -1) {
        die("Unable to fork");
    } else if (pid != 0) {
        // In parent, do parent related stuff
        parent(fd, fd1, size, tput);
    } else {
        // In child process
        child(fd, fd1, size, tput);
    }

    return 0;
}
