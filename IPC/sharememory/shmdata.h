/*define the data struct*/

#ifndef __SHMDATA__H
#define __SHMDATA__H

#define TEXT_SZ 2048
struct shared_use_st
{
	int written;// a flag, 0 represent read,1 represent write 
	char text[TEXT_SZ];// record the read or write text
};

#endif
