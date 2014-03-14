#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void *thr_fn1(void *arg)
{
	printf("thread 1 returning \n");
	printf("the conent is %s\n",arg);
	return ((void *)3);
}

void *thr_fn2(void *arg)
{
	printf("thread 2 exiting\n");
	pthread_exit((void *)4);
}

int main(void)
{
	int err;
	pthread_t tid1,tid2;
	void *tret;
	char str[]="hello world";

	err = pthread_create(&tid1,NULL,thr_fn1,str);
	if(err !=0)
	{
		perror("pthread_create");
	}
	 err = pthread_create(&tid2,NULL,thr_fn2,NULL);
	 if(err !=0)
	 {
		 perror("pthread_create");
	 }

	 err = pthread_join(tid1,&tret);
	 if(err != 0)
	 {
		 perror("pthread_join");
	 }

	 printf("thread 1 exit code %d\n",(int)tret);
	 err = pthread_join(tid2,&tret);

	 if(err !=0)
	 {
		 perror("pthread_join");
	 }
	 printf("thread 2 exit code %d\n",(int)tret);

	 exit(0);
}
