#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include "../include/Color.h"

void init_color(int* rgba, int r, int g, int b, int a){
	rgba[0] = r;
	rgba[1] = g;
	rgba[2] = b;
	rgba[3] = a;
}

void init_color_BW(int* color, int bw){
	assert(color != NULL);
	if(bw == 1)
		init_color(color, 255, 255, 255, color[3]);
	else
		init_color(color, 0, 0, 0, color[3]);
}

int* create_color(int r, int g, int b, int a){
	int* rgba;	

	rgba = (int*)malloc(sizeof(int)*4);
	if(rgba == NULL)
		return NULL;
	init_color(rgba, r, g, b, a);
	return rgba;
}

void display_color(int* color){
	if(color != NULL){
		printf("Red : %d\n", color[0]);
		printf("Green : %d\n", color[1]);
		printf("Blue : %d\n", color[2]);
		printf("Alpha : %d\n", color[3]);
	}
}

int verify_color(int* c1, int* c2){
	int i;
	for(i = 0; i < 4; i++){
		if(c1[i] != c2[i])
			return 0;
	}
	return 1;
}

int black_or_white(int* color){
	float avr_gray = 0.2126*color[0] + 0.7152*color[1] + 0.0722*color[2];
	if(avr_gray > 128)
		return 0;
	return 1;
}

int color_equals(int* c1, int* c2){
	int i;
	if(c1 == NULL || c2 == NULL)
		return 0;
	for(i = 0; i < 4; i++){
		if(c1[i] != c2[i])
			return 0;
	}
	return 1;
}

void convert_rgba_to_BW(int* color){
	init_color_BW(color, black_or_white(color));
}

void free_color(int* color){
	free(color);
	color = NULL;
}
