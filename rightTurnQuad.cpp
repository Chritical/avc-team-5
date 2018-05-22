#include <stdio.h>
#include "E101.h"

void detection();
void turnLeft();
void turnRight();
void straight();

int main(){
	init();
	detection();
	return 0;
}

int speed = 50;
bool leftLine = true;
bool rightLine = true;
bool forwardLine = true;
bool turning = false;

void detection(){
	while(!turning){
		take_picture();
		int column = 20;
		int row = 120;
		for(int i=0; i<9; i++){ //go through nine points in the image
			if(i >= 5){ //check for a right turn
				if(get_pixel(column, row, 0) != 0){
					rightLine = false;
				}
			}
			if(i <= 5){ //checks for a left turn
				if(get_pixel(column, row, 0) != 0){
					leftLine = false;
				}
			}
			column += 33; //checks next point along the image
		}
		column = 160;
		row = 280;
		for(int i=0; i<4; i++){ //go through 4 points down the image
			if(get_pixel(column, row, 0) != 0){
				forwardLine = false; //checks if drive forward option is available
			}
			row -= 20; //checks next point down the image
		}
		if(forwardLine){
			straight();
		}else if(leftLine == rightLine){
			turnLeft();
		}else if(leftLine){
			turnLeft();
		}else if(rightLine){
			turnRight();
		}
		rightLine = true;
		leftLine = true;
		forwardLine = true;
	}
	printf("working "+leftLine);
	printf(" : "+rightLine);
	printf(" : "+forwardLine);
}

void turnRight(){
	turning = true;
	straight(); //moves straight to get to turn
	set_motor(1, speed);
	set_motor(2, 0);
	sleep1(1,0);
	turning = false;
	detection(); //restarts camera up again
}

void turnLeft(){
	turning = true;
	straight();
	set_motor(1, 0);
	set_motor(2, speed);
	sleep1(1,0);
	turning = false;
	detection();
}

void straight(){ //move robot forward
	turning = true;
	set_motor(1, speed);
	set_motor(2, speed);
	sleep1(0,5000000);
	turning = false;
	detection();
}
