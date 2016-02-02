#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define die(msg)     \
    do {             \
        char str[100]; \
        snprintf(str, 100, "%s(%d): %s", __func__, __LINE__, msg); \
        perror(str); \
        exit(1);     \
    } while(0)       \

void parent(int *fd, int *fd1, int size, int tput) {
    int info;
    ssize_t r = 0, ret;
    char *buffer = calloc(sizeof(char), size);

    if (buffer == NULL) {
        die("cannot alloc memory for rx");
    }

    if (tput == 0) {
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
    wait(&info);
    free(buffer);
}

void child(int *fd, int *fd1, int size, int tput) {
    ssize_t r = 0, ret;
    char *buffer = calloc(sizeof(char), size);

    if (buffer == NULL) {
        die("cannot alloc memory for tx");
    }

    if (tput == 0) {
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

    printf("running pipe ipc for bufsize = %lu, tput = %d\n", size, tput);

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
