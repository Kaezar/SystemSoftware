#include <stdio.h>
#include <stdlib.h>
#include <math.h>

    int a = 1103515245;
    int c = 12345;

int lcg(int seed, int mod) {
	
	return(a * seed + c) % mod;
} // lcg(int, int)

int main(int argc, char** argv) {

	int seed = 5;
	int mod = 2147483647;

	if(argc > 1){
		seed = atoi(argv[1]);
	}

	for(int i = 0; i < 10; i++) {
		float rand = fabsf((float)seed/mod);
		printf("%6.2f ", rand);
		seed = lcg(seed, mod);
	}

	printf("\n");
} // main(int, char**)