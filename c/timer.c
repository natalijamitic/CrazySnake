#include "timer.h"
#include <time.h>

Time countdown(Time currenttime, double program_time) {
	Time nexttime;
	double seconds;
	nexttime.seconds = currenttime.seconds - program_time;
	if (nexttime.seconds < 0) {
		if (currenttime.minutes > 0) {
			seconds = -nexttime.seconds;
			nexttime.seconds = MINUT - seconds;
			nexttime.minutes = --currenttime.minutes;
		}
		else {
			nexttime.minutes = 0;
			nexttime.seconds = 0;
		}
	}
	else {
		nexttime.minutes = currenttime.minutes;
	}
	return nexttime;
}
