#include <stdio.h>
#include <stdlib.h>

int sort_function(const void *a, const void *b);
int list[5] = {23,45,21,76,34};

int main()
{
	int x;
	qsort((void*)list,5,sizeof(list[0]),sort_function);
	for(x = 0;x < 5; x++)
		printf("%d\n",list[x]);
	return 0;
}

int sort_function(const void *a, const void *b)
{
	return *(int*)a - *(int*)b;
}



