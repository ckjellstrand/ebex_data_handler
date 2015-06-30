// Examples from http://stackoverflow.com/questions/13775893/converting-struct-to-byte-and-back-to-struct
// Example included to show how to copy struct into byte array and back into struct.

#include <string.h>
#include <stdio.h>
#include <stdint.h>

typedef struct {
	float yaw;
	float pitch;
	float roll;
} AMG_ANGLES;

typedef struct Timestamp{
	/* SIGNED types are used here to permit negative numbers during
	 * renormalization and comparison. THE ORDER IS IMPORTANT, since
	 * this matches the VHDL's field packing. */
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

	AMG_ANGLES *tmp2 = (AMG_ANGLES*) b;
	printf("%f\n", tmp2->yaw);

	DfmuxPacket packet;
	packet.magic = 1;
	printf("%u\n", packet.magic);
	char c[sizeof(packet)];
	memcpy(c, &packet, sizeof(packet));
	DfmuxPacket *tmp3 = (DfmuxPacket*) c;
	printf("%u\n", tmp3->magic);



}
