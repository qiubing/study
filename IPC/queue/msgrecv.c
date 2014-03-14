/*receive message program*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h> //msgget(),msgsnd(),msgrcv(),msgctl()


/*define the send message struct */
struct msg_st
{
	long int msg_type;
	char text[BUFSIZ];
};

int main()
{
	int msgid;
	struct msg_st data;
	long int msgtype = 0;//be attention the msgtype == 0 is represent receive 
	//first message of queue.if the msgtype > 0,f.e, msgtype = 2,then the send message msgtype must
	//be 2 as well,otherwise can not received the message from the sender.
	int running = 1;


	/*create a message queue*/

	msgid = msgget((key_t)1234,0666|IPC_CREAT);
	printf("the message queue ID is:%d\n",msgid);
	if(msgid == -1)
	{
		fprintf(stderr,"msgget error\n",errno);
		exit(1);
	}

	/*get the message from the queue until meet the end*/
	while(running)
	{
		if(msgrcv(msgid,(void *)&data,BUFSIZ,msgtype,0) == -1)
		{
			fprintf(stderr,"msgrcv failed\n",errno);
			exit(1);
		}

		printf("receive data:%s\n",data.text);
		// meet the end

		if(strncmp(data.text,"end",3) == 0)
			running = 0;
	}

	// delete the message queue
	
	if(msgctl(msgid,IPC_RMID,0) == -1)
	{
		fprintf(stderr,"msgctl(IPC_RMID) failed \n",errno);
		exit(1);
	}

	return 0;
}
