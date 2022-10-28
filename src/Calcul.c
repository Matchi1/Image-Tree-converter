#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include <math.h>
#include "../include/Calcul.h"
#include "../include/Pixel.h"

/**
 * Return the square of a value
 * @param the value to compute
 * @return the result
 */
int math_square(int value){
	return ( value ) * ( value );
}

float dist(const int* c1, const int* c2){
	float distance;
	float r, g, b, a;

	r = math_square(c1[0] - c2[0]);
	g = math_square(c1[1] - c2[1]);
	b = math_square(c1[2] - c2[2]);
	a = math_square(c1[3] - c2[3]);

	distance = sqrt(r + g + b + a);
	return distance;
}

void average_color(MLV_Image* img, Pixel* area){
	int i, j, nb_pixel;
	int r, g, b, a;
	long int r_sum, g_sum, b_sum, a_sum;
	int* avr_rgba;

	assert(area != NULL);
	avr_rgba = create_color(0, 0, 0, 0);
	r_sum = g_sum = b_sum = a_sum = 0;
	nb_pixel = area->length * area->length;

	/* Add all color into their corresponding color unite (red, green, blue and alpha)*/
	for(i = 0; i < area->length; i++){
		for(j = 0; j < area->length; j++){
			MLV_get_pixel_on_image(img, area->x + i, area->y + j, &r, &g, &b, &a);
			r_sum += r;
			g_sum += g;
			b_sum += b;
			a_sum += a;
		}
	}
	init_color(avr_rgba, r_sum / nb_pixel, g_sum / nb_pixel, b_sum / nb_pixel,
			a_sum / nb_pixel);
	area->color = avr_rgba;
}

int error(MLV_Image* img, Pixel* area){
	int i, j, error;
	int rgba[4];

	error = 0;
	for(i = 0; i < area->length; i++){
		for(j = 0; j < area->length; j++){
			MLV_get_pixel_on_image(
					img,
					area->x + i, area->y + j,
					&rgba[0], &rgba[1], &rgba[2], &rgba[3]
					);
			error += dist(rgba, area->color);
		}
	}
	return error;
}
