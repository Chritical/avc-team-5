#include <stdio.h> 
#include <time.h> 
#include "E101.h"
#include <string>

int main(){
   init();
 
 boolean inMaze = true;
 int adc_left;// left sensor - channel 0
 int adc_front; // front sensor - channel 1
 int adc_right; //right sensor - channel 2
   

 
 while(inMaze){
 adc_left = read_analog(0); //reads left IR value
 adc_front = read_analog(1); //reads front IR value
 adc_right = read_analog(2); //reads right IR value
 
 //leftIR further from wall than rightIR. frontIR is close to wall. Turn left 
 if(adc_left<adc_right && adc_front >= 300){  
   turn_left();//duration long enough to turn 90
 }
 
 //rightIR further from wall than leftIR. frontIR is close to wall. Turn right
 else if(adc_right<adc_left && adc_front >= 300){ 
   turn_right(); //duration long enough to turn 90
 }
    
 //rightIR, leftIR and frontIR have high readings. Turn around  
 else if(){
   turn_right(); //duration long enough to turn 180
 }
  //if left wall closer than right (values < 100) and front close to wall. Turn left
  else if(left_sensor>right_sensor && adc_front >= 300){
   turn_left(); //duration long enough to turn left 90
  }
 
 // go forward
 else{
   set_motor(1,64); //left motor
   set_motor(2,64); //right motor
 }
 
 }

}

void turn_left(int duration){ // Turns left on spot
   set_motor(1,32); //left motor
   set_motor(2,64); //right motor

   sleep1(0, duration); 
   
   set_motor(1,0); //left motor
   set_motor(2,0); //right motor
}

void turn_right(int duration){ // Turns right on spot
   set_motor(1,64); //left motor
   set_motor(2,32); //right motor
   
   sleep1(0, duration);
   
   set_motor(1,0); //left motor
   set_motor(2,0); //right motor
}
   
  }
//300 front
//400 sides
