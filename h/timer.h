#ifndef _timer_h_
#define _timer_h_
#include <Windows.h>
#define MINUT 60
//Time. 
typedef struct {
	double minutes, seconds;
} Time;
//Calculate time.
Time countdown(Time, double);

#endif