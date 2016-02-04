#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <pthread.h>
#include "hwtimer.h"

#define LATENCY_RUNS 10
#define MAX_MEM (512 * 1024)
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

struct shmem_map {
    pthread_mutex_t mutex;
    pthread_cond_t fill;
    pthread_cond_t empty;
    int volatile produced;
    int volatile consumed;
    int volatile count;
    char data[0];
};

void child(struct shmem_map *pmap, struct shmem_map *pmap2, int tput, int size,
           size_t region_size) {
    int max_data = region_size - sizeof(struct shmem_map);
    int max_count = max_data / size;
    char *buffer = calloc(sizeof(char), size);

    if (buffer == NULL) {
        printf("cannot alloc memory for rx\n");
        return;
    }
    set_affinity(0);

    if (tput == 0) {
        int i;
        hwtimer_t tsct;
        uint64_t ns_time[LATENCY_RUNS];
        for (i = 0; i < LATENCY_RUNS; i++) {
            init_timer(&tsct);
            start_timer(&tsct);
            // consume
            pthread_mutex_lock(&pmap->mutex);
            while (pmap->count == 0) {
                pthread_cond_wait(&pmap->fill, &pmap->mutex);
            }

            memcpy(buffer, &pmap->data[0] + (pmap->consumed * size), size);
            pmap->consumed = (pmap->consumed + 1) % max_count;
            pmap->count--;

            pthread_cond_signal(&pmap->empty);
            pthread_mutex_unlock(&pmap->mutex);

            // produce
            pthread_mutex_lock(&pmap2->mutex);
            while (pmap2->count == max_count) {
                pthread_cond_wait(&pmap2->empty, &pmap2->mutex);
            }

            memcpy(&pmap2->data[0] + (pmap2->produced * size), buffer, size);
            pmap2->produced = (pmap2->produced + 1) % max_count;
            pmap2->count++;

            pthread_cond_signal(&pmap2->fill);
            pthread_mutex_unlock(&pmap2->mutex);

            stop_timer(&tsct);
            ns_time[i] = get_timer_ns(&tsct)/2;
        }
        for (i = 0; i<LATENCY_RUNS;i++){
            printf("%lu", ns_time[i]);
            if (i!=LATENCY_RUNS-1){
                printf("\n");
            }
         }
    } else {
        // TPUT test, we will receive atleast a 100MB of data
        int num_pkts = (100 * 1024 * 1024) / size;
        hwtimer_t tsct;
        uint64_t ns_time;
        init_timer(&tsct);
        start_timer(&tsct);
        while (num_pkts-- > 0) {
            pthread_mutex_lock(&pmap->mutex);
            while (pmap->count == 0) {
                pthread_cond_wait(&pmap->fill, &pmap->mutex);
            }

            memcpy(buffer, &pmap->data[0] + (pmap->consumed * size), size);
            pmap->consumed = (pmap->consumed + 1) % max_count;
            pmap->count--;

            pthread_cond_signal(&pmap->empty);
            pthread_mutex_unlock(&pmap->mutex);
        }

        // ack data transfer
        pthread_mutex_lock(&pmap2->mutex);
        while (pmap2->count == max_count) {
            pthread_cond_wait(&pmap2->empty, &pmap2->mutex);
        }

        pmap2->produced = (pmap2->produced + 1) % max_count;
        pmap2->count++;

        pthread_cond_signal(&pmap2->fill);
        pthread_mutex_unlock(&pmap2->mutex);
        stop_timer(&tsct);
        ns_time = get_timer_ns(&tsct);
        printf("%lu \n", ns_time);
    }
    free(buffer);
}

