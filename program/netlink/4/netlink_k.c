/*netlink kernel program*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/time.h>
#include <linux/types.h>
#include <net/sock.h>
//#include <linux/netlink.h>
#include <net/netlink.h> //it include linux/netlink.h

#define NETLINK_TEST 23
#define MAX_MSGSIZE 1024

/*define the netlink socket */
struct sock *nl_sk =NULL;

/*get the string length*/

int stringlength(char *s)
{
	int slen = 0;
	for(;*s;s++)
		slen++;

	return slen;
}

//send message by netlink

void sendnlmsg(char *message)
{
	struct sk_buff *skb;
	struct nlmsghdr *nlh;
	int len = NLMSG_SPACE(MAX_MSGSIZE);
	int slen = 0;

	if(!message ||!nl_sk)
	{
		return ;
	}

	// Allocate a new sk_buffer
	
	skb = alloc_skb(len,GFP_KERNEL);
	if(!skb){
		printk(KERN_ERR"my netlink: alloc_skb Error.\n");
		return ;
	}

	slen = stringlength(message);

	//Initiate the header of the netlink message
	
	nlh = nlmsg_put(skb,0,0,0,slen,0);
	NETLINK_CB(skb).pid = 0;//from kernel
	NETLINK_CB(skb).dst_group = 1; // multi_cast .0 is for unicast

	//message[slen] = '\0';
	memcpy(NLMSG_DATA(nlh),message,slen);
	printk("my netlink:send message '%s'\n",(char *)NLMSG_DATA(nlh));

	//send message by mutil cast
	netlink_broadcast(nl_sk,skb,0,1,GFP_KERNEL);
	return;

}


//Initialize netlink

static int  __init  netlink_init(void)
{
	int i = 10;
	struct completion cmp1;
	nl_sk = netlink_kernel_create(&init_net, NETLINK_TEST,1,NULL,NULL,THIS_MODULE);
	

	if(nl_sk == NULL)
	{
		printk(KERN_ERR"%s:my netlink:create netlink socket error\n",__FUNCTION__);
		return 1;
	}

	printk("my netlink:create netlink socket ok\n");

	while(i--)
	{
		init_completion(&cmp1);
		wait_for_completion_timeout(&cmp1,3*HZ);
		sendnlmsg("I am from kernel!");

	}
	return 0;

}

static void __exit netlink_exit(void)
{
	if(nl_sk != NULL)
	{
		sock_release(nl_sk->sk_socket);
	}

	printk("my netlink: self module exited\n");

}

module_init(netlink_init);
module_exit(netlink_exit);
MODULE_AUTHOR("qiubing");
MODULE_LICENSE("GPL");

