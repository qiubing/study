#include <sys/socket.h>
#include <linux/netlink.h>

#define MAX_NL_MSG_LEN 1024


int main (int argc, char **argv)
{
	struct sockaddr_nl nladdr;
	struct msghdr msg;
	struct iovec iov;
	struct nlmsghdr *nlhdr;

	nlhdr = (struct nlmsghdr *)malloc(MAX_NL_MSG_LEN);

	iov.iov_base = (void *)nlhdr;
	iov.iov_len = MAX_NL_MSG_LEN;
	msg.msg_name = (void *)&(nladdr);
	msg.msg_namelen = sizeof(nladdr);
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	/*create a socket*/
	int fd = socket(AF_NETLINK,SOCK_RAW,NETLINK_GENERIC);

	bind()
    /*recvmsg()*/
	recvmsg(fd,&msg,0);

	return 0;
}