void parent(struct shmem_map *pmap, struct shmem_map *pmap2, int tput, int size,
            size_t region_size) {
    int max_data = region_size - sizeof(struct shmem_map);
    int max_count = max_data / size;
    char *buffer = calloc(sizeof(char), size);

    if (buffer == NULL) {
        printf("cannot alloc memory for rx\n");
        return;
    }
    set_affinity(1);

    if (tput == 0) {
        int i;
        for (i = 0; i < LATENCY_RUNS; i++) {

            // produce
            pthread_mutex_lock(&pmap->mutex);
            while (pmap->count == max_count) {
                pthread_cond_wait(&pmap->empty, &pmap->mutex);
            }

            memcpy(&pmap->data[0] + (pmap->produced * size), buffer, size);
            pmap->produced = (pmap->produced + 1) % max_count;
            pmap->count++;

            pthread_cond_signal(&pmap->fill);
            pthread_mutex_unlock(&pmap->mutex);

            // consume
            pthread_mutex_lock(&pmap2->mutex);
            while (pmap2->count == 0) {
                pthread_cond_wait(&pmap2->fill, &pmap2->mutex);
            }

            memcpy(buffer, &pmap2->data[0] + (pmap2->consumed * size), size);
            pmap2->consumed = (pmap2->consumed + 1) % max_count;
            pmap2->count--;

            pthread_cond_signal(&pmap2->empty);
            pthread_mutex_unlock(&pmap2->mutex);
        }
    } else {
        // TPUT test, we will send atleast a 100MB of data
        int num_pkts = (100 * 1024 * 1024) / size;

        while (num_pkts-- > 0) {
            pthread_mutex_lock(&pmap->mutex);
            while (pmap->count == max_count) {
                pthread_cond_wait(&pmap->empty, &pmap->mutex);
            }

            memcpy(&pmap->data[0] + (pmap->produced * size), buffer, size);
            pmap->produced = (pmap->produced + 1) % max_count;
            pmap->count++;

            pthread_cond_signal(&pmap->fill);
            pthread_mutex_unlock(&pmap->mutex);
        }

        // wait for ack
        pthread_mutex_lock(&pmap2->mutex);
        while (pmap2->count == 0) {
            pthread_cond_wait(&pmap2->fill, &pmap2->mutex);
        }

        pmap2->consumed = (pmap2->consumed + 1) % max_count;
        pmap2->count--;

        pthread_cond_signal(&pmap2->empty);
        pthread_mutex_unlock(&pmap2->mutex);
    }
    free(buffer);
}

int main(int argc, char **argv) {
    int r, fd, fd2;
    void *ptr, *ptr2;
    int ch;
    int tput = 0;
    unsigned long int size = 4;
    pthread_mutexattr_t sattr;
    pthread_condattr_t fattr, eattr;
    const char *memname = "/smemipc";
    struct shmem_map *pmap = NULL;
    // The second instance is for Latency measurement
    const char *memname2 = "/smemipc2";
    struct shmem_map *pmap2 = NULL;
    const size_t region_size = MAX_MEM + sizeof(struct shmem_map);

    while ((ch = getopt(argc, argv, "s:t")) != -1) {
        switch (ch) {
            case 't':
                tput = 1;
                break;
            case 's':
                size = strtoul(optarg, NULL, 10);
                if (size > MAX_MEM) {
                    printf("Not enough shared memory\n");
                }
                break;
            case '?':
            default:
                die("Not enough arguments");
        }
    }

    if (pthread_mutexattr_init(&sattr) != 0) {
        die("cannot initialize mutex attribute");
    }

    if (pthread_condattr_init(&fattr) != 0) {
        die("cannot initialize cv attribute");
    }

    if (pthread_condattr_init(&eattr) != 0) {
        die("cannot initialize cv attribute");
    }

    if (pthread_mutexattr_setpshared(&sattr, PTHREAD_PROCESS_SHARED) != 0) {
        die("cannot initialize mutex sharing");
    }

    if (pthread_condattr_setpshared(&fattr, PTHREAD_PROCESS_SHARED) != 0) {
        die("cannot initialize mutex sharing");
    }

    if (pthread_condattr_setpshared(&eattr, PTHREAD_PROCESS_SHARED) != 0) {
        die("cannot initialize mutex sharing");
    }
    // clear older references...
    shm_unlink(memname);
    shm_unlink(memname2);

    fd = shm_open(memname, O_CREAT | O_RDWR, 0666);
    if (fd == -1)
        die("shm_open");
    fd2 = shm_open(memname2, O_CREAT | O_RDWR, 0666);
    if (fd == -1)
        die("shm_open");

    r = ftruncate(fd, region_size);
    if (r != 0)
        die("ftruncate");
    r = ftruncate(fd2, region_size);
    if (r != 0)
        die("ftruncate");

    ptr = mmap(0, region_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED)
        die("mmap");
    close(fd);
    ptr2 = mmap(0, region_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
    if (ptr == MAP_FAILED)
        die("mmap");
    close(fd2);

    pmap = (struct shmem_map *)ptr;
    pmap2 = (struct shmem_map *)ptr2;

    pthread_mutex_init(&pmap->mutex, &sattr);
    pthread_cond_init(&pmap->fill, &fattr);
    pthread_cond_init(&pmap->empty, &eattr);
    pmap->produced = 0;
    pmap->consumed = 0;
    pmap->count = 0;
    pthread_mutex_init(&pmap2->mutex, &sattr);
    pthread_cond_init(&pmap2->fill, &fattr);
    pthread_cond_init(&pmap2->empty, &eattr);
    pmap2->produced = 0;
    pmap2->consumed = 0;
    pmap2->count = 0;

    pid_t pid = fork();

    if (pid == 0) {
        child(pmap, pmap2, tput, size, region_size);
        exit(0);
    } else if (pid > 0){
        parent(pmap, pmap2, tput, size, region_size);
    } else {
        printf("error forking\n");
    }


    munmap(ptr, region_size);
    munmap(ptr2, region_size);

    shm_unlink(memname);
    shm_unlink(memname2);

    return 0;
}
