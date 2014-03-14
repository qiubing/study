/*user space sending message */
#include <sys/socket.h>
#include <linux/netlink.h>

#define MAX_MSGSIZE 1024

int main(int argc,char **argv)
{
	/*create a socket*/
	int fd = socket(AF_NETLINK,SOCK_RAW,NETLINK_GENERIC);
	/*bind the socket with socketaddr_nl */
	struct sockaddr_nl nladdr;
	nladdr.nl_family = AF_NETLINK;
	nladdr.nl_pad = 0;
	nladdr.nl_pid = get_pid();//get the process id
	nladdr.nl_groups = 0;

	bind(fd,(struct sockaddr*)&nladdr,sizeof(struct sockaddr_nl));

	/*use the sendmsg() send the message*/
	struct msghdr msg;
	memset(&msg,0,sizeof(msg));
	msg.msg_name = (void *)&(nladdr);
	msg.msg_namelen = sizeof(nladdr);
	
	char buffer[] = "an example message";
	struct nlmsghdr nlhdr;
	nlhdr = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_SIZE));
	strcpy(NLMSG_DATA(nlhdr),buffer);
	nlhdr->nlmsg_len = NLMSG_LENGTH(strlen(buffer));
	nlhdr->nlmsg_pid = getpid();
	nlhdr->nlmsg_flags = 0;

	struct iovec iov;
	iov.iov_base = (void*)nlhdr;
	iov.iov_len = nlh->nlmsg_len;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;

	int n = sendmsg(fd,&msg,0);



	return 0;
}

