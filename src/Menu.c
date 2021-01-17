#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "../include/Menu.h"
#include "../include/Buttons.h"

#define NB_BUTTONS 8
#define INITIAL_Y 20
#define TEXT_SELECT "select image"
#define TEXT_SAVE_N "save image Black & White"
#define TEXT_SAVE_C "save image rgba"
#define TEXT_MIN "Minimize Quadtree"
#define TEXT_MIN_N "save minimized Black & White"
#define TEXT_MIN_C "save minimized rgba"
#define TEXT_TEST "test"
#define TEXT_QUIT "quit"

/**
 * Initialize the buttons necessary for the menu
 * @param arr_buttons an array of Button structure
 */
void init_menu_button(Button* arr_buttons){
	init_button(&(arr_buttons[0]), DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_LEN_X, DEFAULT_LEN_Y, SELECT, TEXT_SELECT, DEFAULT_COLOR);	
	init_button(&(arr_buttons[1]), DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_LEN_X, DEFAULT_LEN_Y, SAVE_N, TEXT_SAVE_N, DEFAULT_COLOR);	
	init_button(&(arr_buttons[2]), DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_LEN_X, DEFAULT_LEN_Y, SAVE_C, TEXT_SAVE_C, DEFAULT_COLOR);	
	init_button(&(arr_buttons[3]), DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_LEN_X, DEFAULT_LEN_Y, MIN, TEXT_MIN, DEFAULT_COLOR);	
	init_button(&(arr_buttons[4]), DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_LEN_X, DEFAULT_LEN_Y, SAVE_MIN_N, TEXT_MIN_N, DEFAULT_COLOR);	
	init_button(&(arr_buttons[5]), DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_LEN_X, DEFAULT_LEN_Y, SAVE_MIN_C, TEXT_MIN_C, DEFAULT_COLOR);	
	init_button(&(arr_buttons[6]), DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_LEN_X, DEFAULT_LEN_Y, TEST, TEXT_TEST, DEFAULT_COLOR);	
	init_button(&(arr_buttons[7]), DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_LEN_X, DEFAULT_LEN_Y, QUIT, TEXT_QUIT, DEFAULT_COLOR);	
}

/**
 * Align the buttons on the center of the screen
 * @param width width of the window
 * 		  height height of the window
 * 		  arr_buttons an array of Button structure
 */
void align_buttons(int width, int height, Button* arr_buttons){
	int i, x, y;
	for(i = 0; i < NB_BUTTONS; i++){
		x = (width - arr_buttons[i].length_x) / 2;
		if(i == 0)
			y = INITIAL_Y;	
		else 
			y = arr_buttons[i - 1].y + arr_buttons [i - 1].length_y + GAP;
		arr_buttons[i].x = x;
		arr_buttons[i].y = y;
	}
}

/**
 * Draw the buttons of the menu 
 * @param arr_buttons an array of Button structure
 */
void draw_buttons(Button* arr_buttons){
	int i;
	for(i = 0; i < NB_BUTTONS; i++)
		draw_button(&(arr_buttons[i]));
	MLV_actualise_window();
}

/**
 * Verify if a button have been pressed by the user with a mouse click
 * @param x the position of the click in the X axis
 * 	   	  y the position of the click in the Y axis
 * 	   	  arr_buttons an array of Button structure
 * @return the associated Action of the button else -1
 */
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

/**
 * Enter into the menu of the project
 * This menu display the action that can be done by the program
 * @param width width of the window
 * 		  height height of the window
 * @return the action choosen by the user
 */
Action menu(int width, int height){
	Button arr_buttons[NB_BUTTONS];
	int x, y;
	Action value;

	value = -1;
	init_menu_button(arr_buttons);
	align_buttons(width, height, arr_buttons);

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
