#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include <math.h>
#include "../include/Calcul.h"
#include "../include/Pixel.h"

int math_square(int value){
	return value * value;
}

float dist(const Color* c1, const Color* c2){
	float distance;
	int r2, g2, b2, a2;

	r2 = math_square(c1->r - c2->r);
	g2 = math_square(c1->g - c2->g);
	b2 = math_square(c1->b - c2->b);
	a2 = math_square(c1->a - c2->a);

	distance = sqrt(r2 + g2 + b2 + a2);
	return distance;	
}

Color* average_color(int len_arr, Pixel* arr_pixel){
	int i;
	int rgba[4];
	
	rgba[0] = rgba[1] = rgba[2] = rgba[3] = 0;
	for(i = 0; i < len_arr; i++){
		rgba[0] += arr_pixel[i].color->r;
		rgba[1] += arr_pixel[i].color->g;
		rgba[2] += arr_pixel[i].color->b;
		rgba[3] += arr_pixel[i].color->a;
	}

	rgba[0] *= len_arr;
	rgba[1] *= len_arr;
	rgba[2] *= len_arr;
	rgba[3] *= len_arr;
	return create_color(rgba);
}

int error(MLV_Image* img, Pixel* area){
	int i, j, error;
	int rgba[4];
	Color color;
	
	error = 0;
	for(i = 0; i < area->length; i++){
		for(j = 0; j < area->length; j++){
			MLV_get_pixel(
					area->x + i, area->y + j, 
					&rgba[0], &rgba[1], &rgba[2], &rgba[3]
					);
			init_color(&color, rgba);
			error += dist(&color, area->color);	
		}
	}
	return error;
}
