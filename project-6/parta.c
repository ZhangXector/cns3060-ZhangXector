#include <stdio.h>
#include <pthread.h>

#define SUCCESS 0
#define ERROR -1

void* incrementCounter(void* m);

int main()
{
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
