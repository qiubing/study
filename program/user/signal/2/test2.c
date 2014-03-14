#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void my_func(int signo)
{
	if(signo == SIGINT)
	{
		printf("I have get SIGINT\n");
	}else if(signo ==SIGQUIT)
	{
		printf("I have get SIGQUIT\n");
	}
}

int main(void)
{
	struct sigaction action;
	printf("waiting for signal SIGINT or SIGQUIT...\n");
	action.sa_handler = my_func;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(SIGINT,&action,0);
	sigaction(SIGQUIT,&action,0);
	pause();
	exit(0);


}


