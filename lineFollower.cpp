#include <stdio.h>
#include <time.h>
#include "E101.h"

int main() {
	init();
	
	int cruiseSpeed = 40;
	int whiteCount = 0;
	double pScale = 0.7;
	double pError = 0;
	double p = 0;
	int right_motor = 0;
	int left_motor = 0;
	
	bool gate = true;	// If the gate is closed or not
	bool q2 = true;		// Following the straight and curvy lines
	bool q3 = true;		// Navigating 90 degree lines and intersections
	bool maze = true;	// Navigating maze using infrared sensors and hugging right wall
	
	while (gate) {
		gate = false;
	}
	
	while (q2) {
		pError = 0;
		whiteCount = 0;
		take_picture();
		for (int i = 0; i < 320; i++) {
			if (get_pixel(120, i, 3) >= 60) {
				pError += i-159; // The centre of the row is index 159 & 160. This maps index 159 as 0
				whiteCount++;
			}
		}
		p = (pError / 320) * pScale; // Dividing by 320 made it easier to calibrate pScale by hand
		
		printf("No. white pixels: %d\n", whiteCount);
		printf("Calculated error of: %f\n", pError);
		printf("Scaled error: %f\n", p);
		
		right_motor = cruiseSpeed + (p);
		left_motor = cruiseSpeed - (p);
		
		printf("Setting left motor to: %d\n", left_motor);
		printf("Setting right motor to: %d\n", right_motor);
		set_motor(1, -left_motor);
		set_motor(2, right_motor);
		
		printf("====================================\n");
		
		// Check if quadrant is over or if line can't be seen
		if (whiteCount > 315) { // Not tested yet
			q2 = false;
		} else if (whiteCount == 0) {
			set_motor(1, cruiseSpeed);
			set_motor(2, -cruiseSpeed);
			printf("Moving backwards for 1 second\n");
			sleep1(1, 0);
		}
	}
	
	while (q3) {
		q3 = false;
	}
	
	while (q4) {
		q4 = false;
	}
	
	return 0;
}

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
