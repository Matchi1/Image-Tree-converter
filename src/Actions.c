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
#include "../include/Test.h"

#define SAVE_COLOR 1
#define SAVE_BW 0

/**
 * Initialize an MLV_Input_box structure.
 * @param box a pointor to a pointor of MLV_Input_box structure
 */
void init_box(MLV_Input_box** box){
	*box = MLV_create_input_box(
			DEFAULT_POS_X, DEFAULT_POS_Y, 
			DEFAULT_INPUT_LEN_X, DEFAULT_INPUT_LEN_Y, 
			DEFAULT_INPUT_BORDER, MLV_COLOR_BLACK, DEFAULT_INPUT_BG,
			"Input an image name : "
		);
} 

/**
 * Convert an image contained in a file
 * into a Quadtree.
 * @param info a pointor to an Image structure
 * 		  qt a pointor to a Quadtree structure
 */
void convert(Image* info, Quadtree* qt){
	if(NULL == *qt)
		free_quadtree(qt);
	if(extension_qt(info->file_name) != -1){
		decompression(info->file_name, qt);
		MLV_clear_window(MLV_COLOR_BLACK);
		graphic_quadtree(0, 0, *qt);
		MLV_wait_seconds(2);
	} else 
		convert_img_qt(info->img, qt);
}

/**
 * Select the file image according to the information
 * in the Image structure
 * @param info a pointor to an Image structure
 */
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

/**
 * Save the rgba representation of an image by a Quadtree structure
 * into a file.
 * @param info a pointor to an Image structure
 * 		  qt a Quadtree structure
 */
void save_color(Image* info, Quadtree qt){
	char* path_save;
	path_save = extension_save_file(info->file_name, 1);
	compression(path_save, qt);
}

/**
 * Save the black and white representation of an image 
 * by a Quadtree structure into a file.
 * @param info a pointor to an Image structure
 * 		  qt a Quadtree structure
 */
void save_bw(Image* info, Quadtree qt){
	char* path_save;
	path_save = extension_save_file(info->file_name, 0);
	compression(path_save, qt);
}

/**
 * Save the minimized Quadtree into a GMC file
 * @param info a pointor to the Image structure
 * 		  qt a pointor to a Quadtree
 */
void min_color(Image* info, Quadtree qt){
	char* path_save;
	path_save = extension_save_min(info->file_name, 1);
	compression(path_save, qt);
}

/**
 * Save the minimized Quadtree into a GMN file
 * @param info a pointor to the Image structure
 * 		  qt a pointor to a Quadtree
 */
void min_bw(Image* info, Quadtree qt){
	char* path_save;
	path_save = extension_save_min(info->file_name, 0);
	compression(path_save, qt);
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
		case MIN:
			minimisation(qt);
			break;
		case SAVE_MIN_C: 
			min_color(info, *qt);
			break;
		case SAVE_MIN_N:
			min_bw(info, *qt);
			break;
		case TEST:
			if(test())
				printf("Test successful !!\n");
			else
				printf("Test failed !!\n");
			break;
		default: break;
	}
}
