#ifndef __BUTTONS__
#define __BUTTONS__

#include <MLV/MLV_all.h>
#include "Actions.h"

#define DEFAULT_LEN_X 200
#define DEFAULT_LEN_Y 40
#define DEFAULT_BOOL_PRESS 1
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
	int bool_press;
	char* text;
	Action action;
	MLV_Color color;
}Button;

void draw_button(Button* button);

void init_button(Button* b, int x, int y, int length_x, int length_y, int bool_press, Action act, char* text, MLV_Color color);

Button* create_button(int x, int y, int length_x, int length_y, int bool_press, Action act, char* text, MLV_Color color);

void display_button_info(Button* b);

#endif
