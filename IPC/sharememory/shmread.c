/*create a shared zone and read message*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <errno.h>
#include "shmdata.h"

int main()
{
	int running = 1;
	void *shm = NULL;
	int shmid;
	struct shared_use_st *shared;// pointer to the shared memory


	/*create a shared memory*/

	shmid = shmget((key_t)1234,sizeof(struct shared_use_st),0666|IPC_CREAT);
	if(shmid == -1)
	{
		fprintf(stderr,"shmget failed\n",errno);
		exit(1);

	}

	/*connect the shared memory to the current address space*/
	shm = shmat(shmid,0,0);
	if(shm == (void *)-1)
	{
		fprintf(stderr,"connect address space failed\n",errno);
		exit(1);
	}

	printf("memory attached at %x\n",(int)shm);

	/*set up the shared memory*/
	shared = (struct shared_use_st *)shm;
	shared->written = 0;//can write
	
	while(running)
	{
	

		if(shared->written != 0)
		{
			/*read data from the shared memory*/
			printf("read data from the shared memory:%s",shared->text);
			sleep(rand()%3);
			shared->written = 0;// read finish and set up the shared memory write
			if(strncmp(shared->text,"end",3) == 0)//input the "end",then quit the loop
			{
				running = 0;
			}

		}else
		{
			/*there is other process is writing, can not read now*/
			sleep(1);
		}
	}

		/*detach the shared memory from the current process*/
		if(shmdt(shm) == -1)
		{
			fprintf(stderr,"shmdt failed\n");
			exit(1);
		}
		/*delete the shared memory*/

		if(shmctl(shmid,IPC_RMID,0) == -1)
		{
			fprintf(stderr,"shmctl(IPC_RMID) failed\n");
		}

	return 0;
}
