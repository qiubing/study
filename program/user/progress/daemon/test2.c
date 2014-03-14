#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

int main(void)
{
	time_t t;
	int fd;
/*close 0,1,2 descriptor */
	if(daemon(0,0) == -1)
	{
		perror("daemon");
		exit(1);
	}

/*
	if(daemon(0,1) == -1)
	{
	
		perror("daemon");
		exit(1);
	}

*/
/*
	if(daemon(1,0) == -1)
	{
	
		perror("daemon");
		exit(1);
	}
*/
	while(1)
	{
		fd = open("daemon1.log",O_WRONLY|O_CREAT|O_APPEND,0644);
		if(fd < 0)
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
