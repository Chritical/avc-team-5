#include <stdio.h> 
#include <time.h> 
#include "E101.h"


int main(){
   init();
 
 boolean inMaze = true;
 int adc_left;// left sensor - channel 0
 int adc_front; // front sensor - channel 1
 int adc_right; //right sensor - channel 2
   

 
 while(inMaze){
   read(); // sensors will read values of surrondings
 
 //leftIR further from wall than rightIR. frontIR is close to wall. Turn left 
 if(adc_left<adc_right && adc_front >= 300){  
    while(adc_left<adc_right && adc_front >= 300){ //turn left while right>left and robot front is close to wall
       read();
       turn_left();
    }
    stop();
 }
 
 //rightIR further from wall than leftIR. frontIR is close to wall. Turn right
 else if(adc_right<adc_left && adc_front >= 300){ 
   while(adc_left<adc_right && adc_front >= 300){
       read();
       turn_right();
    }
    stop();
 }
    
 //rightIR, leftIR and frontIR have high readings. Turn around  
 else if(adc_right >= 300 && adc_left >= 300 && adc_front>= 300){
   while(adc_right >= 300 && adc_left >= 300 && adc_front>= 300){
      read();
      turn_right(); 
  }
     stop();
 }
  //if left wall closer than right (values < 100) and front close to wall. Turn left
  else if(adc_left>adc_right && adc_front >= 300){
   while(adc_left<adc_right && adc_front >= 300){
       turn_left();
    }
    stop();
  }
 
 // go forward
 else{
   set_motor(1,64); //left motor
   set_motor(2,64); //right motor
 }
 
 }

   
}




void turn_left(){ // Turns left on spot
   set_motor(1,32); //left motor
   set_motor(2,64); //right motor
}

void turn_right(){ // Turns right on spot
   set_motor(1,64); //left motor
   set_motor(2,32); //right motor
   
}

void stop();{ //Stops vehicle
   sleep1(1,0);
   
   set_motor(1,0); //left motor
   set_motor(2,0); //right motor
   
  }

void read(){
 adc_left = read_analog(0); //reads left IR value
 adc_front = read_analog(1); //reads front IR value
 adc_right = read_analog(2); //reads right IR value
}
}
//300 front
//400 sides
