#include <stdio.h>
#include <time.h>
#include "E101.h"

int main() {
	init();
	int cruiseSpeed = 80;
	double errScale = 175/646; // Not calibrated yet. Requires trial and error to find.
	while (true) {
		int midArray [64] = { };
		double pError = 0;
		int whiteCount = 0; // Not used yet, but should count properly
		take_picture();
		for (int i = 0; i < 64; i++) { // sizeof(midArray) returns the size of the whole array in bytes, divided by the size of one element in bytes = number of elements
			if (get_pixel(120, i*5, 3) >= 128) {
				midArray[i] = 1;
				pError += midArray[i]*(i-31); // The centre of the array is index 31 & 32. This maps index 31 as 0
				whiteCount++;
			} else { //get_pixel(120, 1*5, 3) <= 127
				midArray[i] = 0;
			}
		}
		printf("Counted %d white pixels\n", whiteCount);
		printf("Calculated error of: %d\n", pError);
		set_motor(1, (int)(cruiseSpeed + (pError * errScale))); //Right wheel
		set_motor(2, (int)(cruiseSpeed - (pError * errScale))); //Left wheel
	}
	return 0;
}
