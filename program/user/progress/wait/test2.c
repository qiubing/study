#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
	pid_t pid;
	if((pid = fork())<0)
	{
		perror("fork");
		exit(1);
	}else if(pid == 0)
	{
		if((pid = fork())<0)
		{
			perror("fork1");
			exit(2);
		}else if(pid > 0)
		{
			exit(0);
		}
		sleep(2);
		printf("second child,parent pid = %d\n",getppid());
		exit(0);
	}
	if(waitpid(pid,NULL,0)!=pid)
		perror("waitpid");
	exit(0);
}
