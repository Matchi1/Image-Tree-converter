#ifndef __PIXEL__
#define __PIXEL__

#include "Color.h"

typedef struct {
	int x, y, length;
	int* color;
} Pixel;

/**
 * @brief Create a Pixel.
 * @param x position of the pixel in the x axis.
 * @param y position of the pixel in the y axis.
 * @param length length of the pixel.
 * @ret a Pixel if there is enough memory space else NULL.
 */
Pixel* create_pixel(int x, int y, int length, int* color);

/**
 * @brief Initialize a Pixel
 * @param p a pointor to a Pixel
 * @param x position in the x axis
 * @param y position in the y axis
 * @param length length of the side of the Pixel
 */
void init_pixel(Pixel* p, int x, int y, int length, int* color);

/**
 * @brief Display element in a pixel.
 * @param p a pointor to a Pixel
 */
void display_pixel(Pixel* p);

/**
 * @brief Draw a pixel into an MLV window
 * @param pixel a pointor to a Pixel structure
 */
void draw_pixel(Pixel* pixel);

/**
 * @brief Free a Pixel structure
 * @param p a pointor to a Pixel structure
 */
void free_pixel(Pixel* p);

#endif
