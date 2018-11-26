#include <stdbool.h>
#include <stdio.h>
#include "time.h"

#include <zephyr.h>

#define SCHEDULE_WINDOW MSEC_PER_SEC

int time_unix;
int time_stored_at = 0;
int schedule1;
int schedule2;
int schedule3;

void setTime(int time)
{
	time_unix = time;
	time_stored_at = (uint32_t)k_uptime_get_32() / 1000;
}

int getTime()
{
	int current_up_time = (uint32_t)k_uptime_get_32() / 1000;
	int diff_time = current_up_time - time_stored_at;
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

bool check_schedule(int schedule){
	int sec_of_day =  getTime() % (24 * 60 * 60);
	int hour = sec_of_day / (60 * 60);
	int minute = sec_of_day % (60 * 60) / 60;

	int scheduleMinutes = get_minutes(schedule);
	int scheduleHours = get_hour(schedule);

	if(hour == scheduleHours && minute == scheduleMinutes){
		printf("SCHEDULE HIT! %d %d\n", scheduleHours, scheduleMinutes);
		return true;
	}

	return false;
}

// Checks the schedule, updates last activation time if in schedule
bool is_on_schedule()
{
	printf("schedule1: %d , schedule2 %d , schedule3 %d", schedule1, schedule2, schedule3);
	if (check_schedule(schedule1) || check_schedule(schedule2) || check_schedule(schedule3)) {
		printf("is on schedule true");
		return true;
	}
	return false;
}

void set_schedules(int ts1, int ts2, int ts3)
{
	schedule1 = ts1;
	schedule2 = ts2;
	schedule3 = ts3;
}
