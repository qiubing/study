#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NLOOP 5000

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int counter;

void *thr_fn(void *arg);

int main(void)
{
	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,thr_fn,NULL);
	pthread_create(&tid2,NULL,thr_fn,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	return 0;
}

void *thr_fn(void *arg)
{
	int i,val;

	for(i = 0;i < NLOOP; i++)
	{
		pthread_mutex_lock(&mutex);
		val = counter;
		printf("%lu:%d\n",pthread_self(),val+1);
		counter = val + 1;
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}
	
