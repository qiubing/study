/*kernel send message to userspace*/

#include <linux/netlink>

void input(struct sock *sk,int len)
{
	struct sk_buff *skb;
	struct nlmsghdr *nlh = NULL;
	u8 *data = NULL;
	while((skb = skb_dequeue(&sk->receive_queue)) !=NULL)
	{
		nlh = (struct nlmsghdr *)skb->data;
		data = NLMSG_DATA(nlh);
	}
}

int main(int argc,char **argv)
{
	/*create a netlink socket in kernel*/
	struct sock *nl_sock;
	nl_sock = netlink_kernel_create(NETLINK_GENERIC,void (*input)(struct sock *sk,int len));

	NETLINK_CB(skb).pid = 0;
	NETLINK_CB(skb).dst_pid = 0;
	NETLINK_CB(skb).dst_group =0; 

	netlink_unicast(nl_sock,skb,pid,0);

	return 0;
}
