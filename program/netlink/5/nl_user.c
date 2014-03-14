/*send message to kernel and receive message from kernel*/

#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <asm/types.h>
#include <linux/netlink.h>
#include <linux/socket.h>
#include <errno.h>

#define NETLINK_MYTEST 22
#define MAX_MSGSIZE 1024

int main(int argc,char **argv)
{
    char buffer[] = "hello world";
	//char buffer[] = "exit";
	
	int ns,nr;
	/*send message to kernel*/
	//create socket
	struct sockaddr_nl srcaddr,dstaddr;
	int err;
	int sock_fd = socket(AF_NETLINK,SOCK_RAW,NETLINK_MYTEST);
	if(sock_fd < 0)
	{
		printf("create socket error\n");
		return -1;
	}

	//initiate netlink socket address
	memset(&srcaddr,0,sizeof(srcaddr));
	srcaddr.nl_family = AF_NETLINK;
	srcaddr.nl_pid = getpid();//use the process pid as the identifier
	srcaddr.nl_groups = 0;

	// bind the socket and address
	err = bind(sock_fd,(struct sockaddr*)&srcaddr,sizeof(srcaddr));
	if(err<0)
	{
		printf("bind failed\n");
		close(sock_fd);
		return -1;
	}

	/*send message to kernel*/
	//prepare the struct to carry the data
	struct msghdr msg;
	struct iovec iov;
	struct nlmsghdr *nlhdr = NULL;
	
	// initiate the destination address
	memset(&dstaddr,0,sizeof(dstaddr));
	dstaddr.nl_family = AF_NETLINK;
	dstaddr.nl_pid = 0;//0 represent the kernel
	dstaddr.nl_groups = 0;//unicast
	memset(&msg,0,sizeof(msg));
	msg.msg_name = (void *)&dstaddr;
	msg.msg_namelen = sizeof(dstaddr);
	nlhdr = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_MSGSIZE));
	nlhdr->nlmsg_len = NLMSG_SPACE(MAX_MSGSIZE);
	nlhdr->nlmsg_pid = getpid();//the source pid send the message
	nlhdr->nlmsg_flags = 0;
	strcpy((char *)NLMSG_DATA(nlhdr),buffer);

	iov.iov_base = (void *)nlhdr;
	iov.iov_len = nlhdr->nlmsg_len;
	msg.msg_iov = &iov;
	msg.msg_iovlen =1;

	//send the message 
	
	printf("start to send message\n");
	sendmsg(sock_fd,&msg,0);
	printf("sending finished \n");

	
	/*recv message from kernel*/
	//prepare the buffer to hold the data from the kernel

/*	
	struct sockaddr_nl nladdr;//store the source address
	struct msghdr msg1;
	struct iovec iov1;
	struct nlmsghdr *nlhdr1;
	nlhdr1 = (struct nlmsghdr *)malloc(MAX_MSGSIZE);
	if(!nlhdr1)
	{
		printf("malloc nlmsghdr error\n");
		close(sock_fd);
		return -1;
	}
	memset(&nladdr,0,sizeof(nladdr));
	iov1.iov_base = (void *)nlhdr1;
	iov1.iov_len = MAX_MSGSIZE;
	msg1.msg_name = (void *)&(nladdr);
	msg1.msg_namelen = sizeof(nladdr);
	msg1.msg_iov = &iov;
	msg1.msg_iovlen = 1;

	memset(nlhdr1,0,MAX_MSGSIZE);

	//use the recvmsg() recv the message
	
	while(1)
	{
		nr = recvmsg(sock_fd,&msg1,0);
	    if(nr < 0)
	    {
		printf("recv message from kernel error\n");
		return -1;
      	}

//	char *string;
//	string = (char *)NLMSG_DATA(nlhdr1);

	   printf("the message recived:%s\n",(char *)NLMSG_DATA(nlhdr1));
	}

	*/
    

	memset(nlhdr,0,NLMSG_SPACE(MAX_MSGSIZE));
	printf("waiting received!\n");

	while(1)
	{	nr = recvmsg(sock_fd,&msg,0);
		if(nr < 0)
		{
			printf("state");
		}
		printf("received message:%s\n",(char*)NLMSG_DATA(nlhdr));
	}
	
	close(sock_fd);

	return 0;
}
