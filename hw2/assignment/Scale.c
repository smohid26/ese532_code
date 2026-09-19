#include "stopwatch_c.h"
#include <stdio.h>

#define HEIGHT (8000)
#define WIDTH (12000)

void Scale(const unsigned char * Input, unsigned char * Output)
{
  stopwatch_handle sw = stopwatch_create();
  stopwatch_start(sw);

  for (int Y = 0; Y < HEIGHT; Y += 2)
    for (int X = 0; X < WIDTH; X += 2)
      Output[(Y / 2) * WIDTH / 2 + (X / 2)] = Input[Y * WIDTH + X];

  stopwatch_stop(sw);

  printf("Scale latency: %lf\n", stopwatch_latency(sw));
  printf("Scale avg latency: %lf\n", stopwatch_avg_latency(sw));
}
