#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

pthread_t tid;

void *thr_fn(void *arg)
{
	printf("New process: PID:%d,TID:%lu\n",getpid(),pthread_self());
	printf("new process:PID:%d,TID:%lu\n",getpid(),tid);
	pthread_exit(0);

}



int main(void)
{
	int err;

	if((err = pthread_create(&tid,NULL,thr_fn,NULL)) !=0)
	{
		perror("pthread_create");
	}
	else
	{
		printf("thread %lu create sucess \n",tid);
	}

	printf("main process:PID:%d,TID:%lu\n",getpid(),pthread_self());
	sleep(1);

	return 0;

}

