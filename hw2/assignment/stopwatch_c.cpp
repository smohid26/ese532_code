#include "stopwatch.h"
#include "stopwatch_c.h"

stopwatch_handle stopwatch_create(void)
{
    return new stopwatch();
}

void stopwatch_reset(stopwatch_handle sw)
{
    static_cast<stopwatch*>(sw)->reset();
}

void stopwatch_start(stopwatch_handle sw)
{
    static_cast<stopwatch*>(sw)->start();
}

void stopwatch_stop(stopwatch_handle sw)
{
    static_cast<stopwatch*>(sw)->stop();
}

double stopwatch_latency(stopwatch_handle sw)
{
    return static_cast<stopwatch*>(sw)->latency();
}

double stopwatch_avg_latency(stopwatch_handle sw)
{
    return static_cast<stopwatch*>(sw)->avg_latency();
}