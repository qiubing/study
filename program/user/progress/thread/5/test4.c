#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

#define NUM 5
int queue[NUM];
sem_t sem1,sem2;

void *producer(void *arg);
void *consumer(void *arg);

int main(void)
{
	pthread_t tid1,tid2;
	sem_init(&sem1,0,NUM);
	sem_init(&sem2,0,0);
	pthread_create(&tid1,NULL,producer,NULL);
	pthread_create(&tid2,NULL,consumer,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	sem_destroy(&sem1);
	sem_destroy(&sem2);

	return 0;
}

void *producer(void *arg)
{
	int  p = 0;
	for(;;){
		sem_wait(&sem1);
		queue[p] = rand()%1000 + 1;
		printf("produce %d\n",queue[p]);
		sem_post(&sem2);
		p = (p+1)%NUM;
		sleep(rand()%5);
	}
}


void *consumer(void *arg)
{
	int c = 0;
	for(;;)
	{
		sem_wait(&sem2);
		printf("consumer %d\n",queue[c]);
		queue[c] = 0;
		sem_post(&sem1);
		c = (c+1)%NUM;
		sleep(rand()%5);
	}
}
