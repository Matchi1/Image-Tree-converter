#ifndef __QUADTREE__
#define __QUADTREE__

#include "Color.h"

typedef struct node{
	int label;
	Color *rgba;
	struct node *sonNW;
	struct node *sonNE;
	struct node *sonSW;
	struct node *sonSE;
}Node, *Quadtree;

/**
 * Create a node with the element in argument.
 * @return a pointor to a node.
 */
Node* create_node(int label, Color* color);

/**
 * Initialize a node with the label and a color.
 * @return void.
 */
void init_node(Node* node, int label, Color* color);

/**
 * Add sons to a quadtree.
 * @return 1 if executed correctly else 0.
 */
int add_sons(Quadtree qt, int nb_sons, Node* sons); 

/**
 * Display a Quadtree.
 * @return void
 */
void display_qt(Quadtree qt);

/**
 * Verify if node is a leave.
 * @return 1 if it is a leave else 0.
 */
int is_leave(Node* node);

#endif
