#include <stdio.h>
#include "../include/Figures.h"

static char* str_actions[] = {
	"select image",
	"save image Black & White",
	"save image rgba",
	"Minimize Quadtree",
	"save minimized Black & White",
	"save minimized rgba",
	"test",
	"quit",
	NULL
};

void init_button(Figure* b, int x, int y, int length_x, int length_y,
		Action act, char* text, MLV_Color color){
	b->x = x;
	b->y = y;
	b->length_x = length_x;
	b->length_y = length_y;
	b->action = act;
	b->text = text;
	b->color = color;
}

Figure* create_button(int x, int y, int length_x, int length_y, Action act,
		char* text, MLV_Color color){
	Figure* b;

	b = (Figure*)malloc(sizeof(Figure));
	if(NULL == b)
		return NULL;
	init_button(b, x, y, length_x, length_y, act, text, color);
	return b;
}

void draw_button(Figure* button){
	MLV_draw_filled_rectangle(
			button->x, button->y,
			button->length_x, button->length_y,
			button->color
			);
	MLV_draw_text(
			button->x, button->y,
			str_actions[button->action], MLV_COLOR_BLACK
			);
}

void display_button_info(Figure* b){
	printf("Position : %d %d\n", b->x, b->y);
	printf("Length : %d %d\n", b->length_x, b->length_y);
}

void free_button(Figure* b){
	free(b);
}
