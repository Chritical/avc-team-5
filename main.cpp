#include <stdio.h>
#include <time.h>
#include "E101.h"

// All of these methods are subject to change
void drive();
int read_white_line();
int calculate_threshold();  // Parameters?

void left_motor(int speed);
void right_motor(int speed);
int open_gate();  // True if successful

int motor_test();

void Turn(int v_left, int v_right);

int SPEED = 32;
int dv;

int quad = 1;

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
    set_motor(2, -speed);
}

void right_motor(int speed)
{
    set_motor(1, speed);
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
