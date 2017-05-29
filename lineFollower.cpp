#include <stdio.h>
#include <time.h>
#include "E101.h"

int turnRight() {
	set_motor(1, 40);
	set_motor(2, 0);
	printf("Turning Right\n");
	sleep1(1, 0);
}
int turnLeft() {
	set_motor(1, 0);
	set_motor(2, 40);
	printf("Turning Left\n");
	sleep1(1, 0);
}

int main() {
	init();
	
	int cruiseSpeed = 40;
	int whiteCount = 0;
	int whiteCountLeft = 0;
	int whiteCountRight = 0;
	double pScale = 0.7;
	double pError = 0;
	double p = 0;
	//double kd = ?; // derivative value
	//int  current_error;
	//int previous_error;
	//int derivative_signal = 0;
	int right_motor = 0;
	int left_motor = 0;
	bool gate = true;	// If the gate is closed or not
	bool q2 = true;		// Following the straight and curvy lines
	bool q3 = false;		// Navigating 90 degree lines and intersections
	bool maze = true;	// Navigating maze using infrared sensors and hugging right wall

	while (gate) {
		char addr[15] = {'1', '3','0','.','1','9','5','.','6','.','1','9','6'};
		connect_to_server(addr, 1024);
		char msgToSrvr[24] = {'P','l','e','a','s','e'};
		send_to_server(msgToSrvr);
		char msgFromSrvr[24];
		receive_from_server(msgFromSrvr); 
		for(int i = 0; i < 6 ; i++ ){ // copy 6 elements of mesgFromSrvr to msgtosrvr
			msgToSrvr [i] = msgFromSrvr [i];
		}
		send_to_server(msgToSrvr);

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
			if (i < 160) {
				whiteCountLeft++;	
			} else {
				whiteCountRight++;
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
		
		// Assume robot has gotten up to the second 4 way intersection, halfway through q3
		
		if (whiteCount > 310) { // Not tested yet
			q3 = true;
			turnLeft();
		}
		if (q3) {
			if (whiteCountLeft > 120) {
				turnLeft();
			} else if (whiteCountRight > 120) {
				turnRight();
			}
		}
	}
	
	while (maze) {
		maze = false;
	}
	
	return 0;
}

// Third Quad note: calculate diff signal: error of this line minus eroor of another line. error_diff*kd . Instead of error of seperate frames 

