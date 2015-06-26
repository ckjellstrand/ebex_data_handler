// Examples from http://stackoverflow.com/questions/13775893/converting-struct-to-byte-and-back-to-struct
// Example included to show how to copy struct into byte array and back into struct.

#include <string.h>
#include <stdio.h>

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
}
