#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/Input_img.h"
#include "../include/Calcul.h"
#include "../include/Hashtable.h"
#include "../include/Graphic.h"

/**
 * Determine the highest error in the element in a hashtable
 * @param ht the hashtable
 * @return the Node structure containing the highest error value
 */
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

/**
 * Initialize the 4 areas that will divide the current pixel
 * @param area1 a pointor to a pointor to a Pixel structure
 * 		  area2 a pointor to a pointor to a Pixel structure
 *  	  area3 a pointor to a pointor to a Pixel structure
 *  	  area4 a pointor to a pointor to a Pixel structure
 *  	  next_divide a pointor to a Node structure
 */
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

/**
 * Attribute an error value to a new Node structure
 * Information about the current zone of the image are contained
 * in a Pixel structure 
 * @param img a pointor to a MLV_Image structure
 * 		  Node a pointor to a pointor to a Node structure
 * 		  ref a pointor a Pixel structure
 * @return 0 if an error occurred else 1
 */
int attribute_error(MLV_Image* img, Node** node, Pixel* ref){
	int error_val;

	average_color(img, ref);
	error_val = error(img, ref); 
	if((*node = create_node(ref, error_val)) == NULL)
		return 0;
	return 1;
}

/**
 * Attribute error value to each area that divide the current zone of the image
 * those error values are stored to each son of the specified Node structure
 * @param img a pointor a MLV_Image structure
 * 		  node a pointor to a Node structure
 * 		  area1 a pointor to a Pixel structure
 * 		  area2 a pointor to a Pixel structure
 * 		  area3 a pointor to a Pixel structure
 * 		  area4 a pointor to a Pixel structure
 */
void attribute_errors(MLV_Image* img, Node* node, Pixel* area1, Pixel* area2, Pixel* area3, Pixel* area4){
	attribute_error(img, &(node->sonNW), area1);
	attribute_error(img, &(node->sonNE), area2);
	attribute_error(img, &(node->sonSE), area3);
	attribute_error(img, &(node->sonSW), area4);
}

/**
 * Add the sons of the specified Node structure
 * into a hashtable
 * @param ht the hashtable
 * 		  node a pointor to a Node structure
 */
void add_ht_sons(List* ht, Node* node){
	add_ht_node(ht, node->sonNW);
	add_ht_node(ht, node->sonNE);
	add_ht_node(ht, node->sonSE);
	add_ht_node(ht, node->sonSW);
}

/**
 * Draw the pixel in an MLV window
 * represented by each son of the specified Node structure
 * @param node a pointor to a Node structure
 */
void draw_sons(Node* node){
	draw_pixel(node->sonNW->pixel);
	draw_pixel(node->sonNE->pixel);
	draw_pixel(node->sonSE->pixel);
	draw_pixel(node->sonSW->pixel);
}

/**
 * Define the refresh frame rate of the conversion
 * @param count_div a pointor to an int value
 * 		  limit a pointor to an int value 
 */
void refresh_display(int* count_div, int* limit){
	if(*count_div == *limit){
		MLV_actualise_window();
		*limit <<= 1;
		MLV_wait_milliseconds(100);
	}
	(*count_div)++;
}

/**
 * Auxiliary function
 * Create the representation of an image into a Quadtree
 * @param img a pointor to a MLV_Image pointor
 * 		  ht the hashtable
 * Note : the Quadtree is created through the hashtable
 */
void input_create_qt_aux(MLV_Image* img, List* ht){
	Node* next_divide;
	int count_div, refresh;
	Pixel* area1;
	Pixel* area2;
	Pixel* area3;
	Pixel* area4;

	count_div = 0;
	refresh = 1;
	area1 = area2 = area3 = area4 = NULL;
	do {
		next_divide = max_error_node(ht);											/* Find the pixel with the highest error in the current Quadtree */
		init_areas(&area1, &area2, &area3, &area4, next_divide);					/* Initialize the 4 areas of the pixel with the highest error*/	
		attribute_errors(img, next_divide, area1, area2, area3, area4); 				/* Initalize the sons of the node with the highest error */	
		add_ht_sons(ht, next_divide); 												/* Add sons of this node to the HashTable*/
		remove_ht_node(ht, next_divide);											/* Remove this node from the HashTable */
		draw_sons(next_divide);
		refresh_display(&count_div, &refresh);
	} while(next_divide->error_val != 0);
}

/**
 * Create a Quadtree structure depending on the specified image
 * @param img a pointor to a MLV_Image structure
 * 		  qt a pointor to a Quadtree structure
 * @return 0 if an error occurred else 1
 */
int input_create_qt(MLV_Image* img, Quadtree* qt){
	List* ht;
	Pixel* first;

	assert(img != NULL);
	ht = create_ht();
	if(ht == NULL)
		return 0;
	first = create_pixel(0, 0, MAXPIXEL, NULL);
	if(first == NULL)
		return 0;

	attribute_error(img, qt, first);	/* Creation of the root of the tree */
	add_ht_node(ht, *qt);			/* Add the root in the HashTable */
	input_create_qt_aux(img, ht);	/* Creation of the tree */
	free_ht(ht);
	return 1;
}

/**
 * Convert an image into a Quadtree structure
 * @param img a pointor to MLV_Image structure
 * 	      qt a pointor to a Quadtree structure
 * @return 0 if an error occurred else 1
 */
int convert_img_qt(MLV_Image* img, Quadtree* qt){
	assert(img != NULL);
	assert(qt != NULL);

	MLV_clear_window(MLV_COLOR_BLACK);
	if(input_create_qt(img, qt) == 0)
		return 0;
	return 1;
}
