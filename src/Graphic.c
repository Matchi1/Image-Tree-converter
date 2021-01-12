#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include "../include/Pixel.h"
#include "../include/Graphic.h"
#include "../include/Buttons.h"

void graphic_quadtree(int origin_x, int origin_y, int length, Quadtree qt){
	int	new_length = length / 2;
	if(is_leave(qt)){
		init_pixel(qt->pixel, origin_x, origin_y, length, qt->pixel->color);	
		draw_pixel(qt->pixel);
		MLV_actualise_window();
	} else {
		graphic_quadtree(origin_x, origin_y, new_length, qt->sonNW);
		graphic_quadtree(origin_x + new_length, origin_y, new_length, qt->sonNE);
		graphic_quadtree(origin_x + new_length, origin_y + new_length, new_length, qt->sonSE);
		graphic_quadtree(origin_x, origin_y + new_length, new_length, qt->sonSW);
	}
}
