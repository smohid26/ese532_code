#ifndef STOPWATCH_C_H_
#define STOPWATCH_C_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef void* stopwatch_handle;

stopwatch_handle stopwatch_create(void);

void stopwatch_reset(stopwatch_handle sw);
void stopwatch_start(stopwatch_handle sw);
void stopwatch_stop(stopwatch_handle sw);

double stopwatch_latency(stopwatch_handle sw);
double stopwatch_avg_latency(stopwatch_handle sw);

#ifdef __cplusplus
}
#endif

#endif