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

int speed = 30;
bool leftLine = true;
bool rightLine = true;
bool forwardLine = true;

void detection(){
	while(true){
		take_picture();
		
// 		//find min and max
//    	for (int i = 0; i < 320; i++)
// 	{
// 		int pix = get_pixel(scan_row,i,3);
// 		if ( pix > max) 
// 		{
// 			max = pix;
// 		}
// 		if (pix < min)
// 		{
// 			min = pix;
// 		}
		
//     } 
	
// 	//find white and black pixels
// 	int thr = (max+min)/2;
		
		int column = 20;
		int row = 120;
		for(int i=0; i<9; i++){ //go through nine points in the image
			if(i <= 5){ //checks for a left turn
				if(get_pixel(column, row, 3) < 100){
					leftLine = false;
				}
			}
			if(i >= 5){ //check for a right turn
				if(get_pixel(column, row, 3) < 100){
					rightLine = false;
				}
			}
			column += 33; //checks next point along the image
		}
		column = 160;
		row = 280;
		for(int i=0; i<4; i++){ //go through 4 points down the image
			if(get_pixel(column, row, 3) < 100){
				forwardLine = false; //checks if drive forward option is available
			}
			row -= 20; //checks next point down the image
		}
		if(forwardLine){
			straight();
		}else if(leftLine && rightLine){
			turnLeft();
		}else if(leftLine){
			turnLeft();
		}else if(rightLine){
			turnRight();
		} else{
			turnAround();
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
	straight(); //moves straight to get to turn
	set_motor(1, speed);
	set_motor(2, 0);
	sleep1(1,0);
	detection(); //restarts camera up again
}

void turnLeft(){
	straight();
	set_motor(1, 0);
	set_motor(2, -speed);
	sleep1(1,0);
	detection();
}

void straight(){ //move robot forward
	set_motor(1, speed);
	set_motor(2, -speed);
	sleep1(0,5000000);
	detection();
}

void turnAround(){ //move robot forward
	set_motor(1, speed);
	set_motor(2, speed);
	sleep1(1, 0);
	detection();
}
