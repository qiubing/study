#include <stdio.h>

typedef void (*callback_t)(void*);//define function pointer

void repeat_three_times(callback_t f,void *p)
{
	f(p);
	f(p);
	f(p);
}


void say_hello(void *str)
{
	printf("Hello %s\n",(const char *)str);

}

void count_numbers(void *num)
{
	int i;
	for(i = 1; i<= (int)num; ++i)
	{
		printf("%d\n",i);
	}
}

int main(void)
{
	repeat_three_times(say_hello,"qiubing");
	repeat_three_times(count_numbers,(void*)4);
	return 0;
}
