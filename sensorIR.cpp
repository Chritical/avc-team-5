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
 adc_left = read_analog(0); //reads left IR value
 adc_front = read_analog(1); //reads front IR value
 adc_right = read_analog(2); //reads right IR value
 
 //leftIR further from wall than rightIR. frontIR is close to wall. Turn left 
 if(adc_left<adc_right && adc_front >= 300){  
   turn_left();
 }
 
 //rightIR further from wall than leftIR. frontIR is close to wall. Turn right
 else if(adc_right<adc_left && adc_front >= 300){ 
   turn_right();
 }
    
 //rightIR, leftIR and frontIR have high readings. Turn around  
 else if(){
   turn_around();
 }
 else{
 
 }
 
 }

}

void turn_left(int duration){ // Turns left
sleep1(0, duration); 
}

void turn_right(int duration){ // Turns right
sleep1(0, duration); 
}

void turn_around(int duration){ // Turns around 180
sleep1(0, duration); 
}
   
  }
//300 front
//400 sides
