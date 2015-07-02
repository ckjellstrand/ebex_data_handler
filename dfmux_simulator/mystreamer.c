
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


int main() {
	struct sockaddr_in addr;
	int fd, nbytes, cnt;
	struct ip_mreq mreq;

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0) {
		perror("socket");
		exit(1);
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr(HELLO_GROUP);
	addr.sin_port=htons(HELLO_PORT);

	DfmuxPacket packet;
	char b[sizeof(packet)];
	memcpy(b, &packet, sizeof(packet));


	while(1) {
		nbytes = sendto(fd, b, sizeof(b), 0, (struct sockaddr *) &addr, sizeof(addr));
		if (nbytes < 0 ) {
			perror("sendto");
			exit(1);
		}
		sleep(1);
	}
}
