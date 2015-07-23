#include <stdio.h>

int main(){
	if (__builtin_cpu_supports("avx2")){
		printf("avx2 supported\n");
	}
	else{
		printf("avx2 not supported\n");
	}
	if (__builtin_cpu_supports("avx")){
		printf("avx supported\n");
	}
	else{
		printf("avx not supported\n");
	}
}
