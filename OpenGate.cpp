// code to open gate 
#include <stdio.h>
#include <time.h>
#include "E101.h"
#include <math.h>

//init();
int main(){

bool gate=true;
//bool startQuad2=false;

// initialise variables 

while(gate){
  char addr[15]={'1', '3','0','.','1','9','5','.','6','.','1','9','6'};
  connect_to_server(addr, 1024);
  char msgToSrvr[24]={'P','l','e','a','s','e'};
  send_to_server(msgToSrvr);
  char msgFromSrvr[24];
  receive_from_server (msgFromSrvr); 
   for(int i = 0; i < 6 ; i++ ){ // copy 6 elements of mesgFromSrvr to msgtosrvr
      msgToSrvr [i] = msgFromSrvr [i];
   }
  
  send_to_server(msgToSrvr);



gate=false; //end while loop

//startQuad2=true; // start
  
}
