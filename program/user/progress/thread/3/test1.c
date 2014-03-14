#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main(void)
{
	pthread_t tid;

	tid = pthread_self();
	printf("Thread ID:%lu\n",tid);

	if(pthread_equal(tid,pthread_self()))
	{
		printf("equal\n");
	}else
	{
		printf("Not equal\n");
	}
	return 0;
}
