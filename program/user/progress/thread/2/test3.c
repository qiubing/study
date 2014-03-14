#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAX 10 
pthread_mutex_t mutex;
int num = 0;
pthread_t tid1,tid2;

void *thread1(void *argv)
{
	int i;
	printf("thread1:I am thread1\n");
	for(i = 0;i < MAX;i++)
	{
		printf("thread1:num is %d\n",num);
		pthread_mutex_lock(&mutex);
		num++;
		pthread_mutex_unlock(&mutex);
		sleep(2);
	}
	printf("thread1:I want to exit\n");
	pthread_exit(NULL);
}

void *thread2(void *argv)
{
	int j;
	printf("thread2:I am thread2\n");
	for(j = 0;j < MAX;j++);
	{
		printf("thread2:num is %d\n",num);
		pthread_mutex_lock(&mutex);
		num++;
		pthread_mutex_unlock(&mutex);
		sleep(2);
	}
	printf("thread2:I want to exit\n");
	pthread_exit(NULL);

}

void thread_exit(void)
	
{
	if(tid1 != 0){
	pthread_join(tid1,NULL);
	printf("thread 1 is end\n");
	}
	if(tid2 != 0){
		pthread_join(tid2,NULL);
		printf("thread 2 is end\n");
	}

}
int main(void)
{

	int err;
	pthread_mutex_init(&mutex,NULL);
	if(err = pthread_create(&tid1,NULL,thread1,NULL) !=0)
	{
		perror("pthread_create");
	}else
	{
		printf("thread1 create success\n");
	}
	if(err = pthread_create(&tid2,NULL,thread2,NULL) !=0)
	{
		perror("pthread_create");
	}else
	{
		printf("thread 2 create success\n");
	}

	thread_exit();
	return 0;

}
