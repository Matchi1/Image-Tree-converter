#ifndef __QUADTREE__
#define __QUADTREE__

#include "Color.h"
#include "Pixel.h"

typedef struct node{
	Pixel* pixel;
	int error_val;
	struct node *sonNW;
	struct node *sonNE;
	struct node *sonSW;
	struct node *sonSE;
}Node, *Quadtree;

/**
 * Create a node with the element in argument.
 * @parameters: color a pointor to a Color.
 * 			    p a pointor to a Pixel.
 * @return: a pointor to a node.
 */
Node* create_node(Pixel* p, int error_val);

/**
 * Initialize a node with the label and a color.
 * @parameters: node a pointor to a Node.
 * 			    color a pointor to a Color.
 * 			    p a pointor to a Pixel.
 * @return: void.
 */
void init_node(Node* node, Pixel* p, int error_val);

/**
 * Add sons to a quadtree.
 * @parameters: qt a Quadtree
 * 			    nb_sons the numbers of sons in the array of son.
 * 			    arr_sons an array of sons
 * @return: 1 if executed correctly else 0.
 */
int add_sons(Quadtree qt, int nb_sons, Node* arr_sons); 

void display_node(Node* node);

/**
 * Display a Quadtree.
 * @parameters: qt a Quadtree.
 * @return: void
 */
void display_qt(Quadtree qt);

/**
 * Verify if node is a leave.
 * @parameters: node a pointor to a Node.
 * @return: 1 if it is a leave else 0.
 */
int is_leave(Node* node);

/**
 * Verify if the Quadtree is empty.
 * @parameters: qt a Quadtree.
 * @return 1 if the Quadtree is empty else 0.
 */
int is_empty(Quadtree qt);

#endif
