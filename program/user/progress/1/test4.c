#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int i = 0;
	printf("I son/par ppid pid pid\n");

	for(i = 0; i < 2; i++ ){
		pid_t pid = fork();
		if(pid == 0){
			printf("%d child %4d %4d %4d\n",i,getppid(),getpid(),pid);
		}else if(pid > 0)
		{
			printf("%d parent %4d %4d %4d\n",i,getppid(),getpid(),pid);
		}else
		{
			printf("fork error\n");
		}
	}
	return 0;
}
