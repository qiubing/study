/*this program is use for the father and child process communication with pipe*/

#include <unistd.h> //pipe()
#include <stdlib.h>
#include <stdio.h>

#define MAXLINE 80

int main()
{
	char buffer[MAXLINE];
	int pid;
	int fd[2];
	int n;
	/*create a pipe*/
	if(pipe(fd) < 0)
	{
		printf("create pipe error\n");
		exit(1);
	}

	/*fork*/
	if((pid = fork())<0)
	{
		printf("fork error\n");
		exit(1);
	}
	if(pid > 0)/*the parent*/
	{
		close(fd[0]);//close the parent read end
		write(fd[1],"hello,world\n",12);//write the data to the pipe  
	}else/*child*/
	{
		close(fd[1]);//close the child write end
		n =read(fd[0],buffer,MAXLINE);//read the data from the pipe 
		 write(STDOUT_FILENO,buffer,n);//output to the standard output

	}

	return 0;

}

