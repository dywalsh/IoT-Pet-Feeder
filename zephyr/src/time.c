#include <stdbool.h>
#include "time.h"
int time_unix;


void setTime(int time)
{
	time_unix = time;
}

int getTime()
{
	return time_unix;
}

bool hasTime()
{
	if (time_unix != 0){
		return true;
	}

	return false;
}