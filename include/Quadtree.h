#ifndef __QUADTREE__
#define __QUADTREE__

#include "Color.h"
#include "Pixel.h"

typedef struct node{
	Pixel* pixel;
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
Node* create_node(Color* color, Pixel* p);

/**
 * Initialize a node with the label and a color.
 * @return void.
 */
void init_node(Node* node, Color* color, Pixel* p);

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

/**
 * Verify if the Quadtree is empty.
 * @argument qt a Quadtree.
 * @return 1 if the Quadtree is empty else 0.
 */
int is_empty(Quadtree qt);

#endif
