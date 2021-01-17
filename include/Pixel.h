#ifndef __PIXEL__
#define __PIXEL__

#include "Color.h"

typedef struct {
	int x, y, length;
	int* color;
} Pixel;

/**
 * Create a Pixel.
 * @parameters x position of the pixel in the x axis.
 * 			   y position of the pixel in the y axis.
 * 			   length length of the pixel.
 * @return a Pixel if there is enough memory space else NULL.
 */
Pixel* create_pixel(int x, int y, int length, int* color);

/**
 * Initialize a Pixel
 * @parameters p a pointor to a Pixel
 * 			 x position in the x axis
 * 			 y position in the y axis
 * 			 length length of the side of the Pixel
 * @return void
 */
void init_pixel(Pixel* p, int x, int y, int length, int* color);

/**
 * Display element in a pixel.
 * @parameters p a pointor to a Pixel
 * @return void
 */
void display_pixel(Pixel* p);

/**
 * Draw a pixel into an MLV window
 * @param pixel a pointor to a Pixel structure
 */
void draw_pixel(Pixel* pixel);

/**
 * Free a Pixel structure
 * @param p a pointor to a Pixel structure
 */
void free_pixel(Pixel* p);

#endif
