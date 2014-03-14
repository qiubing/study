#include <stdio.h>
#include <stdlib.h> /*exit*/
#include <errno.h>

static void my_exit1(void);
static void my_exit2(void);

int  main(void)
{

	if((atexit(my_exit1)) != 0)
	{
		perror("atexit1");
		exit(-1);
	}else
		printf("my_exit1 funtion is register\n");
	if((atexit(my_exit2))!= 0)
	{
		perror("atexit2");
		exit(-1);
	}else
		printf("my_exit2 funtion is register\n");
	printf("hello,world\n");
	exit(0);
}

void my_exit1(void)
{
	printf("frist handle\n");
}

void my_exit2(void)
{
	printf("second handle \n");
}

