#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM 5

pthread_mutex_t mutex1,mutex2,mutex3,mutex4,mutex5;

void *thr_fn1(void *arg);
void *thr_fn2(void *arg);
void *thr_fn3(void *arg);
void *thr_fn4(void *arg);
void *thr_fn5(void *arg);


int main(void)
{
	pthread_t tid1,tid2,tid3,tid4,tid5;
	pthread_mutex_init(&mutex1,NULL);
	pthread_mutex_init(&mutex2,NULL);
	pthread_mutex_init(&mutex3,NULL);
	pthread_mutex_init(&mutex4,NULL);
	pthread_mutex_init(&mutex5,NULL);

	pthread_create(&tid1,NULL,thr_fn1,NULL);
	pthread_create(&tid2,NULL,thr_fn2,NULL);
	pthread_create(&tid3,NULL,thr_fn3,NULL);
	pthread_create(&tid4,NULL,thr_fn4,NULL);
	pthread_create(&tid5,NULL,thr_fn5,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	pthread_join(tid4,NULL);
	pthread_join(tid5,NULL);

	return 0;
}

void *thr_fn1(void *arg)
{
	int i;
	while(1)
	{
		i = rand()%10;
		printf("professor 1  begin to thinking %d seconds\n ",i);
		sleep(i);
		pthread_mutex_lock(&mutex5);
		printf("professor 1 get the chopstick 5\n");
		pthread_mutex_lock(&mutex1);
		printf("professor 1 get the chopstick 1\n");
		printf("professor 1 begin to eat %d seconds\n",i);
		sleep(i);
		pthread_mutex_unlock(&mutex1);
		pthread_mutex_unlock(&mutex5);
	}
}

void *thr_fn2(void *arg)
{
	int i;
	while(1)
	{
		i = rand()%10;
		printf("professor 2  begin to thinking %d seconds\n ",i);
		sleep(i);
		pthread_mutex_lock(&mutex1);
		printf("professor 2 get the chopstick 1\n");
		pthread_mutex_lock(&mutex2);
		printf("professor 2 get the chopstick 2\n");
		printf("professor 2 begin to eat %d seconds\n",i);
		sleep(i);
		pthread_mutex_unlock(&mutex2);
		pthread_mutex_unlock(&mutex1);
	}
}

void *thr_fn3(void *arg)
{
	int i;
	while(1)
	{
		i = rand()%10;
		printf("professor 3  begin to thinking %d seconds\n ",i);
		sleep(i);
		pthread_mutex_lock(&mutex2);
		printf("professor 3 get the chopstick 2\n");
		pthread_mutex_lock(&mutex3);
		printf("professor 3 get the chopstick 3\n");
		printf("professor 3 begin to eat %d seconds\n",i);
		sleep(i);
		pthread_mutex_unlock(&mutex3);
		pthread_mutex_unlock(&mutex2);
	}
}

void *thr_fn4(void *arg)
{
	int i;
	while(1)
	{
		i = rand()%10;
		printf("professor 4  begin to thinking %d seconds\n ",i);
		sleep(i);
		pthread_mutex_lock(&mutex3);
		printf("professor 4 get the chopstick 3\n");
		pthread_mutex_lock(&mutex4);
		printf("professor 4 get the chopstick 4\n");
		printf("professor 4 begin to eat %d seconds\n",i);
		sleep(i);
		pthread_mutex_unlock(&mutex4);
		pthread_mutex_unlock(&mutex3);
	}
}

void *thr_fn5(void *arg)
{
	int i;
	while(1)
	{
		i = rand()%10;
		printf("professor 5  begin to thinking %d seconds\n ",i);
		sleep(i);
		pthread_mutex_lock(&mutex4);
		printf("professor 5 get the chopstick 4\n");
		pthread_mutex_lock(&mutex5);
		printf("professor 5 get the chopstick 5\n");
		printf("professor 5 begin to eat %d seconds\n",i);
		sleep(i);
		pthread_mutex_unlock(&mutex5);
		pthread_mutex_unlock(&mutex4);
	}
}


