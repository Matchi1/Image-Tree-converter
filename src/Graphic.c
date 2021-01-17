#include <stdio.h>
#include "../include/Pixel.h"
#include "../include/Graphic.h"
#include "../include/Buttons.h"

void draw_center_image(MLV_Image* img){
	int x, y;

	x = (MAX_SCREEN_X - MAXPIXEL) / 2;
	y = (MAX_SCREEN_Y - MAXPIXEL) / 2;
	MLV_draw_image(img, x, y);
	MLV_actualise_window();
	MLV_wait_seconds(2);
}

/**
 * Draw a pixel in an MLV window 
 * @param origin_x the position of the pixel according to the X axis
 * 		  origin_y the position of the pixel according to the Y axis
 * 		  length represents the width and the height of the pixel
 * 		  qt a Quadtree structure
 */
void graphic_draw_pixel(int origin_x, int origin_y, int length, Quadtree qt){
	int	new_length = length / 2;
	if(is_leave(qt)){
		init_pixel(qt->pixel, origin_x, origin_y, length, qt->pixel->color);	
		draw_pixel(qt->pixel);
		MLV_actualise_window();
	} else {
		graphic_draw_pixel(origin_x, origin_y, new_length, qt->sonNW);
		graphic_draw_pixel(origin_x + new_length, origin_y, new_length, qt->sonNE);
		graphic_draw_pixel(origin_x + new_length, origin_y + new_length, new_length, qt->sonSE);
		graphic_draw_pixel(origin_x, origin_y + new_length, new_length, qt->sonSW);
	}
}

void graphic_quadtree(int origin_x, int origin_y, Quadtree qt){
	graphic_draw_pixel(origin_x, origin_y, MAXPIXEL, qt);
}

