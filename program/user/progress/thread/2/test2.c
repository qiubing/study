#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

#define MAXSTACK 100

int stack[MAXSTACK][2];
int size = 0;
sem_t sem;

void ReadData1(void){
	FILE *fp = fopen("test1.c","r");
	while(!feof(fp)){
		fscanf(fp,"%d,%d",&stack[size][0],&stack[size][1]);
		sem_post(&sem);
		++size;
	}
	fclose(fp);
}

void ReadData2(void){
	FILE *fp = fopen("/home/bing/core","r");
	while(!feof(fp)){
		fscanf(fp,"%d,%d",&stack[size][0],&stack[size][1]);
		sem_post(&sem);
		++size;
	}
	fclose(fp);
}
void HandleData1(void)
{
	while(1){
		sem_wait(&sem);
		printf("plus:%d + %d =%d\n",stack[size][0],stack[size][1],stack[size][0]+stack[size][1]);
		--size;
	}
}

void HandleData2(void)
{
	while(1){
		sem_wait(&sem);
		printf("Mutiply:%d*%d = %d\n",stack[size][0],stack[size][1],stack[size][0]*stack[size][1]);
		--size;
	}
}

int main(void)
{
	pthread_t t1,t2,t3,t4;
	sem_init(&sem,0,0);
	pthread_create(&t1,NULL,(void *)HandleData1,NULL);
	pthread_create(&t2,NULL,(void *)HandleData2,NULL);
	pthread_create(&t3,NULL,(void *)ReadData1,NULL);
	pthread_create(&t4,NULL,(void *)ReadData2,NULL);
	pthread_join(t1,NULL);
}
