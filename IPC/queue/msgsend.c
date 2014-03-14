/*send message program*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>

#define MAX_TEXT 512

/*define the message containor*/
struct msg_st
{
	long int msg_type;
	char text[MAX_TEXT];
};

int main()
{

	int msgid;
	int running = 1;
	char buffer[BUFSIZ];
	struct msg_st data;
	/*create a message queue*/

	msgid = msgget((key_t)1234,0666|IPC_CREAT);
	printf("the message queue ID is: %d\n",msgid);
	if(msgid == -1)
	{
		fprintf(stderr,"msgget failed\n",errno);
		exit(1);
	}

	/*write message to the queue,until meet the end*/
	while(running)
	{
		printf("Enter some text:");
		fgets(buffer,BUFSIZ,stdin);//input the message
		data.msg_type = 1;//message type is 1
		strcpy(data.text,buffer);

		//send message to the queue

		if(msgsnd(msgid,(void *)&data,MAX_TEXT,0) == -1)
		{
			fprintf(stderr,"msgsnd failed\n",errno);
			exit(1);
		}

		// input the end to finish the send process
		if(strncmp(buffer,"end",3) == 0)
			running = 0;

		sleep(1);

	}

	return 0;

}
