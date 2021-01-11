#include <stdio.h>
#include "../include/Buttons.h"

void init_button(Button* b, int x, int y, int length_x, int length_y, int bool_press, Action act, char* text, MLV_Color color){
	b->x = x;
	b->y = y;
	b->length_x = length_x;
	b->length_y = length_y;
	b->bool_press = bool_press;
	b->action = act;
	b->text = text;
	b->color = color;
}

Button* create_button(int x, int y, int length_x, int length_y, int bool_press, Action act, char* text, MLV_Color color){
	Button* b;

	b = (Button*)malloc(sizeof(Button));
	if(NULL == b)
		return NULL;
	init_button(b, x, y, length_x, length_y, bool_press, act, text, color);
	return b;
}

void draw_button(Button* button){
	MLV_draw_filled_rectangle(
			button->x, button->y,
			button->length_x, button->length_y,
			button->color
			);
	MLV_draw_text(
			button->x, button->y,
			button->text, MLV_COLOR_BLACK
			);
}

void display_button_info(Button* b){
	printf("Position : %d %d\n", b->x, b->y);
	printf("Length : %d %d\n", b->length_x, b->length_y);
}
