// Antonio Shelton-McGaha
// OS Producer-Consumer Lab

#ifndef SHAREDDATA_H
#define SHAREDDATA_H

#include <semaphore.h>
#include <stdlib.h>
struct data 
{
	sem_t mutex;
	int table[2];
};

#endif //SHAREDDATA_H