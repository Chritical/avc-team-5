#include <stdio.h>
#include "E101.h"

// All of these methods are subject to change
void drive();
int read_white_line();
int calculate_threshold();  // Parameters?

void left_wheel(int speed);
void right_wheel(int speed);

boolean open_gate();  // True if successful

int final SPEED = 127;
int dv;

int main()
{
    init();
    
    left_motor(speed);
    right_motor(speed);
    sleep1(5);
    left_motor(0);
    right_motor(0);
    return 0;
}

void left_wheel(int speed)
{
    set_motor(2, speed);
}

void right_wheel(int speed)
{
    set_motor(1, speed);
}

// Returns dv
int read_white_line()
{
    // Take picture
    // Scan through the centre row
}
