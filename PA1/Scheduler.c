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

#define 	STAMPSIZE 17
#define		EVENTSIZE 120

	sem_t sem ,sem2;
	pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;
	MinHeap minHeap;
    char initial_stamp[20];
    timeInt_t start_year, start_day, start_hour,start_minute, start_second;
    bool active = true;


void * updateNow (void * arg){

	while(true){
	sleep(1);
	pthread_mutex_lock(&mutex2);

	start_second++;
	if (start_second >= SECONDS) {
		start_second = 0;
		start_minute++;
	}
	if (start_minute >= MINUTES) {
		start_minute=0;
		start_hour++;
		}
	if (start_hour >= HOURS) {
		start_hour = 0;
		start_day++;
		}
	if (start_day > DAYS) {
		start_year++;
		}
	pthread_mutex_lock(&mutex3);
	sprintf(initial_stamp,"%u/%03u/%02u/%02u/%02u",start_year, start_day, start_hour,start_minute,start_second);
	pthread_mutex_unlock(&mutex3);
	pthread_mutex_unlock(&mutex2);

	}
	return 0;
}

void setTimer(){

	char *next_event;
	char buffer[20];
	timeInt_t yyyy2, ddd2, hh2, mm2, ss2;
	 int result;

	pthread_mutex_lock(&mutex);
	next_event  = getMin(&minHeap);
	if(next_event != 0)
	{
		strncpy(buffer,next_event,17);
	}
	pthread_mutex_unlock(&mutex);
	if(next_event == 0)
		return;

	buffer[17] = '\0';
	sscanf(buffer, "%u/%u/%u/%u/%u", &yyyy2, &ddd2, &hh2, &mm2, &ss2);
	pthread_mutex_lock(&mutex2);
	result = (yyyy2 - start_year)*(YEAR_TO_SEC) + (ddd2 - start_day)*(DAY_TO_SEC)+ (hh2 - start_hour)*(HOUR_TO_SEC) + (mm2 - start_minute)*(MIN_TO_SEC)+ (ss2 - start_second) ;
	pthread_mutex_unlock(&mutex2);
	if(result <0 )
		result = 0;
	alarm(result + 1 );
}



int compareTime(char* new_event) {
	int tmp_num = 0;
	timeInt_t yyyy2, ddd2, hh2, mm2, ss2;
	tmp_num = sscanf(new_event, "%u/%u/%u/%u/%u", &yyyy2, &ddd2, &hh2, &mm2, &ss2);
	if (tmp_num == 5)
	{
		pthread_mutex_lock(&mutex2);
		tmp_num=strncmp(new_event, initial_stamp, STAMPSIZE);
		pthread_mutex_unlock(&mutex2);
		return tmp_num;
	}
	else
		return 0;
}

void createEvent(char * event, char * new_stamp) {
	char tmp[120];
	strcpy(tmp, new_stamp);
	strcat(tmp, " \0");
	strcat(tmp, event);
	strcpy(event, tmp);
}

static int stringCompare(const void * p1, const void * p2) {
	const char * p01 = p1;
	const char * p02 = p2;
	return strcmp(p01, p02);
}
void * worker(void * arg) {
	char buffer[120];
	char buffer2[120];
	while (true) {
		sem_wait(&sem);

		pthread_mutex_lock(&mutex);
		removeMin(&minHeap, buffer);
		if(buffer != 0)
			strcpy(buffer2,buffer);
		pthread_mutex_unlock(&mutex);

		printf("%s\n", buffer2);
		setTimer();
		if (active == 0)
		{
			if (getMin(&minHeap) == 0)
				sem_post(&sem2);
		}
	}
	return 0;
}

static
void timeout_handler(int signo, siginfo_t * info, void *p){
    sem_post(&sem);
}


int main(int argc, char** argv) {
	if (argc != 2) {
		printf("No initial time-stamp Shutting down\n");
		return 0;
	}
	struct sigaction action;
	action.sa_flags = SA_SIGINFO | SA_RESTART;
	action.sa_sigaction = timeout_handler;
	sigemptyset( &action.sa_mask );
	sigaction( SIGALRM, &action, 0 );
        
	char event[120];
	char new_stamp[20];
	pthread_t		tid;
	pthread_t		tid2;
	pthread_mutex_init( &mutex, NULL );
	pthread_mutex_init(&mutex2,NULL);
	pthread_mutex_init(&mutex3,NULL);
	strcpy(initial_stamp, argv[1]);
	sscanf(initial_stamp,"%u/%u/%u/%u/%u",&start_year, &start_day, &start_hour,&start_minute,&start_second);
	initializeMinHeap(&minHeap, stringCompare, sizeof(char) * 120);
	sem_init(&sem, 0, 0);
	sem_init(&sem2, 0, 0);
	pthread_create( &tid, 0, worker, 0 );
	pthread_create(&tid2,0,updateNow,0);

while (printf("enter timestamp, q(quit), or t (time now) >"), scanf(" %s", new_stamp) > 0) {
		if (strcmp(new_stamp, "q") == 0 || strcmp(new_stamp, "quit") == 0) {
			active = 0;
			break;
		}else if(strcmp("t",new_stamp)==0){

			pthread_mutex_lock(&mutex3);
			printf( "%s\n" ,initial_stamp);
			pthread_mutex_unlock(&mutex3);
			continue;
		}

		printf("enter event details> ");
		scanf(" %s", event);
		createEvent(event, new_stamp);
		if (compareTime(event) > 0) {
			pthread_mutex_lock(&mutex);
			addElement(&minHeap, event);
			pthread_mutex_unlock(&mutex);
			setTimer();
		} else
			printf("invalid TimeStamp \n");
	}
	sem_post(&sem);
	sem_wait(&sem2);
	printf("Normal end.\n");
	pthread_mutex_lock(&mutex);
	destroyMinHeap(&minHeap);

}
