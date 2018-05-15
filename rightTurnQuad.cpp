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

void detection(){
	while(true){
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
			column += 20; //moves along the image
		}
	}
	printf("working");
	if(leftLine == rightLine){ //if both left and right turns are available
		horizLine = true;
	}
}

void turnRight(){
	set_motor(1, speed);
	set_motor(2, 0);
}

void turnLeft(){
	set_motor(1, 0);
	set_motor(2, speed);
}

void detectLeftTurn(){
	turnLeft();
}

void detectRightTurn(){
	turnRight();
}


