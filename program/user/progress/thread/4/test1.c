#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int tmp;

void *thr_fn(void *arg);

int main(void)
{
	pthread_t tid;
	int err;

	tmp = 3;
	if((err = pthread_create(&tid,NULL,thr_fn,NULL)) != 0)
	{
		perror("pthread_create");
	}else
	{
		printf("main thread is %lu\n",pthread_self());
	}
	printf("main tmp is %d\n",tmp);

	pthread_join(tid,NULL);

	pthread_mutex_destroy(&mutex);

	return 0;

}

void *thr_fn(void *arg)
{
	printf("thread is %lu\n",pthread_self());
	pthread_mutex_lock(&mutex);

	tmp = 12;
	printf("tmp now is %d\n",tmp);
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}
