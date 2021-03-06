#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>
#define THREAD_MAX  3
#define REPEAT_TIMES 5
#define DELAY 4

sem_t sem[THREAD_MAX];

void *thr_fn(void *);

int main(void)
{
	pthread_t tid[THREAD_MAX];
	int err;
	int i;
	void *retv;

	srand((int)time(0));
	
	for(i = 0;i < THREAD_MAX-1 ;i++)
	{
		sem_init(&sem[i],0,0);
	}

	sem_init(&sem[2],0,1);


	for(i = 0;i < THREAD_MAX;i++)
	{
		if((err = pthread_create(&tid[i],NULL,thr_fn,(void *)i)) != 0)
		{
			perror("pthread_create");
		}else
		{
			printf("thread %d create success\n",i);
		}
	}

	for(i = 0;i < THREAD_MAX;i++)
	{
		if((err = pthread_join(tid[i],&retv)) != 0)
		{
			perror("pthread_join");
		}else
		{
			printf("thread %d join success\n",i);
		}
	}

	for(i = 0;i < THREAD_MAX;i++)
	{
		sem_destroy(&sem[i]);
	}

	return 0;
}

void *thr_fn(void *arg)
{
	int thr_num = (void *)arg;
	int delay_time = 0 ;
	int count ;
	sem_wait(&sem[thr_num]);

	printf("thread %d is starting\n",thr_num);
	for(count = 0;count < REPEAT_TIMES;count++)
	{
		delay_time = (int)(DELAY*(rand()/(double)RAND_MAX))+1;
		sleep(delay_time);
		printf("thread %d :job %d delay = %d\n",thr_num,count,delay_time);
	}
	printf("thread %d is exiting \n",thr_num);
	sem_post(&sem[(thr_num+THREAD_MAX-1)%THREAD_MAX]);
	pthread_exit(NULL);
	
}
