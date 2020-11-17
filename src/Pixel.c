#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include "../include/Pixel.h"

Pixel* create_pixel(int x, int y, int length, Color* color){
	Pixel* pixel;

	pixel = (Pixel*)malloc(sizeof(Pixel));

	if(pixel == NULL)
		return NULL;

	init_pixel(pixel, x, y, length, color);
	return pixel;
}

void init_pixel(Pixel* p, int x, int y, int length, Color* color){
	p->x = x;
	p->y = y;
	p->length = length;
	p->color = color;
}

void draw_pixel(Pixel* pixel){
	MLV_Color color;
	Color* c = pixel->color;
	color = MLV_convert_rgba_to_color(c->r, c->g, c->b, c->a);
	MLV_draw_filled_rectangle(
			pixel->x, pixel->y,
			pixel->length, pixel->length,
			color
			);
}

void display_pixel(Pixel* p){
	printf("x : %d\n", p->x);
	printf("y : %d\n", p->y);
	printf("length : %d\n", p->length);
	display_color(p->color);
}
