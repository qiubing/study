/*print the shared memory address space*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h>

#define ARRAY_SIZE 40000
#define MALLOC_SIZE 100000
#define SHM_SIZE 100000
#define SHM_MODE 0600 //user read/write

char array[ARRAY_SIZE];//uninitialized data = bss

int main()
{
	int shmid;
	void *shm;
	char *ptr;
	/*create a shared memory*/

	printf("array[]from %lx to the %lx\n",(unsigned long)&array[0],(unsigned  long)&array[ARRAY_SIZE]);
	printf("stack around %lx\n",(unsigned long)&shmid);
	if((ptr = malloc(MALLOC_SIZE)) == NULL)
	{
		fprintf(stderr,"malloc error\n",errno);
	}
	printf("malloced from %lx to %lx\n",(unsigned long)ptr,(unsigned long)ptr+MALLOC_SIZE);

	shmid = shmget(IPC_PRIVATE,SHM_SIZE,SHM_MODE);
	if(shmid == -1)
	{
		fprintf(stderr,"shmget failed\n",errno);
		exit(1);
	}
	/*attach the shared memory to the process address*/
	shm = shmat(shmid,0,0);
	if(shm == (void *)-1)
	{
		fprintf(stderr,"shmat failed\n",errno);
		exit(1);
	}

	printf("shared address from %lx to %lx\n",(unsigned long)shm,(unsigned long)shm+SHM_SIZE);

	/*delete the shared memory*/

	if(shmctl(shmid,IPC_RMID,0) == -1)
	{
		fprintf(stderr,"shmctl failed\n",errno);
	}

	return 0;
}
