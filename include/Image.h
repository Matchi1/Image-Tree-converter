#ifndef __IMAGE__
#define __IMAGE__

#include <MLV/MLV_all.h>
#include "Quadtree.h"

typedef struct {
	char* file_name;
	MLV_Image* img;
	Quadtree* qt;
}Image;

char* path_image(char* file_name);

MLV_Image* load_image(char* file_name);

void init_image(Image* info, char* file_name);

#endif
