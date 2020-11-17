#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include "../include/Graphic.h"
#include "../include/Quadtree.h"
#include "../include/Compression.h"
#include "../include/Decompression.h"
#include "../include/Test.h"
#include "../include/Input_img.h"
#include "../include/Hashtable.h"
#include "../include/Calcul.h"

int main(int argc, char const *argv[]){
	Quadtree qt;
	MLV_Image* img;
	char* file_name = "img/img1.jpg";

	MLV_create_window("Pixel", "Pixel", MAXPIXEL, MAXPIXEL);

	qt = NULL;
	img = MLV_load_image(file_name);
	MLV_resize_image(img, MAXPIXEL, MAXPIXEL);
	MLV_draw_image(img, 0, 0);

	MLV_actualise_window();
	MLV_wait_seconds(2);
	MLV_clear_window(MLV_COLOR_BLACK);
	MLV_actualise_window();
	convert_img_qt(img, &qt);
	
	MLV_wait_seconds(1);
	MLV_free_window();
	return 0;
}
