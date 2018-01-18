#include <stdio.h>
#include <stdlib.h>
#include "averages.h"

int main(int argc, char** argv) {

    double x = 4;
    double y = 6;

    if(argc > 2) {
    	x = atof(argv[1]);
    	y = atof(argv[2]);
    }

	printf("Arithmetic mean: %6.2f\n", arithmeticMean(x,y));
	printf("Geometric mean: %6.2f\n", geometricMean(x,y));
	printf("Harmonic mean: %6.2f\n", harmonicMean(x,y));
} // main(int, char**)