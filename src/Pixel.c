#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include "../include/Pixel.h"
#include "../include/Graphic.h"
#include "../include/Window.h"

Pixel* create_pixel(int x, int y, int length, int *color){
	Pixel* pixel = (Pixel *)malloc(sizeof(Pixel));

	if(pixel == NULL)
		return NULL;

	init_pixel(pixel, x, y, length, color);
	return pixel;
}

void init_pixel(Pixel *p, int x, int y, int length, int *color){
	p->x = x;
	p->y = y;
	p->length = length;
	p->color = color;
}

void draw_pixel(Pixel* pixel){
	MLV_Color color;
	int* c = pixel->color;
	int origin_x, origin_y;

	origin_x = (WINDOW_W - IMAGE_SIZE) / 2;
	origin_y = (WINDOW_H - IMAGE_SIZE) / 2;
	color = MLV_convert_rgba_to_color(c[0], c[1], c[2], c[3]);
	MLV_draw_filled_rectangle(
			pixel->x + origin_x, pixel->y + origin_y,
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

void free_pixel(Pixel* p){
	free_color(p->color);
	free(p);
	p = NULL;
}
