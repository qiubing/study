#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	printf("fork!");
	if((pid = fork())<0){
		printf("fork error\n");
	}else if(pid >0)
	{
		printf("parent id is %d\n",getpid());
	}else
	{
		printf("child id is %d\n",getpid());
	}
	return 0;
}
