#define _GNU_SOURCE
#define TSCTIMER
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
    hwtimer_t tsct;
    uint64_t timetsc[MAX_RUNS], meanval;
    double sdval;
    int i;

    set_affinity(0);

    for (i = 0; i < MAX_RUNS; i++) {
        init_timer(&tsct);
        sleep(1);
        start_timer(&tsct);
        stop_timer(&tsct);
        timetsc[i] = get_timer_ns(&tsct);
    }

    meanval = mean(timetsc, MAX_RUNS);
    sdval = stdev(timetsc, MAX_RUNS);
    printf("TSC Precision: mean %lu stdev %f\n", meanval, sdval);

    //calculating accuracy
    for (i = 0; i < MAX_RUNS; i++) {
        init_timer(&tsct);
        start_timer(&tsct);
        sleep(1);
        stop_timer(&tsct);
        timetsc[i] = get_timer_ns(&tsct);
        if (timetsc[i] < 1000000000)
            timetsc[i] = 1000000000 - timetsc[i];
        else
            timetsc[i] -= 1000000000;
    }

    meanval = mean(timetsc, MAX_RUNS);
    sdval = stdev(timetsc, MAX_RUNS);
    printf("TSC Error: mean %lu stdev %f\n", meanval, sdval);

    return 0;
}
