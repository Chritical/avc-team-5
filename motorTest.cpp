#include <stdio.h>
#include <time.h>
#include "E101.h"

int main() {

init();
set_motor(1,255);
set_motor(2,255);
sleep1(0,500000);
stop(1);
stop(2);
return0;}
