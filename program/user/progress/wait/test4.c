#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pid_t pc,pr;
	pc = fork();
	if(pc < 0)
	{
		printf("fork error");
		exit(-1);
	}else if(pc == 0){
		sleep(10);
		return 0;
	}
	do{
		pr = waitpid(pc,NULL,WNOHANG);
		if(pr == 0){
			printf("No child exitd \n");
			sleep(1);
		}
	}while(pr == 0);
	if(pr == pc)
		printf("successfully get child %d\n",pr);
	else		
		printf("some error occured \n");
	return 0;
}
