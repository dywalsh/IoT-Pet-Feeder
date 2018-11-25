#ifndef __TIME_H__
#define __TIME_H__


extern int time_unix;
extern int time_stored_at;
extern int last_fed;
extern int schedule1;
extern int schedule2;
extern int schedule3;

int getTime();

void setTime(int time);

bool hasTime();

int get_minutes(int time);

int get_hour(int time);

bool is_on_schedule();

void set_schedules(int schedule1, int schedule2, int schedule3);

#endif
