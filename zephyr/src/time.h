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


void check_schedule(int currentTime, int ts1, int ts2, int ts3);

#endif
