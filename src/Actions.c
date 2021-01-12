#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "../include/Minimisation.h"
#include "../include/Compression.h"
#include "../include/Decompression.h"
#include "../include/Input_img.h"
#include "../include/Graphic.h"
#include "../include/Buttons.h"
#include "../include/Image.h"
#include "../include/Extension.h"

#define SAVE_COLOR 1
#define SAVE_BW 0

void init_box(MLV_Input_box** box){
	*box = MLV_create_input_box(
			DEFAULT_POS_X, DEFAULT_POS_Y, 
			DEFAULT_INPUT_LEN_X, DEFAULT_INPUT_LEN_Y, 
			DEFAULT_INPUT_BORDER, MLV_COLOR_BLACK, DEFAULT_INPUT_BG,
			"Input an image name : "
		);
} 

void draw_center_image(MLV_Image* img){
	int x, y;

	x = (MAX_SCREEN_X - MAXPIXEL) / 2;
	y = (MAX_SCREEN_Y - MAXPIXEL) / 2;
	MLV_draw_image(img, x, y);
	MLV_actualise_window();
	MLV_wait_seconds(2);
}

void convert(Image* info, Quadtree* qt){
	if(extension_qt(info->file_name) != -1){
		decompression(info->file_name, qt);
		MLV_clear_window(MLV_COLOR_BLACK);
		graphic_quadtree(0, 0, MAXPIXEL, *qt);
		MLV_wait_seconds(2);
	} else 
		convert_img_qt(info->img, qt);
}

void select_image(Image* info){
	MLV_Input_box* box;
	char* file_name;

	init_box(&box);
	MLV_clear_window(MLV_COLOR_BLACK);
	MLV_activate_input_box(box);
	MLV_wait_particular_input_box(box, &file_name);

	init_image(info, file_name);
	MLV_free_input_box(box);
	if(info->img != NULL)
		draw_center_image(info->img);
}

void save_color(Image* info, Quadtree qt){
	char* path_save;
	path_save = extension_save_file(info->file_name, 1);
	compression(path_save, qt);
}

void save_bw(Image* info, Quadtree qt){
	char* path_save;
	path_save = extension_save_file(info->file_name, 0);
	compression(path_save, qt);
}

void minimize(Quadtree* qt){
	minimisation(qt);
}

void choice(Action action, Image* info, Quadtree* qt){
	switch(action){
		case SELECT:
			select_image(info);
			convert(info, qt);
			break;
		case SAVE_C:
			save_color(info, *qt);
			break;
		case SAVE_N: 
			save_bw(info, *qt);
			break;
		case MINIMI: 
			minimize(qt);
			break;

		default: break;
	}
}
