
#ifndef scheduler_h
#define scheduler_h
#include	"MinHeap.h"
#include	<stdio.h>
#include	<string.h>
#include 	"scheduler.h"
#include 	<semaphore.h>
#include    <pthread.h>
#include	<unistd.h>
#include    <signal.h>
#include    <sys/time.h>
#include 	<time.h>

#define MIN_TO_SEC 60
#define HOUR_TO_SEC MIN_TO_SEC * 60
#define DAY_TO_SEC HOUR_TO_SEC*24
#define YEAR_TO_SEC DAY_TO_SEC * 366
#define SECONDS 60
#define MINUTES 60
#define HOURS 24
#define DAYS 366
#define false 0
#define true 1
#define why printf("here\n");

typedef unsigned short bool;
typedef unsigned int timeInt_t;
extern pthread_mutex_t mutex , mutex2, mutex3;
extern sem_t sem ,sem2;
extern timeInt_t start_year, start_day, start_hour, start_second;


int compareTime(char* new_event);
void createEvent(char * event, char * new_stamp);
void * worker(void *arg);
void setTimer();
static void timeout_handler(int signo, siginfo_t * info, void *p);
void setNow(char *stamp);

#endif
