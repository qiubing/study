#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

void hander(void *arg)
{
	free(arg);
	pthread_mutex_unlock(&mutex);
}

void *thr_fn1(void *arg);
void *thr_fn2(void *arg);

int main(void)
{
	pthread_t tid1,tid2;
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);
	int err;
	if((err = pthread_create(&tid1,NULL,thr_fn1,NULL)) != 0)
	{
		perror("pthread_create");
	}

	if((err = pthread_create(&tid2,NULL,thr_fn2,NULL)) != 0)
	{
		perror("pthread_create");
	}

	sleep(1);
	do{
		pthread_cond_signal(&cond);

	}while(1);
	sleep(20);
	pthread_exit(0);
	return 0;

}

void *thr_fn1(void *arg)
{
	pthread_cleanup_push(hander,&mutex);
	while(1){
	printf("thread1 is running\n");
	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&cond,&mutex);
	printf("thread1 applied the condition\n");
	pthread_mutex_unlock(&mutex);
	sleep(4);
	}
	pthread_cleanup_pop(0);
}


void *thr_fn2(void *arg)
{
	while(1)
	{
		printf("thread 2 is running\n");
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond,&mutex);
		printf("thread 2 applied the condition\n");
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

