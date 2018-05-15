#include <stdio.h> 
#include <time.h> 
#include "E101.h"


int main(){
   init();
 
 int adc_left;// left sensor - channel 0
 int adc_front; // front sensor - channel 1
 int adc_right; //right sensor - channel 7
   
 for(int i=0; i<10; i++){
   adc_left = read_analog(0);
   adc_front = read_analog(1);
   adc_right = read_analog(7);
    
   printf("%d\n", adc_left); 
   sleep1(1,0);
    
}
    for(int i=0; i<10; i++){
   adc_left = read_analog(0);
   adc_front = read_analog(1);
   adc_right = read_analog(7);
    
   printf("%d\n", adc_front); 
   sleep1(1,0);
    
}
    for(int i=0; i<10; i++){
   adc_left = read_analog(0);
   adc_front = read_analog(1);
   adc_right = read_analog(7);
    
   printf("%d\n", left); 
   sleep1(1,0);
    
}
   
  }
