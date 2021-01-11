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
#include "../include/Menu.h"
#include "../include/Buttons.h"
#include "../include/Actions.h"
#include "../include/Image.h"

void select_menu(int* choice){
	printf("1: Test\n");
	printf("2: Produce Quadtree for B&W image\n");
	printf("3: Produce Quadtree for Colorful image\n");
	scanf("%d", choice);
}

void presentation(){
	Quadtree qt;
	MLV_Image* img;
	char* file_name = "img/img1.jpg";
	MLV_create_window("Pixel", "Pixel", MAXPIXEL, MAXPIXEL);

	qt = NULL;
	img = MLV_load_image(file_name);
	if(img == NULL){
		fprintf(stderr, "Image not found !!!\n");
		return;
	}
	MLV_resize_image(img, MAXPIXEL, MAXPIXEL);
	MLV_draw_image(img, 0, 0);

	MLV_actualise_window();
	MLV_wait_seconds(2);

	MLV_clear_window(MLV_COLOR_BLACK);
	MLV_actualise_window();
	convert_img_qt(img, &qt);
	
	MLV_wait_seconds(1);
	MLV_free_window();
}

void basic_menu(int choice){
	switch(choice){
		case 1:
			test(); break;
		case 2:
			presentation(); break;
		default:
			presentation(); break;
	}
}

int main(int argc, char const *argv[]){
	Action action;
	Quadtree qt;
	Image info;

	MLV_create_window("Pixel", "Pixel", MAX_SCREEN_X, MAX_SCREEN_Y);

	action = NONE;
	while(action != QUIT){
		action = menu(MAX_SCREEN_X, MAX_SCREEN_Y);
		choice(action, &info, &qt);
	}

	MLV_free_window();
	return 0;
}
