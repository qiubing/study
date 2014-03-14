#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int status;
	pid_t pc,pr;
	//pr = wait(NULL);
	pc = fork();
	if(pc<0)
	{
		printf("fork error\n");
		exit(0);
	}else if(pc == 0)
	{
		printf("This is child process with pid of %d\n",getpid());
		sleep(30);
		exit(3);
	}else{
		pr = wait(&status);
		if(WIFEXITED(status))
		{
			printf("The child process %d exit nomally\n",pr);
			printf("The WEXITSTATUS return code is %d\n",WEXITSTATUS(status));
			printf("The WIFEXITED return code is %d\n",WIFEXITED(status));
		}else{
			printf("The child process %d exit abnormally\n",pr);
			printf("Status is %d\n",status);
		}
		//sleep(20);
		//printf("I catched a child process with pid of %d\n",pr);
	}
	exit(0);
}
