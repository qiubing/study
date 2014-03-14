// my callback function
#include <stdio.h>

typedef void (*call_back_t)(void *);//define a callback function

void func1(call_back_t f, void *p)
{
		f(p);
}

void printhello(void *p)
{
	printf("hello %s\n",(const char*)p);
}

void countnum(void *num)
{
	//int sum =0;
	//for(int i = 0; i <= (int)num; i++)
	//	sum + = i;
	printf("the sum is: %d\n",(int)num);

}

int main()
{
	func1(printhello,"qiubing");
	func1(countnum,(void*)10);
	return 0;
}
