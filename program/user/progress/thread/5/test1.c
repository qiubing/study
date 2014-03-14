#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thr_fn1(void *arg)
{
	printf("thread 1 %lu is returning\n",pthread_self());
	return (void *)1;
}

void *thr_fn2(void *arg)
{
	printf("thread 2 %lu exiting\n",pthread_self());
	pthread_exit((void *)2);
}

void *thr_fn3(void *arg)
{
	while(1)
	{
		printf("thread 3 %lu writing\n",pthread_self());
		sleep(1);
	}
}


int main(void)
{
	pthread_t tid;
	void *tret;
	int err;

	if((err = pthread_create(&tid,NULL,thr_fn1,NULL)) != 0)
	{
		printf("create thread error!\n");
		exit(0);
	}

	pthread_join(tid,&tret);
	printf("thread 1 exit code %d\n",(int)tret);

	pthread_create(&tid,NULL,thr_fn2,NULL);
	pthread_join(tid,&tret);
	printf("thread 2 exit code %d\n",(int)tret);

	pthread_create(&tid,NULL,thr_fn3,NULL);
	//pthread_detach(tid);
	sleep(3);
	pthread_cancel(tid);
	if((err = pthread_join(tid,&tret)) != 0)
	{
		printf("pthread_join error\n");
		exit(1);
	}
	printf("thread 3 exit code %d\n",(int)tret);

	return 0;
}
