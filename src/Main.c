#include <stdio.h>
#include <stdlib.h>
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

void code(){
	Action action;
	Quadtree qt;
	Image info;

	MLV_create_window("Pixel", "Pixel", MAX_SCREEN_X, MAX_SCREEN_Y);

	action = NONE;
	qt = NULL;
	while(action != QUIT){
		action = menu(MAX_SCREEN_X, MAX_SCREEN_Y);
		choice(action, &info, &qt);
	}

	free_quadtree(&qt);
	MLV_free_window();
}

int main(int argc, char const *argv[]){
	code();
	return 0;
}
