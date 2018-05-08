#include <stdio.h>
#include <time.h>
#include "E101.h"

int main() {

	init();
	parameter = 0;
	
	if (something < 0){
		parameter = 1;
	}
	else if (something > 0){
		parameter = 2:
	}
	else {
		something == 0;
	}
	
	if (parameter == 1){
		set_motor(1,127);
		set_motor(2,-127);
	}
	else if (parameter == 2){
		set_motor(1,-127);
		set_motor(2,127);
	}
	else if (parameter == 0){
		set_motor(1,127):
		set_motor(2,127);
	}
	
return0;}
