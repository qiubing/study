/*write data to the shared memory*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h>
#include "shmdata.h"

int main()
{
	int shmid;
	void *shm = NULL;//share memory address
	struct shared_use_st *shared = NULL;
	char buffer[BUFSIZ+1];
	int running = 1;
	/*create a shared memory*/
	shmid = shmget((key_t)1234,sizeof(struct shared_use_st),0666|IPC_CREAT);
	if(shmid == -1)
	{
		fprintf(stderr,"shmget failed\n",errno);
		exit(1);
	}

	/*connet the shared memory to the current address space*/

	shm = shmat(shmid,0,0);
	if(shm == (void *)-1)
	{
		fprintf(stderr,"shmat failed\n",errno);
		exit(1);
	}

	printf("attach shared memory at:%x\n",(int)shm);
	/*set up the shared memory*/
	shared = (struct shared_use_st *)shm;

	/*write data to the shared memory*/
	while(running)
	{
		while(shared->written == 1)//data have not been read yet,wait the data to be read and can not write the data to shared memory
		{
			sleep(1);
			printf("waiting...\n");
		}

		/*write data to the shared memory*/
		printf("enter some text:");
		fgets(buffer,BUFSIZ,stdin);
		strncpy(shared->text,buffer,TEXT_SZ);
		shared->written = 1;//write data finish,and enable read
		if(strncmp(buffer,"end",3) == 0)
			running = 0;//if input the "end" then exit the loop,that is stop write data to the shared memory
	
	}

	/*detach the shared memory from the current process*/
	if(shmdt(shm) == -1)
	{
		fprintf(stderr,"shmdt failed\n");
		exit(1);
	}

	sleep(2);
	return 0;
}
