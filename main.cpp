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

int final SPEED = 64;
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

                gate_open();
                sleep1(7, 0);
                
                
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
    
    left_motor(speed);
    right_motor(speed);
    sleep1(5);
    left_motor(0);
    right_motor(0);
    return 0;
}

void left_motor(int speed)
{
    set_motor(2, speed);
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

// Returns dv
int read_white_line()
{
    // Initialise variables
    int max = 0;
    int min = 255;
    int[] row_pixels = new int[320];
    
    // Take picture
    take_picture();
    // Scan through the centre row
    
    for (int i = 0; i < 320; i++)
    {
        int temp_pixel = get_pixel(120, i, 3);
        
        if (max < temp_pixel)
        {
            max = temp_pixel;
        }
        if (min > temp_pixel)
        {
            min = temp_pixel;
        }
    }

}
