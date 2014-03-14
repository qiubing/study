#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


void my_func(int signo)
{
	if(signo == SIGINT)
	{
		printf("I have get SIGINT\n");
	}else if(signo ==SIGQUIT )
	{
		printf("I have get SIGQUIT\n");
	}
}

int main(void)
{
	printf("waiting for signal SIGINT or SIGQUIT...\n");
	signal(SIGINT,my_func);
	signal(SIGQUIT,my_func);
	raise(SIGINT);
	pause();
	return 0;
}


