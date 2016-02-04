#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sched.h>
#include "hwtimer.h"

void set_affinity(int cpuid){
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(cpuid, &set);

    if (sched_setaffinity(getpid(), sizeof(set), &set) == -1)
        perror("sched_affinity");

}

int main()
{
    hwtimer_t tsct;
    uint64_t timetsc;
    set_affinity(0);
    init_timer(&tsct);
    start_timer(&tsct);
    stop_timer(&tsct);
    timetsc = get_timer_ns(&tsct);
    printf("%lu \n", timetsc);

    //calculating accuracy
    start_timer(&tsct);
    sleep(1);
    stop_timer(&tsct);
    timetsc = get_timer_ns(&tsct);
    printf("%lu \n", timetsc-1000000);   
    return 0;
}
