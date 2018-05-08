#include <stdio.h>
#include "E101.h"

// All of these methods are subject to change
void drive();
int read_white_line();
int calculate_threshold();  // Parameters?

void left_wheel(int speed);
void right_wheel(int speed);

boolean open_gate();  // True if successful

int main()
{
    init();

    return 0;
}

void left_wheel(int speed)
{
    set_motor(1, speed);
}

void right_wheel(int speed)
{
    set_motor(2, speed);
}
