#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "Prod_cons.h"
#include "queue.h"
#include "math.h"

void * getRed(void * arg){
	size_t max_distance = ceil(sqrt(num));
	size_t i =0;
	while (i<= max_distance){
		if (num % i ==0){

		}
	}

}
void getBlue(){

}
void getGreen(){

}
void getReject(){

}

int main( int argc, char ** argv){
	int num;
	Queue *store;
	queueInit(store, sizeof(product));
	int i=0;
	product item;
//	while (printf("enter a number> "), scanf(" %s", &num)>0)
//	{
	while(i < 20){
		if (getQueueSize(store) == MAXSTORE){
			printf("Too many products please wait");
		}
		else {
			item.num = num;
			enqueue(store,item);
		}
		i++;
	}

 exit(0);
}
