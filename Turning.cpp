#include <stdio.h>
#include <time.h>
#include "E101.h"
void TurnLeft(v_left, v_right);
void TurnRight(v_left, v_right);
int main() {
	int final v_go = 64;
	int final Kp = 1;
	dv = error ∗ Kp;
	
	init();
	
	while (true){
		dv = error ∗ Kp;
		v_left = v_go + dv;
		v_right = v_go - dv;

		if (v_left > 255){
			v_left = 255;
		}
		else if (v_right > 255){
			v_right = 255;
		}
		if (error < 1000 && error > 0){
			TurnLeft(v_left, v_right);
		}
		else if (error < 0 && error > -1000){
			TurnRight(v_left, v_right);
		}
		
		else (error > 1000){
			set_motor(1,v_go):
			set_motor(2,v_go);	
		}
		
	}
	
return 0;
}

void TurnLeft(int v_left, int v_right) {
	set_motor(1,v_right);
	set_motor(2,v_left);
}

void TurnRight(int v_left, int v_right) {
	set_motor(1,v_left);
	set_motor(2,v_right);
}
