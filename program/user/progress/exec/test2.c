#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char **argv)
{
	pid_t pid;
	char *const env[]={"yes","are","right",NULL};
	char *const ps_argv[]={"ps","-o","pid,ppid,session,comm",NULL};
	char *const ps_env[]={"PATH=/bin:/usr/bin","TERM=console",NULL};
	

	if((pid = fork())<0)
	{
		perror("fork");
		exit(0);
	}else if(pid > 0)/*parent*/
	{
		sleep(2);
		execv("/bin/ps",ps_argv);
	}else /*child*/
	{
		execle("/home/bing/program/user/progress/exec/hello","print","the","environment","parameter",NULL,ps_env);
//		printf("TERM=%s\n",getenv("TERM"));
//		printf("PATH=%s\n",getenv("PATH"));
	}
	//execv("/bin/ps",ps_argv);
	//execle("/bin/ls","-al",NULL,ps_env);
	//execve("/bin/ps",ps_argv,ps_env);
	//execlp("ps","ps","-o","pid,ppid,session,comm",NULL);
	//`execvp("ps",ps_argv);
	/*
	if(argc<3)
	{
		printf("please input more than 3 parameter\n");
		exit(0);
	}*/
//	execlp("/home/bing/program/user/progress/exec/hello",argv[1],argv[2],argv[3],NULL);
//	perror("execlp");
//	execv("/home/bing/program/user/progress/exec/hello",env);
//	perror("execv ");
	return 0;
}
