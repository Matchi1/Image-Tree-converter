#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/Pixel.h"

void init_pixel(Pixel* p, int x, int y, int length){
	p->x = x;
	p->y = y;
	p->length = length;
}

void display_pixel(Pixel* p){
	printf("x : %d\n", p->x);
	printf("y : %d\n", p->y);
	printf("length : %d\n", p->length);
}
