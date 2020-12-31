#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include "../include/Input_img.h"
#include "../include/Calcul.h"
#include "../include/Hashtable.h"
#include "../include/Graphic.h"


Node* max_error_node(List* ht){
	int i;
	Node* max_error_node;
	
	max_error_node = (*ht)->node;
	for(i = 0; i < HT_MAX_LEN; i++){
		if(ht[i] != NULL && max_error_node->error_val < ht[i]->node->error_val)
			max_error_node = ht[i]->node;
	}	
	return max_error_node;
}

void init_areas(Pixel** area1, Pixel** area2, Pixel** area3, Pixel** area4, Node* next_divide){
	Pixel* pixel;
	int len;
	pixel = next_divide->pixel;
	if(pixel->length >= 2)
		len = pixel->length / 2;
	else
		len = pixel->length;
	*area1 = create_pixel(pixel->x, pixel->y, len, NULL);
	*area2 = create_pixel(pixel->x + len, pixel->y, len, NULL);
	*area3 = create_pixel(pixel->x + len, pixel->y + len, len, NULL);
	*area4 = create_pixel(pixel->x, pixel->y + len, len, NULL);
}

int divide_pixel(MLV_Image* img, Node** node, Pixel* ref, int bw){
	int error_val;

	average_color(img, ref, bw);
	error_val = error(img, ref, bw); 
	if((*node = create_node(ref, error_val)) == NULL)
		return 0;
	return 1;
}

void input_init_sons(MLV_Image* img, Node* node, Pixel* area1, Pixel* area2, Pixel* area3, Pixel* area4, int bw){
	divide_pixel(img, &(node->sonNW), area1, bw);
	divide_pixel(img, &(node->sonNE), area2, bw);
	divide_pixel(img, &(node->sonSE), area3, bw);
	divide_pixel(img, &(node->sonSW), area4, bw);
}

void add_ht_sons(List* ht, Node* node){
	add_ht_node(ht, node->sonNW);
	add_ht_node(ht, node->sonNE);
	add_ht_node(ht, node->sonSE);
	add_ht_node(ht, node->sonSW);
}

void draw_sons(Node* node){
	draw_pixel(node->sonNW->pixel);
	draw_pixel(node->sonNE->pixel);
	draw_pixel(node->sonSE->pixel);
	draw_pixel(node->sonSW->pixel);
	MLV_actualise_window();
}

void input_create_qt_aux(MLV_Image* img, List* ht, int bw){
	Node* next_divide;
	Pixel* area1;
	Pixel* area2;
	Pixel* area3;
	Pixel* area4;

	area1 = area2 = area3 = area4 = NULL;
	do {
		next_divide = max_error_node(ht);											/* Find the pixel with the biggest error in the current Quadtree */
		init_areas(&area1, &area2, &area3, &area4, next_divide);
		input_init_sons(img, next_divide, area1, area2, area3, area4, bw); 			/* Initialize the 4 areas of the initial pixel*/
		add_ht_sons(ht, next_divide); 												/* Add sons of this node to the HashTable*/
		remove_ht_node(ht, next_divide);											/* Remove this node from the HashTable */
		draw_sons(next_divide);
	} while(next_divide->error_val != 0);
}

int input_create_qt(MLV_Image* img, Quadtree* qt, int bw){
	List* ht;
	Pixel* first;

	assert(img != NULL);
	ht = create_ht();
	if(ht == NULL)
		return 0;
	first = create_pixel(0, 0, MAXPIXEL, NULL);
	if(first == NULL)
		return 0;

	divide_pixel(img, qt, first, bw);	
	add_ht_node(ht, *qt);
	input_create_qt_aux(img, ht, bw);
	free_ht(ht);
	return 1;
}

int convert_img_qt(MLV_Image* img, Quadtree* qt, int bw){
	assert(img != NULL);
	assert(qt != NULL);

	if(input_create_qt(img, qt, bw) == 0)
		return 0;
	return 1;
}
