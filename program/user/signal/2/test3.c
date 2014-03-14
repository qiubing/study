#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>


void my_func(int signo)
{
	printf("if you want to quit,please try SIGQUIT\n");
}

int main(void)
{
	sigset_t set,pendset;
	struct sigaction action1,action2;

	if(sigemptyset(&set)<0)
	{
		perror("sigemptyset");
		exit(1);
	}

	if(sigaddset(&set,SIGQUIT)<0)
	{
	
		perror("sigaddset");
		exit(1);
	}

	if(sigaddset(&set,SIGINT)<0)
	{
		printf("sigaddset");
		exit(1);
	}

	if(sigismember(&set,SIGINT))
	{
		sigemptyset(&action1.sa_mask);
		action1.sa_handler = my_func;
		action1.sa_flags = 0;
		sigaction(SIGINT,&action1,0);
	}
	if(sigismember(&set,SIGINT))
	{
		sigemptyset(&action2.sa_mask);
		action2.sa_handler = SIG_DFL;
		action2.sa_flags = 0;
		sigaction(SIGQUIT,&action2,0);
	}

	if(sigprocmask(SIG_BLOCK,&set,NULL)<0)
	{
		perror("sigpromask");
		exit(1);
	}else
	{
		printf("Signal set was blocked.press any key!\n");
		getchar();
	}
	if(sigprocmask(SIG_UNBLOCK,&set,NULL)<0)
	{
		perror("sigprocmask");
		exit(1);
	}else
	{
		printf("signal set is unblock state \n");
	}

	while(1)
	{
	}
	exit(0);

}
