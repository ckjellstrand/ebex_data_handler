#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *noise_file;
	noise_file = fopen("noise", "r");

	int32_t data[128];
	int i;

	for (i = 0; i<128; i++){
		fscanf(noise_file, "%d", &data[i]);
	}

	fclose(noise_file);

	for (i = 0; i<128; i++){
		printf("%d\n", data[i]);
	}
	return 0;
}
