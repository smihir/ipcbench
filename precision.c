#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "hwtimer.h"

int main()
{
    hwtimer_t tsct;
    uint64_t timetsc;

    init_timer(&tsct);
    start_timer(&tsct);
    stop_timer(&tsct);
    timetsc = get_timer_ns(&tsct);
    printf("%lu \n", timetsc);
    return 0;
}
