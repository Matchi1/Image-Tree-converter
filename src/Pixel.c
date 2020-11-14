#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
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

void display_pixel(Pixel* p){
	printf("x : %d\n", p->x);
	printf("y : %d\n", p->y);
	printf("length : %d\n", p->length);
	display_color(p->color);
}
