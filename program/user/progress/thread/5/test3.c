#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

struct msg{
	struct msg *next;
	int num;
};

struct msg *head;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *producer(void *arg);
void *consumer(void *arg);

int main(void)
{
	pthread_t tid1,tid2;
	srand(time(NULL));
	pthread_create(&tid1,NULL,producer,NULL);
	pthread_create(&tid2,NULL,consumer,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	return 0;
}

void *producer(void *arg)
{
	struct msg *mp;
	for(;;){
		mp = malloc(sizeof(struct msg));
		mp->num = rand()%1000 + 1;
		printf("produce %d\n",mp->num);
		pthread_mutex_lock(&mutex);
		mp->next = head;
		head = mp;
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&cond);
		sleep(rand()%5);
	}
}


void *consumer(void *arg)
{
	struct msg *mp;
	for(;;)
	{
		pthread_mutex_lock(&mutex);
		while(head == NULL)
			pthread_cond_wait(&cond,&mutex);
		mp = head;
		head = mp->next;
		pthread_mutex_unlock(&mutex);
		printf("consume %d\n",mp->num);
		free(mp);
		sleep(rand()%5);
	}
}
