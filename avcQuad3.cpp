//
//  main.cpp
//  avcQuad3
//
//  Created by michael behan on 29/05/18.
//  Copyright © 2018 michael behan. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include "E101.h"

// All of these methods are subject to change
void drive();

void left_motor(int speed);
void right_motor(int speed);
int open_gate();  // True if successful
int clamp(int val, int min, int max);
void Turn(int v_left, int v_right);
int follow_line(int error);
int detect_white_line();
void checkTurn(int thr);

int SPEED = 40;
int dv;
int quad = 1;
int BLACK_THRESHOLD = 100;
int WHITE_THRESHOLD = 150;

int main()
{
    init();
    
    while (true)
    {
        switch (quad)
        {
            case 1:
                open_gate();
                //sleep1(1, 0);
                left_motor(75);
                right_motor(60);
                sleep1(0, 200000);
                quad = 2;
                break;
            case 2:
                detect_white_line();
                break;
            case 3:
                detect_white_line();
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
    double s = speed * 1.2;
    speed = (int) s;
    speed = clamp(speed, -255, 255);
    
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



//Quad 3 -------------:
void checkTurn(int thr){
    int col1 = 10;
    int col2 = 310;
    int row = 25;
    bool leftTurn = false;
    bool rightTurn = false;
    bool moveForward = false;
    
    for(int i=50; i<270; i++){
        int left = get_pixel(i, col1, 3);
        int right = get_pixel(i, col2, 3);
        int forward = get_pixel(row, i, 3);
        if(forward > thr){
			moveForward = true;
        }else if(left > thr){
            leftTurn = true;
        }else if(right > thr){
            rightTurn = true;
        }
    }
    if(moveForward){
		return;
    }else if(leftTurn){
        //sleep1(0, 500000);
        Turn(0, 0);
        sleep1(1, 0);
        Turn(0, SPEED);
        sleep1(0, 500000);
    }else if (rightTurn){
        //sleep1(0, 500000);
        Turn(0, 0);
        sleep1(1, 0);
        Turn(SPEED, 0);
        sleep1(0, 500000);
    }
}

int detect_white_line() {
    int max = 0;
    int min = 255;
    int scan_row = 120;
    int error = 0;
    int numWhite = 0;
    int whi[320];  // white pixels
    
    take_picture();
    
    //find min and max
    for (int i = 0; i < 320; i++)
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
    for (int i = 0; i < 320; i++)
    {
        whi[i]= 0 ;
        int pix = get_pixel(scan_row, i, 3);
        if (pix > thr)
        {
            whi[i] = 1;
            numWhite++;
        }
    }
   
    
    //calculate error
    for (int i = 0; i < 320; i++)
    {
        error = error+((i-160)/numWhite)*whi[i];
    }
    
    if (max<BLACK_THRESHOLD){ // if all black
        error = -10000;
    } else if (min>WHITE_THRESHOLD){ //if all white
        error = 10000;
    }
    
    follow_line(error);
    
    //Quad 3 -------------------:
    if(quad == 3){
        checkTurn(thr);
    }
    
    return 0;
}

int follow_line(int error) {
    int v_go = SPEED;
    double Kp = 0.18;
    double dv;
    int v_left;
    int v_right;
    
    dv = error * Kp;
    v_right = v_go + dv;
    v_left = v_go - dv;
    
    if (v_left > 255){
        v_left = 255;
    }
    if (v_right > 255){
        v_right = 255;
    }
    if (error > -1000 && error < 1000){
        printf("L: %d    R: %d\n", v_left, v_right);
        Turn(v_left, v_right);
    }
    
    if (error >= 10000){
        left_motor(0);
        right_motor(0);
    }
    return 0;
}

void Turn(int v_left, int v_right) {
    right_motor(v_right);
    left_motor(v_left);
}

int clamp(int val, int min, int max)
{
    if (val > max)
    {
        return max;
    }
    else if (val < min)
    {
        return min;
    }
    else
    {
        return val;
    }
}
