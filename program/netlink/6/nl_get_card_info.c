/*this program is use for get the network card information from the kernel*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <linux/netdevice.h>
#include <net/if_arp.h>
#include <netinet/if_ether.h>
#include <netinet/ether.h>

#define MAX_MSGSIZE 1024
//request return message in the struct req
struct req{
	struct nlmsghdr nlhdr;//netlink message header
	struct ifinfomsg ifi;//device information

};

int main()
{
	/*define some data struct*/
	int sock_fd;
	struct sockaddr_nl srcaddr,dstaddr;
	int err;
	struct req reqdata;
	char buffer[MAX_MSGSIZE];
	int len,attrlen;
	struct nlmsghdr *hdr;
	struct ifinfomsg *ifimsg;
	struct rtattr *attr;
	struct ether_addr *ethaddr;
	struct net_device_stats *netstat;



	/*create a netlink socket*/
	sock_fd = socket(AF_NETLINK,SOCK_DGRAM,NETLINK_ROUTE);
	if(sock_fd < 0)
	{
		printf("create socket error\n");
		return -1;
	}


	/*bind the netlink socket with sockaddr_nl address*/
	//initiate the source address
	memset(&srcaddr,0,sizeof(srcaddr));
	srcaddr.nl_family = AF_NETLINK;
	srcaddr.nl_pid = getpid();//self pid
	srcaddr.nl_groups = 0;// unicast

	err = bind(sock_fd,(struct sockaddr *)&srcaddr,sizeof(srcaddr));
	if(err < 0)
	{
		printf("bind the socket error\n");
		return -1;
	}

	/*prepare the data to send to kernel*/
	memset(&reqdata,0,sizeof(reqdata));
	reqdata.nlhdr.nlmsg_len = NLMSG_LENGTH(sizeof(reqdata));
	reqdata.nlhdr.nlmsg_type = RTM_GETLINK;
	reqdata.nlhdr.nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;//request the kernel and dump the message
	reqdata.ifi.ifi_family = AF_UNSPEC;//network card family
	
	memset(&dstaddr,0,sizeof(dstaddr));
	dstaddr.nl_family = AF_NETLINK;
	dstaddr.nl_pid = 0;//send to kernel
	dstaddr.nl_groups = 0;//unicast
    
	/*call the sendto function to send the message*/
	err = sendto(sock_fd,&reqdata,reqdata.nlhdr.nlmsg_len,0,(struct sockaddr *)&dstaddr,sizeof(dstaddr));
	if(err < 0)
	{
		printf("send message error\n");
		return -1;
	}


	/*receive the message loop*/

	alarm(30);

	memset(buffer,0,MAX_MSGSIZE);
	while((len = recv(sock_fd,buffer,MAX_MSGSIZE,0)) >0) //receive message from kernel
	{
		alarm(0);
		hdr = (struct nlmsghdr *)buffer;
		// if the data is receive completed,the type may be NLMSG_NONE,
		// otherwise there is more data to parse
		if(hdr->nlmsg_type == NLMSG_DONE)
		{
			printf("there is no more data to received.\n");
			break;
		}
		
		// if error occured when kernel send the message
		if(hdr->nlmsg_type == NLMSG_ERROR)
		{
			printf("some error occurred in the kernel.\n");
			struct nlmsgerr *nlherr;
			nlherr = (struct nlmsgerr *)NLMSG_DATA(hdr);//fetch the error code in the netlink payload
			printf("error message:%d\n",nlherr->error);
			break;
		}

		// though these marco to get the data
		
		ifimsg = NLMSG_DATA(hdr);//get the interface infomation
		printf("get the device infomation:%d\n",ifimsg->ifi_index);
		printf("the device type:\n");

		switch(ifimsg->ifi_type)
		{
			case ARPHRD_ETHER:
				printf("ethernet device\n");
				break;
			case ARPHRD_LOOPBACK:
				printf("loopback device\n");
				break;
			default:
				printf("unkown device\n");
				break;
		}

		printf("the device status:\n");

		if((ifimsg->ifi_flags & IFF_UP) == IFF_UP)
			printf("UP");
		if((ifimsg->ifi_flags & IFF_BROADCAST) == IFF_BROADCAST)
			printf("BROADCAST");
		if((ifimsg->ifi_flags & IFF_DEBUG) == IFF_DEBUG)
			printf("DEBUG");
		if((ifimsg->ifi_flags & IFF_MASTER) == IFF_MASTER)
			printf("MASTER");
		if((ifimsg->ifi_flags & IFF_SLAVE) == IFF_SLAVE)
			printf("SLAVE");
		if((ifimsg->ifi_flags & IFF_AUTOMEDIA) == IFF_AUTOMEDIA)
			printf("AUTOMEDIA");
		if((ifimsg->ifi_flags & IFF_DYNAMIC) == IFF_DYNAMIC)
			printf("DYNAMIC");
		printf("\n");

		/*though the marco get the netlink attributes*/
		attr = IFLA_RTA(hdr);//get the attribute from the data portion
		attrlen = NLMSG_PAYLOAD(hdr,sizeof(struct ifinfomsg));

		while(RTA_OK(attr,attrlen))
		{
			switch(attr->rta_type)
			{
				case IFLA_IFNAME:
					printf("the device name:%s\n",(char *)RTA_DATA(attr));
					break;

				case IFLA_MTU:
					printf("the device mtu:%s\n",(char *)RTA_DATA(attr));
					break;
				case IFLA_QDISC:
					printf("the device queue:%s\n",(char *)RTA_DATA(attr));
					break;
				case IFLA_ADDRESS:
					if(ifimsg->ifi_type == ARPHRD_ETHER)
					{
						ethaddr = (struct ether_addr *)RTA_DATA(attr);
					    printf("the device MAC address:%s\n",ether_ntoa(ethaddr));
					}
					break;
				case IFLA_BROADCAST:
					if(ifimsg->ifi_type == ARPHRD_ETHER)
					{
						ethaddr = (struct ether_addr *)RTA_DATA(attr);
						printf("the device broadcast address:%s\n",ether_ntoa(ethaddr));
					}
					break;

				default:
					break;
					
			}

			/*the next attribute*/
			attr = RTA_NEXT(attr,attrlen);
		}

		/*the next data*/
		hdr = NLMSG_NEXT(hdr,len);
		memset(buffer,0,MAX_MSGSIZE);//reset the buffer to receive the next data
		alarm(30);

	}
	
	
	return 0;	

}
