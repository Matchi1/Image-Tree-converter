#include <stdio.h>
#include "../include/Minimisation.h"

void init_colors(Node* node, int* c1, int* c2, int* c3, int* c4){
	if(node->sonNW->pixel != NULL)
		c1 = node->sonNW->pixel->color;
	if(node->sonNE->pixel != NULL)
		c2 = node->sonNE->pixel->color;
	if(node->sonSE->pixel != NULL)
		c3 = node->sonSE->pixel->color;
	if(node->sonSW->pixel != NULL)
		c4 = node->sonSW->pixel->color;
}

int minimisation(Quadtree* qt){
	int* c1;
	int* c2;
	int* c3;
	int* c4;
	int* color;

	c1 = c2 = c3 = c4 = color = NULL;
	if(*qt == NULL)
		return 1;
	if(is_leave(*qt))
		return 1;
	else {
		if(minimisation(&(*qt)->sonNW) == 0 || minimisation(&(*qt)->sonNE) == 0
				|| minimisation(&(*qt)->sonSE) == 0 || minimisation(&(*qt)->sonSW) == 0)
			return 0;
		init_colors(*qt, c1, c2, c3, c4);
		if(color_equals(c1, c2) == 1 && color_equals(c1, c3) == 1 && color_equals(c1, c4) == 1){
			color = create_color(c1[0], c1[1], c1[2], c1[3]);
			if(NULL == color){
				fprintf(stderr, "Not enough space memory\n");
				return 0;
			}
			(*qt)->pixel = create_pixel(0, 0, 1, color);
		}
	}
	printf("Minimisation OK");
	return 1;
}
