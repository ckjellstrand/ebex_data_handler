//http://ntrg.cs.tcd.ie/undergrad/4ba2/multicast/antony/example.html
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

main(int argc, char *argv[])
{
	struct sockaddr_in addr;
	int fd, nbytes, cnt;
	struct ip_mreq mreq;
	char *message="Hello, World!";

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
		nbytes = sendto(fd,message,sizeof(message)+5,0,(struct sockaddr *) &addr,sizeof(addr));
		// If the +5 isn't in the sizeof, the message is cut off. Not sure why.
		printf("%d", sizeof(message));
		if (nbytes < 0) {
			perror("sendto");
			exit(1);
		}
		sleep(1);
	}
}
