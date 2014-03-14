#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond = PTHREAD_MUTEX_INITIALIZER;

struct node{
	int n_number;
	struct node *n_next;
}*head = NULL;

static void cleanup_handler(void *arg)
{
	printf("clean up handler if second thread \n");
	free(arg);
	pthread_mutex_unlock(&mutex);
}


static void *thr_fn(void *arg)
{
	struct node *p = NULL;
	pthread_cleanup_push(cleanup_handler,p);
	while(1)
	{
		pthread_mutex_lock(&mutex);
		while(head == NULL)
		{
			pthread_cond_wait(&cond,&mutex);
			p = head;
			printf("get %d from front of queue\n",p->n_number);
			free(p);
		}
		pthread_mutex_unlock(&mutex);
	}
	pthread_cleanup_pop(0);
	return 0;
}

int main(void)
{
	pthread_t tid;
	int i;
	struct node *p;
	int err;
	if((err = pthread_create(&tid,NULL,thr_fn,NULL)) !=0)
	{
		perror("pthread_create");
	}
	sleep(1);

	for(i = 0;i < 10;i++)
	{
		p = (struct node*)malloc(sizeof(struct node));
		p->n_number = i;
		pthread_mutex_lock(&mutex);
		p->n_next = head;
		head = p;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	printf("thread 1 want end the line,so cancel thread 2 \n");
	pthread_cancel(tid);
	pthread_join(tid,NULL);
	printf("ALL done --exiting\n");
	return 0;
}
