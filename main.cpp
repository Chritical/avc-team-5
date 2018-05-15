#include <stdio.h>
#include <time.h>
#include "E101.h"

// All of these methods are subject to change
void drive();

void left_motor(int speed);
void right_motor(int speed);
int open_gate();  // True if successful

void Turn(int v_left, int v_right);

int SPEED = 32;
int dv;
int quad = 2;

int main()
{
    init();
    
    while (true)
    {
        switch (quad)
        {
            case 1:
				
				motor_test();

//                 gate_open();
//                 sleep1(7, 0);
                
                
                break;
            case 2:
			detect_white_line();
			
                break;
            case 3:
                break;
            case 4:
                break;
            default:
                return -1;
        }
    }
    
    return 0;
}

void left_motor(int speed)
{
    set_motor(2, speed);
}

void right_motor(int speed)
{
    set_motor(1, -speed);
}

int open_gate(){
	char ip[15] = "130.195.6.196";
	while(connect_to_server(ip, 1024)!=0){continue;}
	printf("Connected");
	char message[24] = "Please";
	while(send_to_server(message) != 0){continue;}
	printf("Message sent");
	char password[24] = "";
	while(receive_from_server(password) != 0){continue;}
	while(send_to_server(password) != 0){continue;}
	printf("Message sent 2");
	return 0;
} 

int detect_white_line() {
	int max = 0;
    	int min =255;
	int scan_row = 120;
	int error = 0;
	int numWhite = 0;
	int whi[320];  // white pixels
	
	take_picture();
	
	//find min and max
   	for (int i = 0; i <320;i++)
	{
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
	for (int i = 0; i <320;i++)
	{
		whi[i]= 0 ;
		int pix = get_pixel(scan_row,i,3);
		if ( pix > thr)
		{
			whi[i] = 1;
			numWhite++;
		}
	}
		
	
	//calculate error
	for (int i = 0; i<320; i++)
	{
		error = error+((i-160)/numWhite)*whi[i];
	}

	if (max<150){ // if all black
		error = -10000;
	} else if (min>150){ //if all white
		error = 10000;
	}
	
	printf("error: %d", error);
		
return 0;
}

int follow_line(int error) {
	int v_go = SPEED;
	double Kp = 1;
	double dv;
	int v_left;
	int v_right;
	
	while (true){
		dv = error * Kp;
		v_left = v_go + dv;
		v_right = v_go - dv;

		if (v_left > 255){
			v_left = 255;
		}
		if (v_right > 255){
			v_right = 255;
		}
		if (error < 1000 && error > -1000){
			Turn(v_left, v_right);
		}
		
		if (error > 1000){
			left_motor(0);
			right_motor(0);	
		}
		
	}
	
return 0;
}

void Turn(int v_left, int v_right) {
	left_motor(v_right);
	left_motor(v_left);
}
