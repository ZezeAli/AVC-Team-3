#include <stdio.h>
#include <time.h>
#include "E101.h"

int main() {
	init();
	int cruiseSpeed = 80;
	double errScale = 1;
	while (true) {
		int midArray [64] = { };
		int pError = 0;
		int whiteCount = 0; // Not used yet, but should count properly
		take_picture();
		for (int i = 0; i < (sizeof(midArray)/sizeof(midArray[0]); i++) { // sizeof(midArray) returns the size of the whole array in bytes, divided by the size of one element in bytes = number of elements
			if (get_pixel(120, 1*5, 3) >= 128) {
				midArray[i] = 1;
				pError += midArrary[i]*(i-31); // The centre of the array is index 31 & 32. This maps index 31 as 0
				whiteCount++;
			} else { //get_pixel(120, 1*5, 3) <= 127
				midArray[i] = 0;
			}
		}
		printf("Counted %d white pixels", whiteCount);
		printf("Calculated error of: %d\n", pError);
		set_motor(1, cruiseSpeed + (pError * errScale)); //Right wheel
		set_motor(2, cruiseSpeed - (pError * errScale)); //Left wheel
	}
}
