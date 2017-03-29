#ifndef PROD_CONS_H
#define PROD_CONS_H
#define MAXSTORE 20
#include "queue.h"

typedef struct product{
	int num;
	char color [6];
	unsigned short rejections;
}product;

extern Queue *store;
enum{RED,BLUE,GREEN};

#endif
