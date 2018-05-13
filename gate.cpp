#include <stdio.h>
#include "E101.h"

int gateOpen();

int main(){
	init();
	gateOpen();
	return 0;
}

int gateOpen(){
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
