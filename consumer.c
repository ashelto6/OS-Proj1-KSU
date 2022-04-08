// Antonio Shelton-McGaha
// OS Producer-Consumer Lab

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>

#include "shared.h"

sem_t mutexLock;

void undoSHM(void) 
{
	shm_unlink("opersysproj1");
}

int main(int argc, char *argv[]) 
{
    int numOfProdCons = 15;

	atexit(undoSHM);
	int fileDescriptor = shm_open("opersysproj1", O_RDWR, 0666);

	while(fileDescriptor < 0) 
		fileDescriptor = shm_open("opersysproj1", O_RDWR, 0);

	if(fileDescriptor < 0) 
    {
        printf("opening of shared memory failed\n");
		return 0;
    }

	ftruncate(fileDescriptor, 1024);

	if(fileDescriptor < 0) 
    {
		printf("opening of shared memory failed\n");
		return 0;
	}

	struct data *mem = mmap(NULL, 1024, PROT_READ|PROT_WRITE, MAP_SHARED, fileDescriptor, 0);
	int i = 1;

	while(numOfProdCons > 0) 
    {
		sem_wait(&mem->mutex);
		printf("Consumer has began consuming.\n");

		if(mem->table[i]>-1) 
        {
			printf("ID %d: filled with value: %d. clearing in progress\n", i, mem->table[i]);
			mem->table[i] = -1;
			i++;
		}
		else
			printf("Table %d: is empty, next attempt occurs in next critical section\n", i);
		
		if(i > 1)
			i = 0;
	
		numOfProdCons--;
		sem_post(&mem->mutex);
		sleep(1);
	}
}
