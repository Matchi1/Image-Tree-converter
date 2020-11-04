#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/Quadtree.h"

Node* create_node(int label, Color* color){
	Node* node;

	assert(color != NULL);
	node = (Node*)malloc(sizeof(Node));

	if(node == NULL)
		return NULL;

	init_node(node, label, color);
	return node;	
}

void init_node(Node* node, int label, Color* color){
	assert(node != NULL);

	node->label = label;
	node->rgba = color;	
	node->sonNW = NULL;
	node->sonNE = NULL;
	node->sonSE = NULL;
	node->sonSW = NULL;
}

int add_sons(Quadtree qt, int nb_sons, Node* sons){
	assert(qt != NULL);

	if(nb_sons == 0)
		return 0;	

	qt->sonNW = &sons[0];
	qt->sonNE = &sons[1];
	qt->sonSE = &sons[2];
	qt->sonSW = &sons[3];

	return 1;
}

int is_leave(Node* node){
	if(node->sonNW == NULL || node->sonNE == NULL || node->sonSW == NULL || node->sonSE == NULL)
		return 0;
	return 1;
}

void display_node(Node* node){
	assert(node != NULL);

	printf("label : %d\n", node->label);	
	display_color(node->rgba);	
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
