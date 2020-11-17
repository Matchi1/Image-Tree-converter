#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include <math.h>
#include "../include/Calcul.h"
#include "../include/Pixel.h"

int math_square(int value){
	return ( value ) * ( value );
}

float dist(const Color* c1, const Color* c2){
	float distance;
	float r, g, b, a;
	float r2, g2, b2, a2;

	r = c1->r - c2->r;
	g = c1->g - c2->g;
	b = c1->b - c2->b;
	a = c1->a - c2->a;
	r2 = math_square(r);
	g2 = math_square(g);
	b2 = math_square(b);
	a2 = math_square(a);

	distance = sqrt(r2 + g2 + b2 + a2);
	return distance;	
}

void average_color(MLV_Image* img, Pixel* area){
	int i, j, div;
	int r, g, b, a;
	long int r_sum, g_sum, b_sum, a_sum;
	int avr_rgba[4];

	assert(area != NULL);
	r_sum = g_sum = b_sum = a_sum = 0;
	avr_rgba[0] = avr_rgba[1] = avr_rgba[2] = avr_rgba[3] = 0;
	for(i = 0; i < area->length; i++){
		for(j = 0; j < area->length; j++){
			MLV_get_pixel_on_image(img, area->x + i, area->y + j, &r, &g, &b, &a);
			r_sum += r;
			g_sum += g;
			b_sum += b;
			a_sum += a;
		}
	}
	div = area->length * area->length;
	avr_rgba[0] = r_sum / div;
	avr_rgba[1] = g_sum / div;
	avr_rgba[2] = b_sum / div;
	avr_rgba[3] = a_sum / div;
	area->color = create_color(avr_rgba);
}

int error(MLV_Image* img, Pixel* area){
	int i, j, error;
	int rgba[4];
	Color color;
	
	error = 0;
	for(i = 0; i < area->length; i++){
		for(j = 0; j < area->length; j++){
			MLV_get_pixel_on_image(
					img,
					area->x + i, area->y + j, 
					&rgba[0], &rgba[1], &rgba[2], &rgba[3]
					);
			init_color(&color, rgba);
			error += dist(&color, area->color);	
		}
	}
	return error;
}
