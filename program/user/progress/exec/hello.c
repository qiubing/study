#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
	int i = 0;
	for(i = 0; i < argc;i++)
		printf("argv[i] is %s\n",argv[i]);
	printf("PATH=%s\n",getenv("PATH"));
	printf("PATH=%s\n",getenv("TERM"));

	return 0;
}
