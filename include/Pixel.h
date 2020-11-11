#ifndef __PIXEL__
#define __PIXEL__

typedef struct {
	int x, y;
	int length;
} Pixel;

/**
 * Create a Pixel.
 * @parameters x position of the pixel in the x axis.
 * 			   y position of the pixel in the y axis.
 * 			   length length of the pixel.
 * @return a Pixel if there is enough memory space else NULL.
 */
Pixel* create_pixel(int x, int y, int length);

/**
 * Initialize a Pixel
 * @argument p a pointor to a Pixel
 * 			 x position in the x axis
 * 			 y position in the y axis
 * 			 length length of the side of the Pixel
 * @return void
 */
void init_pixel(Pixel* p, int x, int y, int length);

/**
 * Display element in a pixel.
 * @argument p a pointor to a Pixel
 * @return void
 */
void display_pixel(Pixel* p);

#endif
