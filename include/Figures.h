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

typedef struct fig{
	int x, y;
	int length_x, length_y;
	char* text;
	Action action;
	MLV_Color color;
	struct fig *next;
}Figure;

/**
 * @brief Draw the Figure structure into an MLV window
 * @param button a pointor to a Figure structure
 */
void draw_button(Figure* button);

/**
 * @brief Initialize a Figure structure
 * @param b a pointor to a Figure structure
 * @param x the position of the button in the X axis
 * @param y the position of the button in the Y axis
 * @param width width of the button
 * @param height height of the button
 * @param act the action that this button imply
 * @param text the text that represent the button
 * @param color background color of the button
 */
void init_button(Figure* b, int x, int y, int length_x, int length_y,
		Action act, char *text, MLV_Color color);

/**
 * @brief Initialize a Figure structure
 * @param x the position of the button in the X axis
 * @param y the position of the button in the Y axis
 * @param width width of the button
 * @param height height of the button
 * @param act the action that this button imply
 * @param text the text that represent the button
 * @param color background color of the button
 * @return a pointor to a button if there is enough memory space else NULL
 */
Figure* create_button(int x, int y, int length_x, int length_y, Action act,
		char *text, MLV_Color color);

/**
 * @brief Display all the information in a Figure structure
 * @param b a pointor to a Figure structure
 */
void display_button_info(Figure *b);

#endif
