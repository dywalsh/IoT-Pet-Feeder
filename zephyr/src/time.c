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

int get_minutes(int time){
	return time%100;
}

int get_hour(int time){
	return time/100;
}

void check_schedule(int currentTime, int ts1, int ts2, int ts3){
	int sec_of_day = currentTime % (24 * 60 * 60);
	int hour = sec_of_day / (60 * 60);
	int minute = sec_of_day % (60 * 60) / 60;

	int ts1Minutes = get_minutes(ts1);
	int ts1Hours = get_hour(ts1);

	int ts2Minutes = get_minutes(ts2);
	int ts2Hours = get_hour(ts2);

	int ts3Minutes = get_minutes(ts3);
	int ts3Hours = get_hour(ts3);

	printf("sec of day = %d\n current minute = %d\n current hour = %d\n", sec_of_day, minute, hour);
	printf("TS1 minute = %d\n TS1 hour = %d\n TS2 minute = %d\n TS2 hour = %d\n TS3 minute = %d\n TS3 hour = %d\n", ts1Minutes, ts1Hours, ts2Minutes, ts2Hours, ts3Minutes, ts3Hours);
	if((hour == ts1Hours && minute == ts1Minutes) || (hour == ts2Hours && minute == ts2Minutes) || (hour == ts3Hours && minute == ts3Minutes)){
		printf("SCHEDULE HIT!!!!!!!\n");
	}
}
