#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>



int g_Flag = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *thr_fn1(void *arg)
{
	printf("this is thread1\n");
	printf("this is thread1,g_Flag:%d,thread id is %u\n",g_Flag,(unsigned int)pthread_self());
	pthread_mutex_lock(&mutex);
	if(g_Flag == 2)
		pthread_cond_signal(&cond);
	g_Flag = 1;
	printf("this is thread1,g_Flag:%d,thread id is %u\n",g_Flag,(unsigned int)pthread_self());
	pthread_mutex_unlock(&mutex);
	pthread_join(*(pthread_t *)arg,NULL);
	pthread_exit(0);

}

void *thr_fn2(void *arg)
{
	printf("this is thread2\n");
	printf("this is thread2,g_Flag:%d,thread id is %u\n",g_Flag,(unsigned int)pthread_self());
	pthread_mutex_lock(&mutex);
	if(g_Flag == 1)
		pthread_cond_signal(&cond);
	g_Flag = 2;
	printf("this is thread2,g_Flag:%d,thread id is %u\n",g_Flag,(unsigned int)pthread_self());
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);

}



int main(void)
{
	printf("enter main\n");
	pthread_t tid1,tid2;
	int err;
	if((err = pthread_create(&tid2,NULL,thr_fn2,NULL)) != 0)
	{
		perror("pthread_create");
	}

	if((err = pthread_create(&tid1,NULL,thr_fn1,&tid2)) != 0)
	{
		perror("pthread_create");
	}

	pthread_cond_wait(&cond,&mutex);

	printf("leave main\n");

	
	exit(0);
}
