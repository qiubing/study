#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void *thr_fn1(void *arg);
void *thr_fn2(void *arg);

pthread_t tid1,tid2;

int main(void)
{
	int err;
	void *retv;

	if((err = pthread_create(&tid1,NULL,thr_fn1,NULL)) != 0)
	{
		perror("pthread_create");
	}else
	{
		printf("thread1 create sucess \n");
	}

	if((err = pthread_create(&tid2,NULL,thr_fn2,NULL)) != 0)
	{
		perror("pthread_create");
	}else
	{
	
		printf("thread2 create success\n");
	}

	pthread_join(tid1,&retv);
	printf("thread1 exit with %d\n",(int *)retv);
	pthread_join(tid2,&retv);
	printf("thread2 exit with %d\n",(int *)retv);

	return 0;

}

void *thr_fn1(void *arg)
{
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	while(1)
	{
		printf("thread %lu is running!\n",pthread_self());
		sleep(1);
	}
//	printf("thread %lu exit \n",tid1);
//	printf("thread %lu create success\n",pthread_self());
	pthread_exit((void *)0);
}

void *thr_fn2(void *arg)
{
	printf("thread %lu is running!\n",pthread_self());
	sleep(5);
	if(pthread_cancel(tid1) == 0)
	{
		printf("send cancel command to thread1\n");
	}
//	printf("thread %lu exit \n",tid2);
//  printf("thread %lu create success\n",pthread_self());
	pthread_exit((void *)2);
}

	
