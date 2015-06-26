#include <stdint.h>
#include <stdio.h>
#include <zmq.h>
#include <assert.h>
#include <string.h>

#define FAST_MAGIC      0x666d7578
#define FAST_VERSION    2


typedef struct Timestamp {
	/* SIGNED types are used here to permit negative numbers during
	 * renormalization and comparison. THE ORDER IS IMPORTANT, since
	 * this matches the VHDL's field packing. */
	int32_t y,d,h,m,s;
	int32_t ss;
	int32_t c, sbs;
} Timestamp;


typedef struct DfmuxPacket {
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


static int s_send (void *socket, char *string) {
	int size = zmq_send (socket, string, strlen (string), 0);
	return size;
}


int main (void){


	//  Prepare our context and publisher
	void *context = zmq_ctx_new ();
	void *publisher = zmq_socket (context, ZMQ_PUB);
	int rc = zmq_bind (publisher, "tcp://*:5556");
	assert (rc == 0);


	int i;
	DfmuxPacket packet;
	for(i=0; i<100; i++)
	{
		packet.seq = i;
		printf("%d\n", packet.seq);
		s_send(publisher, "test");
	}

	zmq_close (publisher);
	zmq_ctx_destroy (context);
	return 0;
}
