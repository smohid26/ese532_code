#include <stdlib.h>
#include <stdio.h>
#include "App.h"
#include "stopwatch_c.h"

#define INPUT_HEIGHT (4000)
#define INPUT_WIDTH (6000)

#define FILTER_LENGTH (7)

#define OUTPUT_HEIGHT (INPUT_HEIGHT - (FILTER_LENGTH - 1))
#define OUTPUT_WIDTH (INPUT_WIDTH - (FILTER_LENGTH - 1))

unsigned Coefficients[] = {2, 15, 62, 98, 62, 15, 2};

void Filter_horizontal(const unsigned char * Input, unsigned char * Output)
{
  stopwatch_handle sw = stopwatch_create();
  stopwatch_start(sw);


  
  LOOP1: for (int Y = 0; Y < INPUT_HEIGHT; Y++)
    LOOP2: for (int X = 0; X < OUTPUT_WIDTH; X++)
    {
      unsigned int Sum = 0;
      LOOP3: for (int i = 0; i < FILTER_LENGTH; i++)
        Sum += Coefficients[i] * Input[Y * INPUT_WIDTH + X + i];
      Output[Y * OUTPUT_WIDTH + X] = Sum >> 8;
    }
    
  stopwatch_stop(sw);

  printf("Filter Horizontal latency: %lf\n", stopwatch_latency(sw));
  printf("Filter Horizontal avg latency: %lf\n", stopwatch_avg_latency(sw));
}

void Filter_vertical(const unsigned char * Input, unsigned char * Output)
{
  stopwatch_handle sw = stopwatch_create();
  stopwatch_start(sw);

  

  LOOP1: for (int Y = 0; Y < OUTPUT_HEIGHT; Y++)
    LOOP2: for (int X = 0; X < OUTPUT_WIDTH; X++)
    {
      unsigned int Sum = 0;
      LOOP3: for (int i = 0; i < FILTER_LENGTH; i++)
        Sum += Coefficients[i] * Input[(Y + i) * OUTPUT_WIDTH + X];
      Output[Y * OUTPUT_WIDTH + X] = Sum >> 8;
    }
    
  stopwatch_stop(sw);

  printf("Filter Vertical latency: %lf\n", stopwatch_latency(sw));
  printf("Filter Vertical avg latency: %lf\n", stopwatch_avg_latency(sw));
}

void Filter(const unsigned char * Input, unsigned char * Output)
{
  unsigned char * Temp = (unsigned char*)malloc(INPUT_HEIGHT * OUTPUT_WIDTH);
  Filter_horizontal(Input, Temp);
  Filter_vertical(Temp, Output);
  free(Temp);
}

