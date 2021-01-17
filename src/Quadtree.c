#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/Quadtree.h"

Node* create_node(Pixel* p, int error_val){
	Node* node;

	node = (Node*)malloc(sizeof(Node));

	if(node == NULL)
		return NULL;

	init_node(node, p, error_val);
	return node;	
}

void init_node(Node* node, Pixel* p, int error_val){
	assert(node != NULL);

	node->pixel = p;
	node->error_val = error_val;
	node->sonNW = NULL;
	node->sonNE = NULL;
	node->sonSE = NULL;
	node->sonSW = NULL;
}

int add_sons(Quadtree qt, int nb_sons, Node* arr_sons){
	assert(qt != NULL);

	if(nb_sons == 0)
		return 0;	

	qt->sonNW = &arr_sons[0];
	qt->sonNE = &arr_sons[1];
	qt->sonSE = &arr_sons[2];
	qt->sonSW = &arr_sons[3];

	return 1;
}

int is_leave(Node* node){
	if(node->sonNW == NULL && node->sonNE == NULL && node->sonSW == NULL && node->sonSE == NULL)
		return 1;
	return 0;
}

int is_empty(Quadtree qt){
	if(qt == NULL){
		printf("Arbre Vide\n");
		return 1;
	}
	return 0;
}

void display_node(Node* node){
	assert(node != NULL);
	printf("error value: %d\n", node->error_val);
	if(node->pixel != NULL)
		display_pixel(node->pixel);
}

void display_qt(Quadtree qt){
	if(qt == NULL)
		printf("Arbre Vide\n");
	if(is_leave(qt) == 1)
		display_node(qt);

	display_qt(qt->sonNW);
	display_qt(qt->sonNE);
	display_qt(qt->sonSW);
	display_qt(qt->sonSE);
}

void free_quadtree(Quadtree* qt){
	if(*qt != NULL){
		free_quadtree(&((*qt)->sonNW));
		free_quadtree(&((*qt)->sonNE));
		free_quadtree(&((*qt)->sonSE));
		free_quadtree(&((*qt)->sonSW));
		if((*qt)->pixel != NULL)
			free_pixel((*qt)->pixel);
		free(*qt);
		*qt = NULL;
	}
}	
