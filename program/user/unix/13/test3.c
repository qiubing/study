#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


void daemonize(void)
{
	pid_t pid,n;
	int fd;

	if((pid = fork())<0)
	{
		perror("fork");
		exit(1);
	}else if( pid != 0)   /*parent*/
		exit(0);
	if ((n = setsid())<0)
	{
		perror("setsid");
		exit(1);
	}
	printf("session id is %d\n",(int)n);

	if(chdir("/")<0)
	{
		perror("chdir");
		exit(1);
	}

	/*
	 * change the current working directory to the root
	 */
	close(0);
	fd = open("/dev/null",O_RDWR);
	printf("open /dev/null fd is %d\n",fd);
	fd = dup2(0,1);
	printf(" fd is %d\n",fd);
	dup2(0,2);
	printf(" return fd is %d\n",fd);
}


int main(void)
{
	daemonize();
	while(1);
}
