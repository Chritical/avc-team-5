#include <stdio.h> 
#include <time.h> 
#include "E101.h"


int main(){
   init();
 
 bool inMaze = true;
 int adc_left;// left sensor - channel 0
 int adc_front; // front sensor - channel 1
 int adc_right; //right sensor - channel 2
   

 
 while(inMaze){
   read(); // sensors will read values of surrondings
 
 //turn right for first two turns
 if(adc_left >= 550 && adc_right< 120 && adc_front >= 580){  
    while(adc_front>=120 || adc_left<500){ 
       read();
       turn_right();
    }
    stop();
 }
    
 // turn left for the first alley instead of the alley with the gate
  else if(adc_left <= 120 && adc_right > 500 && adc_front <= 120){
   while(adc_right > 120 && adc_front > 120 && adc_left > 120){
       turn_left();
    }
    stop();
  }
    
    //turn right after the alley
  if(adc_right>adc_left&& adc_right > 200 && adc_front >= 580){
      while(adc_front>=120 || adc_left<500){ 
           read();
         turn_right();
      }
    stop();
  }
 
  //turn left
  if(adc_right>adc_left&& adc_right < 200 && adc_front >= 580){
      while(adc_front>=120 || adc_right<500){ 
           read();
         turn_left();
      }
    stop();
  }
    
  // final left turn
   if(adc_right >= 550 && adc_left< 120 && adc_front >= 580){  
    while(adc_front>=120 || adc_right<500){ 
       read();
       turn_leftt();
    }
    stop();
 }
 
    
 //rightIR, leftIR and frontIR have high readings. Turn around  
 else if(adc_right >= 580 && adc_left >= 580 && adc_front>= 580){
   while(adc_right >= 580 && adc_left >= 580 && adc_front>= 580){
      read();
      turn_right(); 
      if(adc_right >= 580 && adc_left >= 580 && adc_front < 120){
      break;
      }
  }
     stop();
 }
    

 
 
 else if(adc_left >= 580 && adc_right < 540 ){
   //correct itself to the centre by making left wheel faster
 }
 else if(adc_right >= 580 && adc_left < 540 ){
   //correct itself to the centre by making right wheel faster
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
 printf("%dL %dF %dR",adc_left, adc_front, adc_right);
}
}

