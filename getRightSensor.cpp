#include <stdio.h> 
#include <time.h> 
#include "E101.h"


int main(){
   init();
 
 int adc_left;// left sensor - channel 0
 int adc_front; // front sensor - channel 1
 int adc_right; //right sensor - channel 2
 
 while (true){
      sleep1(2,0);
      
      adc_right = read_analog(2);
      printf("%d", adc_right);
      }
 }
   
