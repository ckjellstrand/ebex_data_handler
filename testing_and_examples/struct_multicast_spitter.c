// Creates struct, tries translatting it to byte array and back itself, sends byte array.
//
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define HELLO_PORT 12345
#define HELLO_GROUP "225.0.0.37"

typedef struct AMG_ANGLES {
	float yaw;
	float pitch;
	float roll;
} AMG_ANGLES;

int main() {
	AMG_ANGLES struct_data;

	struct_data.yaw = 87.96;
	struct_data.pitch = -114.58;
	struct_data.roll = 100.50;

	//Sending Side
	char b[sizeof(struct_data)];
	memcpy(b, &struct_data, sizeof(struct_data));
	//Receiving Side
	AMG_ANGLES tmp; //Re-make the struct
	memcpy(&tmp, b, sizeof(tmp));
	printf("%f\n", tmp.yaw);


	// Creates struct, converts to byte array.




	struct sockaddr_in addr;
	int fd, nbytes, cnt;
	struct ip_mreq mreq;

	/* create what looks like an ordinary UDP socket */
	fd=socket(AF_INET,SOCK_DGRAM,0);
	if (fd < 0) {
		perror("socket");
		exit(1);
	}

	/* set up destination address */
	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr(HELLO_GROUP);
	addr.sin_port=htons(HELLO_PORT);

	/* now just sendto() our destination! */
	while (1) {
		nbytes = sendto(fd,b,sizeof(b)+5,0,(struct sockaddr *) &addr,sizeof(addr));
		// If the +5 isn't in the sizeof, the message is cut off. Not sure why.
		if (nbytes < 0) {
			perror("sendto");
			exit(1);
		}
		sleep(1);
	}
}
