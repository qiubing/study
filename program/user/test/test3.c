/*
 * this program is for callback fuction
 * */
#include <stdio.h>

void printwelcome(int len)
{
	printf("welcome to %d\n",len);
}

void printgoodbye(int len)
{
	printf("goodbye %d\n",len);
}

void callback(int times,void(*print)(int))
{
	int i;
	for(i = 0; i < times; ++i)
	print(i);
	printf("I don't know welcome or goodbye to you\n");
}

int main(int agrc,char **argv)
{
	callback(10,printwelcome);
	callback(10,printgoodbye);
	return 0;

}
	
