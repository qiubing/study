#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>



void daemonize(void)
{
	pid_t pid;

	if((pid = fork())<0)
	{
		perror("fork");
		exit(1);
	}else if(pid != 0)
	{/*parent*/
		exit(0);
	}
	setsid();

	if((chdir("/")) < 0)
	{
		perror("chdir");
		exit(1);
	}
	umask(0);

	open("/dev/null",O_RDWR);
	dup2(0,1);
	dup2(0,2);
}


int main(void)
{
	time_t t;
	int fd;
	daemonize();
	while(1)
	{
		fd = open("daemon.log",O_WRONLY|O_CREAT|O_APPEND,0644);
		if( fd < 0)
		{
			perror("open");
			exit(1);
		}
		t = time(0);
		char *buf = asctime(localtime(&t));
		write(fd,buf,strlen(buf));
		close(fd);
		sleep(30);
	}
	return 0;
}
