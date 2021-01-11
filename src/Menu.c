#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "../include/Menu.h"
#include "../include/Buttons.h"

#define NB_BUTTONS 5
#define INITIAL_Y 20
#define TEXT_SELECT "select image"
#define TEXT_SAVE_N "save image Black & White"
#define TEXT_SAVE_C "save image rgba"
#define TEXT_QUIT "quit"
#define TEXT_MINIMISATION "minimize quadtree"

void init_menu_button(Button* arr_buttons){
	init_button(&(arr_buttons[0]), DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_LEN_X, DEFAULT_LEN_Y, DEFAULT_BOOL_PRESS, SELECT, TEXT_SELECT, DEFAULT_COLOR);	
	init_button(&(arr_buttons[1]), DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_LEN_X, DEFAULT_LEN_Y, DEFAULT_BOOL_PRESS, SAVE_N, TEXT_SAVE_N, DEFAULT_COLOR);	
	init_button(&(arr_buttons[2]), DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_LEN_X, DEFAULT_LEN_Y, DEFAULT_BOOL_PRESS, SAVE_C, TEXT_SAVE_C, DEFAULT_COLOR);	
	init_button(&(arr_buttons[3]), DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_LEN_X, DEFAULT_LEN_Y, DEFAULT_BOOL_PRESS, MINIMI, TEXT_MINIMISATION, DEFAULT_COLOR);	
	init_button(&(arr_buttons[4]), DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_LEN_X, DEFAULT_LEN_Y, DEFAULT_BOOL_PRESS, QUIT, TEXT_QUIT, DEFAULT_COLOR);	
}

void align_buttons(int screen_x, int screen_y, Button* arr_buttons){
	int i, x, y;
	for(i = 0; i < NB_BUTTONS; i++){
		x = (screen_x - arr_buttons[i].length_x) / 2;
		if(i == 0)
			y = INITIAL_Y;	
		else 
			y = arr_buttons[i - 1].y + arr_buttons [i - 1].length_y + GAP;
		arr_buttons[i].x = x;
		arr_buttons[i].y = y;
	}
}

void draw_buttons(Button* arr_buttons){
	int i;
	for(i = 0; i < NB_BUTTONS; i++)
		draw_button(&(arr_buttons[i]));
	MLV_actualise_window();
}

int click_on_buttons(int x, int y, Button* arr_buttons){
	int i, x_min, x_max, y_min, y_max;
	for(i = 0; i < NB_BUTTONS; i++){
		x_min = arr_buttons[i].x;
		x_max = arr_buttons[i].x + arr_buttons[i].length_x;
		y_min = arr_buttons[i].y;
		y_max = arr_buttons[i].y + arr_buttons[i].length_y;
		if(x_min <= x && x <= x_max && y_min <= y && y <= y_max)
			return arr_buttons[i].action;
	}
	return -1;
}

Action menu(int screen_x, int screen_y){
	Button arr_buttons[NB_BUTTONS];
	int x, y;
	Action value;

	value = -1;
	init_menu_button(arr_buttons);
	align_buttons(screen_x, screen_y, arr_buttons);

	MLV_clear_window(MLV_COLOR_BLACK);
	draw_buttons(arr_buttons);

	while(1){
		MLV_wait_mouse_or_seconds(&x, &y, 2);
		value = click_on_buttons(x, y, arr_buttons);
		if(value != -1)
			break;
	}
	MLV_actualise_window();
	return value;
}
