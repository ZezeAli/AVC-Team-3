#include <stdio.h>
#include <time.h>
#include "E101.h"

int main() {
  set_motor(1, 60);
  set_motor(2, 0);
  
  sleep1(1, 0);
  
  set_motor(1, 0);
  set_motor(2, 0);
}
