/*read data from the pipe and write the data to the file*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

int main()
{
	const char *fifo_name = "/home/bing/display/fifo/my_fifo";
	int pipe_fd,data_fd;
	int res = 0;
	const int open_mode = O_RDONLY;
	char buffer[PIPE_BUF+1];
	int nread =0;
	int nwrite =0;
	memset(buffer,'\0',sizeof(buffer));

	printf("process %d opening FIFO O_RDONLY\n",getpid());
	//open the FIFO with the block mode and the write the data to the file
	
	pipe_fd = open(fifo_name,open_mode);
	
	data_fd = open("datafromFIFO.txt",O_WRONLY|O_CREAT,0644);
	
	printf("process %d result %d\n",getpid(),pipe_fd);
	if(pipe_fd != -1)
	{
		do
		{
			res = read(pipe_fd,buffer,PIPE_BUF);
			nwrite = write(data_fd,buffer,res);
			nread += res;
		}while(res > 0);
		close(pipe_fd);
		close(data_fd);
	}else
	{
		exit(1);
	}

	printf("process %d finished, %d bytes read\n",getpid(),nread);

	return 0;
}
