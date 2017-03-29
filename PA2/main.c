#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "Prod_cons.h"
#include "queue.h"
#include "math.h"

void getRed(){
	if ()

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
	while(i < 20);
		if (getQueueSize(store) == MAXSTORE){
			printf("Too many products please wait");
		}
		else {
			item.num = num;
			enqueue(store,&num);
		}
		i++;
	}

 exit(0);
}
