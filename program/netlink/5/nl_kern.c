/*this program is use for receive message from the
 * userspace and send message back
 * */
#include <linux/netlink.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/types.h>
#include <net/sock.h>
#include <linux/time.h>
#include <linux/completion.h>
#include <net/netlink.h>


#define NETLINK_MYTEST 22
#define MAX_MSGSIZE 1024

struct sock *nl_sk=NULL;//netlink socket
struct sockaddr_nl src_addr,dst_addr;//netlink addr 
struct iovec iov;
struct msghdr msg;
int pid;
char buffer[1024];

int stringlen(char *string);
/*send the message to userspace and return the number send*/
int netlink_sendmsg(char *message)
{
	struct sk_buff *nl_skb = NULL;
	struct nlmsghdr *nl_hdr = NULL;
	int len = NLMSG_SPACE(MAX_MSGSIZE);
	int slen = 0;//message length
	if(!message || !nl_sk)
	{
		printk(KERN_ERR"no message or netlink socket create failed\n");
		return -1;
	}

	//allocate a skb buffer to the message
	 nl_skb = alloc_skb(len,GFP_KERNEL);
	 if(!nl_skb)
	 {
		 printk(KERN_ERR"allocate a skb buffer error\n");
		 return -1;
	 }
	 slen = stringlen(message);
	 //construct the netlink message header and input the header into the nl_skb
	 nl_hdr = nlmsg_put(nl_skb,0,0,0,slen,0);
	 
	 NETLINK_CB(nl_skb).pid = 0;
	 NETLINK_CB(nl_skb).dst_group = 1;
	 memcpy(NLMSG_DATA(nl_hdr),message,slen);//copy the message to the netlink message data portion

	 printk("my netlink :send message %s\n",(char*)NLMSG_DATA(nl_hdr));
	 // kernel netlink send message to userspace :unicast
     netlink_unicast(nl_sk,nl_skb,pid,0);
	 return slen;

}


/*recive message from the userspace and return the number recv*/
void netlink_recvmsg(struct sk_buff *skb)
{
	struct sk_buff *skb1;
	struct nlmsghdr *nlh;
	char str[100];
	
	skb1 = skb_get(skb);
	
	if(skb1->len >= NLMSG_SPACE(0))
	{
		//get the netlink message header
		nlh = nlmsg_hdr(skb);
		int i = 10;

		//copy the netlink message data to string array
		memcpy(str,NLMSG_DATA(nlh),sizeof(str));
		printk("message recevied:%s\n",str);
		//pid = nlh->nlmsg_pid;//the source address ,it use for send back to the applicaiton

		// h stands for hello message and return back
		if(str[0] == 'h')
		{
			pid = nlh->nlmsg_pid;
			// send the message to the userspace application
			while(i--)
			{
			 netlink_sendmsg("I am from kernel!");
			}
		}
		else if(str[0] == 'e');
		{
			pid = 0;
		}
		kfree_skb(skb1);
	}
}



int stringlen( char *string)
{
	int length = 0;
	for(;*string;string++)
		length += 1;
	return length;
}



// initiatize the netlink module 
static int __init netlink_init(void)
{
	// create netlink kernel socket 
	nl_sk=netlink_kernel_create(&init_net,NETLINK_MYTEST,0,netlink_recvmsg,NULL,THIS_MODULE);
	if(nl_sk == NULL)
	{
		printk(KERN_ERR"Error from %s:netlink:create error\n",__FUNCTION__);
		return 1;
	}

	printk("%s:netlink create success\n",__FUNCTION__);

	return 0;
}

static void __exit netlink_exit(void)
{
	
	if(nl_sk != NULL)
	{
		printk("%s:netlink:exit the module\n",__FUNCTION__);
		sock_release(nl_sk->sk_socket);
	}
	
}

module_init(netlink_init);
module_exit(netlink_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("qiubing");

