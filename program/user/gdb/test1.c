#include <stdio.h>

int main(void)
{
	int sum = 0, i = 0;
	char input[5];
	
		scanf("%s",input);
		for(i = 0;input[i] !='\0';i++){
			if(input[i]<'0'||input[i]>'9'){
				printf("Invaild input!\n");
				sum = -1;
				break;
			}
		sum = sum*10 + input[1] - '\0';
		}
		printf("input=%d\n",sum);
	return 0;

}

