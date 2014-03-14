/*netlink user space program*/
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

#define NETLINK_TEST 23
#define MAX_PAYLOAD 1024 //maxinum payload size


int main(int argc, char **argv)
{
	struct sockaddr_nl src_addr,dest_addr;
	struct nlmsghdr *nlh =NULL;
	struct iovec iov;
	struct msghdr msg;
	int sock_fd, retval;

	// create a socket
	 sock_fd = socket(AF_NETLINK,SOCK_RAW,NETLINK_TEST);
	 if(sock_fd < 0)
	 {
		 printf("error getting socket:%s",strerror(errno));
		 return -1;
	 }

	 // to prepare binding
	 memset(&src_addr,0,sizeof(src_addr));
	 src_addr.nl_family = AF_NETLINK;
	 src_addr.nl_pid = getpid();//self pid
	 src_addr.nl_groups = 1; // mutil cast

	 //retval = bind(sock_fd, (struct sockaddr *)&src_addr,sizeof(src_addr));
	 retval = bind(sock_fd,(struct sockaddr*)&src_addr,sizeof(src_addr));
	 if(retval < 0){
		 printf("bind failed:%s",strerror(errno));
		 close(sock_fd);
		 return -1;
	 }
	 printf("bind success\n");

	 // to prepare recvmsg
	 nlh = (struct nlmsghdr*)malloc(NLMSG_SPACE(MAX_PAYLOAD));
	 if(!nlh)
	 {
		 printf("malloc nlmsghdr error\n");
		 close(sock_fd);
		 return -1;
	 }

	 memset(nlh,0,NLMSG_SPACE(MAX_PAYLOAD));
	 iov.iov_base = (void*)nlh;
	 iov.iov_len = NLMSG_SPACE(MAX_PAYLOAD);

	 memset(&msg,0,sizeof(msg));
	 memset(&dest_addr,0,sizeof(dest_addr));
	 msg.msg_name = (void *)&dest_addr;
	 msg.msg_namelen = sizeof(dest_addr);
	 msg.msg_iov = &iov;
	 msg.msg_iovlen = 1;

	 //read message form kernel
	 while(1)
	 {
		 printf("strat receive message\n");
		 recvmsg(sock_fd,&msg,0);
		 printf("receive message:%s\n",(char *)NLMSG_DATA(nlh));		 
	 }

	 close(sock_fd);

	 return 0;
}
