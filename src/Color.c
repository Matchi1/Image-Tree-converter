#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include "../include/Color.h"

Color* create_color(int* rgba){
	Color* color;

	color = (Color*)malloc(sizeof(Color));
	if(color == NULL)
		return NULL;
	init_color(color, rgba);
	return color;
}

void init_color(Color* color, int* rgba){
	assert(color != NULL);
	color->r = rgba[0];
	color->g = rgba[1];
	color->b = rgba[2];
	color->a = rgba[3];
}

void display_color(Color* color){
	if(color != NULL){
		printf("Red : %d\n", color->r);
		printf("Green : %d\n", color->g);
		printf("Blue : %d\n", color->b);
		printf("Alpha : %d\n", color->a);
	}
}

int verify_color(Color* c1, Color* c2){
	if(c1->r != c2->r || c1->g != c2->g || c1->b != c2->b || c1->a != c2->a)
		return 0;
	return 1;
}
