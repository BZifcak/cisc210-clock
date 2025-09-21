#include "display.h"
#include <stdio.h>
#include <linux/input.h>
#include "sense.h"
void mode_function(unsigned int code);
int mainMode = 1;
int main(void){
	pi_joystick_t* joystick=getJoystickDevice();
	int h;
	int m;
	int s;
	int running = 3;
	open_display();	
	while(running == 3){

		running = scanf("%d:%d:%d",&h,&m,&s);
		pollJoystick(joystick,mode_function,1000);
		display_time(h,m,s,mainMode);
	}
	close_display();
	return 0;
}
void mode_function(unsigned int code){
	mainMode = !mainMode;	
}
