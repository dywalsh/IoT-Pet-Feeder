#include <stdbool.h>
#include <stdio.h>
#include "time.h"

#include <zephyr.h>


int time_unix;
int time_stored_at = 0;
int last_fed = 0;


void setTime(int time)
{
	time_unix = time;
	time_stored_at = (uint32_t)k_uptime_get_32() / 1000;
}

int getTime()
{
	int current_up_time = (uint32_t)k_uptime_get_32() / 1000;
	printf("Current up time = %d\n", current_up_time);
	int diff_time = current_up_time - time_stored_at;
	printf("Diff time = %d\n", diff_time);
	printf("time unix = %d\n", time_unix);
	printf("time unix + diff time = %d\n", (time_unix+diff_time));
	return time_unix + diff_time;
}

bool hasTime()
{
	if (time_unix != 0){
		return true;
	}

	return false;
}