/*this program is about the dup and pipe*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAXLINE  1024

int main()
{
	int pid;
	int fd[2];
	int n;
	char buffer[1024];
	/*create a pipe*/
	if(pipe(fd) < 0)
	{
		printf("create pipe failed\n");
		exit(1);
	}

	/*fork*/
	if((pid = fork()) < 0)
	{
		printf("fork error\n");
		exit(1);
	}
	if(pid >0)/*parent*/
	{
		close(0);//close the STDIN_FILENO
		dup2(fd[0],0);// the fd[0] is redirect to the STDIN_FILENO
		close(fd[1]);//close the pipe write end
	    execlp("wc","wc","-c",NULL);// wc -l
		//n = read(STDIN_FILENO,buffer,MAXLINE);
	}else /*child*/
	{
		close(1);//close the STDOUT_FILENO
		dup2(fd[1],1);// the fd[1] is redirect to the STDOUT_FILENO
		close(fd[0]); //close the pipe read end
		write(STDOUT_FILENO,"hello,world\n",12);
	   // execlp("ls","ls","-l",NULL);// ls -l
	}


	return 0;
}
