#include <stdio.h>
#include "E101.h"

// All of these methods are subject to change
int calculate_threshold();
int read_white_line();
void left_wheel();
void right_wheel();

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
