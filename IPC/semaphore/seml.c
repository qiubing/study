/*this program is about how the semaphore work */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/sem.h> // semget(),semctl(),semops()

/*the fourth argurement*/
union semun
{
	int val;// for SETVAL
	struct semid_ds *buf;//every sem have a struct semid_ds
	unsigned short *arry;//for GETALL and SETALL 
};

static int sem_id = 0;
static int set_semvalue();//set the sem value
static void del_semvalue();//delete a semvalue
static int semaphore_p();
static int semaphore_v();


int main(int argc,char **argv)
{
	char message = 'X';
	int i = 0;
	/*create a semaphore */

	sem_id = semget((key_t)1234,1,0666|IPC_CREAT);
	if(sem_id  == -1)
	{
		fprintf(stderr,"create a semaphore failed\n",errno);
		exit(1);
	}
	if(argc > 1)
	{
		/*if the program is first called,then initiate the semaphore*/
		if(!set_semvalue())
		{
			fprintf(stderr,"failed to initialize semaphore\n",errno);
			exit(1);
		}

		/*set up the message output message,that is the first argument*/
		message = argv[1][0];
		sleep(2);
	}

	for(i = 0; i < 10; ++i)
	{
		/*access to the critical region */
		/*the critical zone is between the semaphore_p() and semaphore_v() */
		if(!semaphore_p())
		{
			printf("semaphore_p failed\n");
			exit(1);
		}
		printf("%c",message);

		/*clean the buffer zone and sleep at random time*/
		fflush(stdout);
		sleep(rand()%3);

		/*before leave the critical zone,output the data to screen*/
		printf("%c",message);
		fflush(stdout);

		/*leave the critical zone and sleep random time then continue loop*/
		if(!semaphore_v())
		{
			printf("semaphore_v failed\n");
			exit(1);
		}
		sleep(rand()%2);
	}

	sleep(10);
	printf("process %d finished\n",getpid());

	if(argc > 1)
	{
		/*if the program is first called, then delete the semaphore*/
		sleep(3);
		del_semvalue();
	}

	return 0;

}


static int set_semvalue()
{
	/*use to initialize the semaphore,must be done before use the semaphore*/
	union semun sem_union;
	sem_union.val = 1;
	if(semctl(sem_id,0,SETVAL,sem_union) == -1)
		return 0;
	return 1;
}

static void del_semvalue()
{
	/*delete the semaphore*/
	union semun sem_union;
	if(semctl(sem_id,0,IPC_RMID,sem_union) == -1)
	{
		fprintf(stderr,"failed to delete semphore\n");
	}
}


static int semaphore_p()
{
	/*sub semaphore by 1,that is P(SV)*/
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = -1;// -1 operator
	sem_b.sem_flg = SEM_UNDO;

	if(semop(sem_id,&sem_b,1) == -1)
	{
		fprintf(stderr,"semaphore_p failed\n");
		return 0;
	}
	return 1;
}

static int semaphore_v()
{
	/*add semaphore by 1,make the semaphore can be used,that is V(sv)*/
	struct  sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = 1;//+1 operator
	sem_b.sem_flg = SEM_UNDO;
	if(semop(sem_id,&sem_b,1) == -1)
	{
		fprintf(stderr,"semphore_v failed \n");
		return 0;
	}
	return 1;

}

