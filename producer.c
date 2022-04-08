// Antonio Shelton-McGaha
// OS Producer-Consumer Lab

#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/types.h>

#include "shared.h"

void undoSHM(void) 
{
	shm_unlink("opersysproj1");
}

int main() 
{
    	srand(time(NULL));
	int numOfProdCons = 15;

	atexit(undoSHM);
	int fileDescriptor = shm_open("opersysproj1", O_CREAT | O_RDWR, 0666);

	if(fileDescriptor < 0) 
    	{
        	printf("Initialization of shared memory failed.\n");
        	return 0;
    	}

	ftruncate(fileDescriptor, 1024);

	struct data *mem = mmap(NULL, 1024, PROT_READ|PROT_WRITE, MAP_SHARED, fileDescriptor, 0);

	if(fileDescriptor < 0) 
    	{
		printf("Initialization of shared memory failed.\n");
		return 0;
	}

	mem->table[0] = -1;
    	mem->table[1] = -1;

	sem_init(&mem->mutex, 1, 1);
    	int i = 0;

	while(numOfProdCons > 0) 
    	{
		sem_wait(&mem->mutex);
		printf("Producer has began producing.\n");
		if(mem->table[i] == -1) 
        	{
			int randNum = rand() % 1000 + 1;
			mem->table[i] = randNum;
			printf("ID %d: filling with item: %d \n", i, randNum);
			i++;
		}
		else 
			printf("ID %d: filled, recheck occurs in next critical section\n", i);
		
		if(i > 1) 
			i = 0;
		
		numOfProdCons--;
		sem_post(&mem->mutex);
		sleep(1);
	}
}
