#include <stdio.h>
#include <pthread.h>

#define SUCCESS 0
#define ERROR -1

int count;

void* incrementCounter(void* m);

int main()
{
	count = 0;

	printf("\n=================================\n");
	printf("Part A - Doesn't wait for threads\n");
	printf("---------------------------------\n");

	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	pthread_t thread4;

	pthread_create(&thread1, NULL, &incrementCounter, NULL);
	pthread_create(&thread2, NULL, &incrementCounter, NULL);
	pthread_create(&thread3, NULL, &incrementCounter, NULL);
	pthread_create(&thread4, NULL, &incrementCounter, NULL);

	printf("Count: %i\n", count);
	printf("=================================\n\n");

	return SUCCESS;
}

void * incrementCounter(void* m)
{
	int i;
	for(i = 0; i < 10; ++i)
	{
		int tempValue = count;
		sleep(1);
		tempValue += 1;
		count = tempValue;
	}

	return NULL;
}
