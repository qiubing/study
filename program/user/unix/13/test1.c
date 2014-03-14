#include "apue.h"
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>

void daemonize(const char *cmd)
{
	int i,fd0,fd1,fd2;
	pid_t pid;
	struct rlimit rl;
	struct sigaction sa;
	
	umask(0);

	if(getrlimit(RLIMIT_NOFILE,&rl)<0)

	{
		perror("getrlimit");
		exit(1);
	}

	if((pid = fork())<0)
	{
		perror("fork");
		exit(1);
	}else if(pid != 0)
	{
		exit(0);
	}

	setsid();

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if(sigaction(SIGHUP,&sa,NULL)<0)
	{
		perror("sigaction");
		exit(1);
	}

	if((pid = fork())<0)
	{
	 perror("fork");
	 exit(1);
	}else if(pid != 0)
	{
		exit(0);
	}


	if(chdir("/")<0)
	{
		perror("chdir");
		exit(1);
	}

	if(rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;

	for(i = 0;i <rl.rlim_max; i++)
		close(i);

	fd0 = open("/dev/null",O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	openlog(cmd,LOG_CONS,LOG_DAEMON);
	if(fd0 !=0 || fd1 != 1 || fd2 !=2)
	{
		syslog(LOG_ERR,"unexpected file descriptors %d %d %d",fd0,fd1,fd2);
		exit(1);
	}

}

int main(int argc,char **argv)
{
	if(argc != 2)
	{
		printf("please input a commond\n");
		exit(1);
	}
	printf("begin to call daemonize function\n");
	daemonize(argv[1]);
	printf("exit\n");
	return 0;
}
