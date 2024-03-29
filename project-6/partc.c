// Cliff Kelley
// CS 3060
// Project 6 - Threads

#include <stdio.h>
#include <pthread.h>

#define SUCCESS 0
#define ERROR -1

int count;

void* incrementCounter(void* m);

int main()
{
	count = 0;

	printf("\n====================================\n");
	printf("Part C - Waits for threads, no sleep\n");
	printf("------------------------------------\n");

	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	pthread_t thread4;

	if(pthread_create(&thread1, NULL, &incrementCounter, NULL) != SUCCESS)
	{
		perror("Unable to create thread 1.");
		return ERROR;
	}
	if(pthread_create(&thread2, NULL, &incrementCounter, NULL) != SUCCESS)
	{
		perror("Unable to create thread 2.");
		return ERROR;
	}
	if(pthread_create(&thread3, NULL, &incrementCounter, NULL) != SUCCESS)
	{
		perror("Unable to create thread 3.");
		return ERROR;
	}
	if(pthread_create(&thread4, NULL, &incrementCounter, NULL) != SUCCESS)
	{
		perror("Unable to create thread 4.");
		return ERROR;
	}

	if(pthread_join(thread1, NULL) != SUCCESS)
	{
		perror("Unable to join thread 1.");
		return ERROR;
	}
	if(pthread_join(thread2, NULL) != SUCCESS)
	{
		perror("Unable to join thread 2.");
		return ERROR;
	}
	if(pthread_join(thread3, NULL) != SUCCESS)
	{
		perror("Unable to join thread 3.");
		return ERROR;
	}
	if(pthread_join(thread4, NULL) != SUCCESS)
	{
		perror("Unable to join thread 4.");
		return ERROR;
	}

	printf("Count: %i\n", count);
	printf("====================================\n\n");

	return SUCCESS;
}

void * incrementCounter(void* m)
{
	int i;
	for(i = 0; i < 10; ++i)
	{
		int tempValue = count;
		//sleep(1);
		tempValue += 1;
		count = tempValue;
	}

	return NULL;
}
