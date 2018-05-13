#include <stdio.h>
#include <time.h>
#include "E101.h"

int main() {
	int final v_go = 64;
	int final Kp = 1;
	dv = error ∗ Kp;
	
	init();
	
	dv = error ∗ Kp;
	v_left = v_go + dv;
	v_right = v_go - dv;
	
	if (v_left > 255){
		v_left = 255;
	}
	if (v_right > 255){
		v_right = 255;
	}
	
	while (error > 0, err > -1000){
		set_motor(1,v_left);
		set_motor(2,v_right);
	}
	while (error < 0, error < 1000){
		set_motor(1,v_left);
		set_motor(2,v_right);
	}
	while (error == 0){
		set_motor(1,v_left):
		set_motor(2,v_right);
	}
	while (error > 1000){
		set_motor(1,0):
		set_motor(2,0);	
	}
	void Turn_Left {
		set_motor(1,v_left);
		set_motor(2,v_right);
	}
return0;}
