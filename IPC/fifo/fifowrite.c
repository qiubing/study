/*create a fifo and write data to the fifo*/

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
	int pipe_fd, data_fd;
	int res = 0;
	const int open_mode = O_WRONLY;
	int nsent = 0;
	char buffer[PIPE_BUF+1];

	//if the fifo file exist 
	if(access(fifo_name,F_OK) == -1)
	{
		res = mkfifo(fifo_name,0777);//there is no fifo_name,so create it
		if(res != 0)
		{
			fprintf(stderr,"could not create fifo%s\n",fifo_name);
			exit(1);
		}
	}

	printf("process %d opening FIFO O_WRONLY\n",getpid());
	//open the FIFO file with BLOCK,and read the data file only
	pipe_fd = open(fifo_name,open_mode);
	data_fd = open("data.txt",O_RDONLY);

	printf("process %d result %d\n",getpid(),pipe_fd);

	if(pipe_fd != -1)
	{
		int nread = 0;
		nread = read(data_fd,buffer,PIPE_BUF);
		buffer[nread] = '\0';

		while(nread > 0)
		{
			//write data to the FIFO

			res = write(pipe_fd,buffer,nread);
			if(res == -1)
			{
				fprintf(stderr,"write error on pipe\n");
				exit(1);
			}
			nsent += res;// add the bytes write
			nread = read(data_fd,buffer,PIPE_BUF);
			buffer[nread] = '\0';
		}
		close(pipe_fd);
		close(data_fd);
	}else
		exit(1);

	printf("process %d finished\n",getpid());
	return 0;
}
