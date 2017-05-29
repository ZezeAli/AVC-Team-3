#include <stdio.h>
#include <time.h>
#include "E101.h"

int main() {
  init();
  
  //Left Turn
  // Right Wheel
  set_motor(1, -70);
  // Left Wheel
  set_motor(2, 0);
  sleep1(1, 125000);
  
  /*
  //Right Turn
  // Right Wheel
  set_motor(1, 0);
  // Left Wheel
  set_motor(2, 70);
  sleep1(1, 0);
  */
  
  
  set_motor(1, 0);
  set_motor(2, 0);
}
