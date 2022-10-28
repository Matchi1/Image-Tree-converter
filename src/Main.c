#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "../include/Graphic.h"
#include "../include/Quadtree.h"
#include "../include/Compression.h"
#include "../include/Decompression.h"
#include "../include/Test.h"
#include "../include/Input.h"
#include "../include/Hashtable.h"
#include "../include/Calcul.h"
#include "../include/Menu.h"
#include "../include/Figures.h"
#include "../include/Actions.h"
#include "../include/Image.h"
#include "../include/Window.h"

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

	MLV_create_window("Pixel", "Pixel", WINDOW_W, WINDOW_H);

	action = NONE;
	qt = NULL;
	while(action != QUIT){
		action = menu(WINDOW_W, WINDOW_H);
		choice(action, &info, &qt);
	}

	free_quadtree(&qt);
	MLV_free_window();
}

int main(int argc, char const *argv[]){
	code();
	return 0;
}
