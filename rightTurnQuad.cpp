#include <stdio.h>
#include "E101.h"

void detection();
void turnLeft();
void turnRight();
void straight();
void left_motor(int speed);
void right_motor(int speed);
int clamp(int val, int min, int max);
int findThreshold();
int follow_line(int error);
void Turn(int v_left, int v_right);

int BLACK_THRESHOLD = 100;
int WHITE_THRESHOLD = 150;

int main(){
	init();
	detection();
	return 0;
}

int SPEED = 40;
bool leftLine = true;
bool rightLine = true;
bool forwardLine = true;
int thr;

int findThreshold(){
	int max = 0;
	int min = 255;
	int scan_row = 120;
	
	//find min and max
   	for (int i = 0; i < 320; i++){
		int pix = get_pixel(scan_row,i,3);
		if ( pix > max){
			max = pix;
		}
		if (pix < min){
			min = pix;
		}
    } 
	//set threshold
	if(max>100 && min<150){
		thr = (max+min)/2;
	}
		
	return 0;
}

int detect_white_line() {
	int max = 0;
	int min = 255;
	int scan_row = 120;
	int error = 0;
	int numWhite = 0;
	int whi[320];  // white pixels
	
	take_picture();
	
	//find min and max
   	for (int i = 0; i < 320; i++){
		int pix = get_pixel(scan_row,i,3);
		if ( pix > max) 
		{
			max = pix;
		}
		if (pix < min)
		{
			min = pix;
		}
		
    } 
	
	//find white and black pixels
	int thr = (max+min)/2;	
	for (int i = 0; i < 320; i++)
	{
		whi[i]= 0 ;
		int pix = get_pixel(scan_row, i, 3);
		if (pix > thr)
		{
			whi[i] = 1;
			numWhite++;
		}
	}

	//calculate error
	for (int i = 0; i < 320; i++)
	{
		error = error+((i-160)/numWhite)*whi[i];
	}

	if (max<BLACK_THRESHOLD){ // if all black
		error = -10000;
	} else if (min>WHITE_THRESHOLD){ //if all white
		error = 10000;
	}
	
	follow_line(error);
	
// 	printf("error: %d%n", error);
		
return 0;
}

int follow_line(int error) {
	int v_go = SPEED;
	double Kp = 0.18;
	double dv;
	int v_left;
	int v_right;
	
	dv = error * Kp;
	v_right = v_go + dv;
	v_left = v_go - dv;

	if (v_left > 255){
		v_left = 255;
	}
	if (v_right > 255){
		v_right = 255;
	}
	if (error > -1000 && error < 1000){
		Turn(v_left, v_right);
	}
	
	if (error >= 10000){
		left_motor(0);
		right_motor(0);	
	}
	else if (error <= -10000){
		left_motor(-SPEED*0.9);
		right_motor(-SPEED*0.9);
	}
    return 0;
}

void detection(){
	while(true){
        detect_white_line();
		take_picture();
		
		if (get_pixel(120, 160, 0)>180){
			set_motor(1, 0);
			set_motor(2, 0);
		}
		
		findThreshold();
		
		int column = 20;
		int row = 120;
		for(int i=0; i<9; i++){ //go through nine points in the image
			if(i <= 5){ //checks for a left turn
				if(get_pixel(column, row, 3) < thr){
					leftLine = false;
				}
			}
			if(i >= 5){ //check for a right turn
				if(get_pixel(column, row, 3) < thr){
					rightLine = false;
				}
			}
			column += 33; //checks next point along the image
		}
		column = 160;
		row = 280;
		for(int i=0; i<4; i++){ //go through 4 points down the image
			if(get_pixel(column, row, 3) < thr){
				forwardLine = false; //checks if drive forward option is available
			}
			row -= 20; //checks next point down the image
		}
		if(leftLine && rightLine){
			right_motor(60);
            left_motor(0);
		}else if(leftLine){
			right_motor(60);
            left_motor(0);
		}else if(rightLine){
			right_motor(0);
            left_motor(60);
		}
		rightLine = true;
		leftLine = true;
		forwardLine = true;
	}
}

void Turn(int v_left, int v_right) {
	right_motor(v_right);
	left_motor(v_left);
}

void right_motor(int speed){
	double s = speed * 1.2;
	speed = (int) s;
	speed = clamp(speed, -255, 255);
	
    set_motor(2, -speed);
}

void left_motor(int speed){
    set_motor(1, speed);
}

int clamp(int val, int min, int max)
{
	if (val > max)
	{
		return max;
	}
	else if (val < min)
	{
		return min;
	}
	else
	{
		return val;
	}
}
