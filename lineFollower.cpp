#include <stdio.h>
#include <time.h>
#include "E101.h"

int main() {
	init();
	int cruiseSpeed = 20;
	double errScale = 175/646; // Not calibrated yet. Requires trial and error to find.
	while (true) {
		double pError = 0;
		int whiteCount = 0; // Not used yet, but should count properly
		take_picture();
		for (int i = 0; i < 64; i++) { // sizeof(midArray) returns the size of the whole array in bytes, divided by the size of one element in bytes = number of elements
			if (get_pixel(120, i*5, 3) >= 128) {
				pError += i-31; // The centre of the array is index 31 & 32. This maps index 31 as 0
				whiteCount++;
			}
		}
		printf("Counted %d white pixels\n", whiteCount);
		printf("Calculated error of: %f\n", pError);
		set_motor(1, (int)(cruiseSpeed + (pError * errScale))); //Right wheel
		set_motor(2, (int)(cruiseSpeed - (pError * errScale))); //Left wheel
	}
	return 0;
}

// should we add if/ else statement for what happens if no white pix. Back up slightly off centre. For now? - GP
// Third Quad note: calculate diff signal: error of this line minus eroor of another line. error_diff*kd . Instead of error of seperate frames 
//Taken from lecture slides
//int main(){
//float kd = 0.5;
//int derivative_signal = 0;
//int error; //frame loop calculating error from middle line
//frame loop calculating future error from 180 line
//error_diff = future_error-error;
//derivative_signal = error_diff*kd;
//set motor speeds from sum of PID signals
//return 0;}
