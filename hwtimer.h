#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

typedef uint64_t hrtime_t;

__inline__ hrtime_t _rdtsc() {
    unsigned long int lo, hi;
    __asm__ __volatile__ ("rdtscp" : "=a" (lo), "=d" (hi));
    return (hrtime_t)hi << 32 | lo;
}

typedef struct {
	hrtime_t start;
	hrtime_t end;
	double cpuMHz;
} hwtimer_t;

inline void reset_timer(hwtimer_t* timer)
{
	timer->start = 0;
	timer->end = 0;
}

inline void init_timer(hwtimer_t* timer) 
{
#if defined(__linux) || defined(__linux__) || defined(linux)
    FILE* cpuinfo;
    char str[100];
    cpuinfo = fopen("/proc/cpuinfo","r");
    while(fgets(str,100,cpuinfo) != NULL){
        char cmp_str[8];
        strncpy(cmp_str, str, 7);
        cmp_str[7] = '\0';
        if (strcmp(cmp_str, "cpu MHz") == 0) {
			double cpu_mhz;
			sscanf(str, "cpu MHz : %lf", &cpu_mhz);
			timer->cpuMHz = cpu_mhz;
			break;
        }
    }
    fclose( cpuinfo );
#else
    timer->cpuMHz = 0;
#endif

	reset_timer(timer);
}

inline void start_timer(hwtimer_t* timer)
{
#if defined(TSCTIMER)
    timer->start = _rdtsc();
#else
    struct timespec time1;
    clock_gettime(CLOCK_MONOTONIC_RAW, &time1);
    timer->start = (time1.tv_sec * 1000000000) + time1.tv_nsec;
#endif
}

inline void stop_timer(hwtimer_t* timer)
{
#if defined(TSCTIMER)
    timer->end = _rdtsc();
#else
    struct timespec time1;
    clock_gettime(CLOCK_MONOTONIC_RAW, &time1);
    timer->end = (time1.tv_sec * 1000000000) + time1.tv_nsec;
#endif
}

inline uint64_t get_timer_ticks(hwtimer_t* timer)
{
	return timer->end - timer->start;
}

inline uint64_t get_timer_ns(hwtimer_t* timer)
{
	if (timer->cpuMHz == 0) {
		/* Cannot use a timer without first initializing it 
		   or if not on linux 
		*/
		return 0;
	}
#if defined(TSCTIMER)
	return (uint64_t)(((double)get_timer_ticks(timer))/timer->cpuMHz*1000);
#else
    return (uint64_t)(get_timer_ticks(timer));
#endif
}
#endif
