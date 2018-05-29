#include <stdio.h> 
#include <time.h> 
#include "E101.h"

int SPEED = 40;
void quad4();
void Turn(int v_left, int v_right);
void right_motor(int speed);
void left_motor(int speed);
int clamp(int val, int min, int max);

int main(){
	init();
	while(true){
		quad4();
	}
}

void quad4(){

	int adc_left = read_analog(0); //reads left IR value
	int adc_front = read_analog(1); //reads front IR value
	int adc_right = read_analog(2); //reads right IR value
	if(adc_front > 550){
		if(adc_left > 550){ //Turn right
			Turn(SPEED,0);
			sleep1(0,500000);
		}else{			//Turn left
			Turn(0,SPEED);
			sleep1(0,500000);
		}
	}else{
		if((adc_left - adc_right) < 50 && (adc_left - adc_right) > -50){
			Turn(SPEED, SPEED);
		}else{
			if(adc_left > adc_right){
				Turn(SPEED*1.2, SPEED);
			}else{
				Turn(SPEED, SPEED*1.2);
			}
		}
	}
	
}

void Turn(int v_left, int v_right) {
    right_motor(v_right);
    left_motor(v_left);
}

void left_motor(int speed){
    double s = speed * 1.2;
    speed = (int) s;
    speed = clamp(speed, -255, 255);
    
    set_motor(2, -speed);
}

void right_motor(int speed){
    set_motor(1, speed);
}

int clamp(int val, int min, int max){
    if (val > max){
        return max;
    }else if (val < min){
        return min;
    } else {
        return val;
    }
}
