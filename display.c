#include <unistd.h>
#include <stdlib.h>
#include "sense.h"
#define WHITE 0xFFFF
#define BLACK 0x0000
#define GREEN 0x0f00
#define BLUE 0x0000FF
#define RED 0xF000
#define DIMWHITE 0x8410
#define DIMRED 0x6000
#define DIMBLUE 0x008B
#define DIMGREEN 0x0300


void display_colons(void);
void display_hours(int hours);
void display_minutes(int minutes);
void display_seconds(int seconds);
void displayFunction(int x, int time);
int* binaryConvert(int number);

int display = 1; //variable for the light display settings, one means normal display and zero means dimmed
int mode = 1; //variable for time setting, one means military and zero means standard clock

pi_framebuffer_t *fb = NULL;
sense_fb_bitmap_t *bm = NULL;

int open_display(void){
	fb = getFrameBuffer();
	bm = fb->bitmap;	
	return 1;

}
void display_time(int hours, int minutes, int seconds, int m){
	clearFrameBuffer(fb, BLACK);
	mode = m;
	
	display_hours(hours);
	display_minutes(minutes);
	display_seconds(seconds);
	display_colons();
}
void display_colons(void){
	int colons[][2] = {{2,1},{2,2},{2,4},{2,5},{3,1},{3,2},{3,4},{3,5},{5,1},{5,2},{5,4},{5,5},{6,1},{6,2},{6,4},{6,5}};
	int color = WHITE;
	if (display == 0){
		color = DIMWHITE;
	}
        for (int i = 0; i < 16; i++) {
            int x = (colons[i][1]);
            int y = (colons[i][0]);
            bm->pixel[x][y] = color;
        }	
}
void display_hours(int hours){
	
	if (!mode && hours > 12 ){
		display = 0;
		hours -= 12;
	} else {
		display = 1;
	}
	displayFunction( 6,  hours);	
}
void display_minutes(int minutes){
	displayFunction( 3,  minutes);

}
void display_seconds(int seconds){
	displayFunction( 0,  seconds);

}
void close_display(void){	
	clearFrameBuffer(fb, BLACK);
	freeFrameBuffer(fb); 
}

void displayFunction(int x, int time){
	int color;
	int *binary = binaryConvert(time);
 
	if (display){
		if (x == 6){
			color = BLUE;
		} else if (x==3){
			color = GREEN;
		} else if (x == 0){
			color = RED;
		}
	} else {
		if (x == 6){
			color = DIMBLUE;
		} else if (x==3){
			color = DIMGREEN;
		} else if (x == 0){
			color = DIMRED;
		}
	}
	for( int i = 0; i < 6; i++){
		if (binary[i]){
			bm->pixel[x][i+2] = color;
		}
	}




}
int* binaryConvert(int number){
	int* binary = (int*)malloc(6 * sizeof(int));
	for (int i = 0; i < 6; i++) {
       		binary[i] = 0;
    	}


	for(int i = 5; number > 0; i--){
		binary[i] = number % 2;
		number /= 2;
	}	
	return binary;
}
