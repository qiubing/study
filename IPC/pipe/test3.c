/*the popen() and pclose() function*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
	FILE *read_fp = NULL;
	FILE *write_fp = NULL;
	int nread = 0;
	char buf[BUFSIZ +1];
	memset(buf,'\0',sizeof(buf));

	/*use popen() function execute the commond*/
	read_fp = popen("ls -l","r");//ls -l
	write_fp = popen("grep rwxrwxr-x","w");// grep rwxrwxr-x

	if(read_fp && write_fp)// both read_fp and write_fp is vaild
	{
		nread = fread(buf,sizeof(char),BUFSIZ,read_fp);//read a data block
		while(nread > 0)
		{
			buf[nread] = '\0';
			fwrite(buf,sizeof(char),nread,write_fp);//write the data to the grep process
			nread = fread(buf,sizeof(char),BUFSIZ,read_fp);// more data to read?
		}
		pclose(read_fp);
		pclose(write_fp);
	
	}

	return 0;
}
