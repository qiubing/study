#include <stdio.h>
#include <stdlib.h>

void why_me(void)
{
	printf("this function is %s\n",__func__);
	printf("this file is %s\n",__FILE__);
	printf("this is line %d\n",__LINE__);
}

int main(void)
{
	printf("the file is %s\n",__FILE__);
	printf("the data is %s\n",__DATE__);
	printf("the time is %s\n",__TIME__);
	printf("this is line %d\n",__LINE__);
	printf("this function is %s\n",__func__);
	why_me();
	return 0;


}
