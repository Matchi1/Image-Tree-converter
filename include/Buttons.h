#ifndef __BUTTONS__
#define __BUTTONS__

#include <MLV/MLV_all.h>
#include "Actions.h"

#define DEFAULT_LEN_X 200
#define DEFAULT_LEN_Y 40
#define DEFAULT_POS_X 0
#define DEFAULT_POS_Y 0
#define DEFAULT_COLOR MLV_COLOR_WHITE
#define DEFAULT_INPUT_LEN_X 400
#define DEFAULT_INPUT_LEN_Y 40
#define DEFAULT_INPUT_BORDER MLV_COLOR_BLUE
#define DEFAULT_INPUT_BG MLV_COLOR_WHITE
#define GAP 20

typedef struct {
	int x, y;
	int length_x, length_y;
	char* text;
	Action action;
	MLV_Color color;
}Button;

/**
 * Draw the Button structure into an MLV window
 * @param button a pointor to a Button structure
 */
void draw_button(Button* button);

/**
 * Initialize a Button structure
 * @param b a pointor to a Button structure
 * 		  x the position of the button in the X axis
 * 		  y the position of the button in the Y axis
 * 		  width width of the button
 * 		  height height of the button
 * 		  act the action that this button imply
 * 		  text the text that represent the button
 * 		  color background color of the button
 */
void init_button(Button* b, int x, int y, int length_x, int length_y, Action act, char* text, MLV_Color color);

/**
 * Initialize a Button structure
 * @param x the position of the button in the X axis
 * 		  y the position of the button in the Y axis
 * 		  width width of the button
 * 		  height height of the button
 * 		  act the action that this button imply
 * 		  text the text that represent the button
 * 		  color background color of the button
 * @return a pointor to a button if there is enough memory space else NULL
 */
Button* create_button(int x, int y, int length_x, int length_y, Action act, char* text, MLV_Color color);

/**
 * Display all the information in a Button structure
 * @param b a pointor to a Button structure
 */
void display_button_info(Button* b);

#endif
