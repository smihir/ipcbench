#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sched.h>
#include <math.h>
#include "hwtimer.h"

#define MAX_RUNS 10

void set_affinity(int cpuid){
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(cpuid, &set);

    if (sched_setaffinity(getpid(), sizeof(set), &set) == -1)
        perror("sched_affinity");

}

uint64_t mean(uint64_t *v, int size) {
    int i = 0;
    uint64_t s = 0;

    for (i = 0; i < size; i++) {
        s += v[i];
    }

    return (s/size);
}

double stdev(uint64_t *v, int size) {
    int i;
    uint64_t sq = 0, meanval = mean(v, size);

    for (i = 0; i < size; i++) {
        sq += ((v[i] - meanval) * (v[i] - meanval));
    }

    return (sqrt(((double)sq)/size));
}

int main()
{
    clock_t start, end;
    uint64_t timetsc[MAX_RUNS], meanval;
    double sdval;
    int i, j;
    unsigned long k = 1;

    set_affinity(0);

    start = clock();
    end = clock();

    if (start - end != 0) {
        for (i = 0; i < MAX_RUNS; i++) {
            sleep(1);
            start = clock();
            end = clock();
            timetsc[i] = (end - start);
        }
    }

redo:
    while (start - end == 0) {
        k += k;
        if (k == 0) {
            printf("Cannot calculate precision!\n");
            return 0;
        }
        start = clock();
        for (j = 0; j < k; j++);
        end = clock();
    }

    start = clock();
    for (j = 0; j < k; j++);
    end = clock();

    if (start - end == 0)
        goto redo;

    // adjust stddev to be withing 10% of mean
adjust:
    for (i = 0; i < MAX_RUNS; i++) {
        sleep(1);
        start = clock();
        for (j = 0; j < k; j++);
        end = clock();
        timetsc[i] = (end - start);
    }

    meanval = mean(timetsc, MAX_RUNS);
    sdval = stdev(timetsc, MAX_RUNS);

    if ((sdval / meanval) > 0.1) {
        k += k;
        goto adjust;
    }
    printf("Clock Precision: mean %luus stdev %fus\n", meanval, sdval);

    return 0;
}
