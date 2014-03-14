#include <stdio.h>
#include <unistd.h>
#include <errno.h>


int main(int argc, char **argv)
{
	pid_t pid;
	int count = 0;
	if((pid = fork())<0)
	{
		perror("fork");
	}else if(pid == 0){

		printf("I am the child process,my process id is %d father id is %d\n",getpid(),getppid());
		printf("I am the son of my dad\n");
		count++;
	}else{
		sleep(5);
		printf("I am the parent progress,my process id is %d\n",getpid());
		printf("I am the father of my son\n");
		count++;
	}

	printf("count = %d\n",count);
	return 0;
}
