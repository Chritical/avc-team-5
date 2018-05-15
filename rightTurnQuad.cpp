#include <stdio.h>
#include "E101.h"

void detection();

int main(){
	init();
	detection();
	return 0;
}

int speed = 64;
int width = 320;
bool horizLine = false;
bool leftLine = true;
bool rightLine = true;
bool fowardLine = true;
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
			if(i <= 5){//checks for a left turn
				if(get_pixel(column, row, 0) != 0){
					leftLine = false;
				}
			}
			column += 20; //checks next point along the image
		}
		column = 160;
		row = 320;
		for(int i=0; i<4; i++){ //go through 4 points down the image
			if(get_pixel(column, row, 0) != 0){
				fowardLine = false; //checks if drive forward option is available
			}
			row -= 10; //checks next point down the image
		}
	}
	printf("working "+leftLine);
	printf(" : "+rightLine);
	printf(" : "+fowardLine);
	if(leftLine == rightLine){ //if both left and right turns are available
		horizLine = true;
	}
}

void turnRight(){
	turning = true;
	set_motor(1, speed);
	set_motor(2, 0);
	sleep1(1,0);
	detection();
}

void turnLeft(){
	turning = true;
	set_motor(1, 0);
	set_motor(2, speed);
	sleep1(1,0);
	turning = false;
	detection();
}

void detectLeftTurn(){
	turnLeft();
}

void detectRightTurn(){
	turnRight();
}

