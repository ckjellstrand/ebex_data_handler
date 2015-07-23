#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define HELLO_PORT 9876
#define HELLO_GROUP "239.192.0.2" 
#define MSGBUFSIZE 560


typedef struct Timestamp{
	/* SIGNED types are used here to permit negative numbers during
	 *          * renormalization and comparison. THE ORDER IS IMPORTANT, since
	 *                   * this matches the VHDL's field packing. */
	int32_t y,d,h,m,s;
	int32_t ss;
	int32_t c, sbs;
} Timestamp;


typedef struct DfmuxPacket{
	uint32_t magic;
	uint32_t version;

	uint8_t num_modules;
	uint8_t channels_per_module;
	uint8_t fir_stage;
	uint8_t module; /* linear; 0-7. don't like it much. */

	uint32_t seq; /* incrementing sequence number */

	int32_t s[128];

	struct Timestamp ts;
} DfmuxPacket;


main(int argc, char *argv[])
{
	struct sockaddr_in addr;
	int fd, nbytes,addrlen;
	struct ip_mreq mreq;
	char msgbuf[MSGBUFSIZE];
	char totalbuff[MSGBUFSIZE*1000];

	/* create what looks like an ordinary UDP socket */
	fd=socket(AF_INET,SOCK_DGRAM,0);
	if (fd < 0) {
		perror("socket");
		exit(1);
	}


	/* allow multiple sockets to use the same PORT number */
	u_int yes=1;
	if (setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0) {
		perror("Reusing ADDR failed");
		exit(1);
	}


	/* set up destination address */
	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=htonl(INADDR_ANY); /* N.B.: differs from sender */
	addr.sin_port=htons(HELLO_PORT);

	/* bind to receive address */
	if (bind(fd,(struct sockaddr *) &addr,sizeof(addr)) < 0) {
		perror("bind");
		exit(1);
	}

	/* use setsockopt() to request that the kernel join a multicast group */
	mreq.imr_multiaddr.s_addr=inet_addr(HELLO_GROUP);
	mreq.imr_interface.s_addr=htonl(INADDR_ANY);
	if (setsockopt(fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0) {
		perror("setsockopt");
		exit(1);
	}


	//while (1) {
	int i;
	for (i=0; i<1000; i++){
		addrlen=sizeof(addr);

		nbytes=recvfrom(fd,msgbuf,MSGBUFSIZE,0,(struct sockaddr *) &addr,&addrlen);
		if (nbytes < 0) {
			perror("recvfrom");
			exit(1);
		}
		//DfmuxPacket *tmp = (DfmuxPacket*) msgbuf;
		memcpy(totalbuff + MSGBUFSIZE*i, msgbuf, MSGBUFSIZE);
		printf("%d\n", totalbuff[i]);
		// This isn't actually ints, but I can see differences between packets if I pretend they are.
		printf("Received %d\n", i);
	}
	printf("%d\n", sizeof(totalbuff));
	// Do blosc compression here.
}
