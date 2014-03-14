#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

struct foo{
	int f_count;
	pthread_mutex_t f_lock;
};

struct foo* foo_alloc(void)
{
	struct foo *fp;
	if((fp = malloc(sizeof(struct foo))) != NULL){
		free(fp);
		return (NULL);
	}
	return (fp);
}

void foo_hold(struct foo *fp)
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);
}

void foo_rele(struct foo *fp)
{
	pthread_mutex_lock(&fp->f_lock);
	if(--fp->f_count == 0)
	{
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destory(&fp->f_lock);
	}else
	{
		pthread_mutex_unlock(&fp->f_lock);
	}
}

