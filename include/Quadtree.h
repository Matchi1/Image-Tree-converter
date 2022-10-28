#ifndef __QUADTREE__
#define __QUADTREE__

#include "Color.h"
#include "Pixel.h"

/**
 * This structure is used to represent an image
 * through a tree structure
 * @field pixel contains information about how to represent the pixel
 * 				in the window
 * 		  error_val error value that represent the distance between the current pixel
 * 		  			and the real pixel
 * 		  sonNW a Node structure representing the North West corner of the current node
 * 		  sonNE a Node structure representing the North East corner of the current node
 * 		  sonSE a Node structure representing the South East corner of the current node
 * 		  sonSW a Node structure representing the South West corner of the current node
 */
typedef struct node{
	Pixel* pixel;
	int error_val;
	struct node *sonNW;
	struct node *sonNE;
	struct node *sonSW;
	struct node *sonSE;
}Node, *Quadtree;

/**
 * @brief Create a node with the element in argument.
 * @param color a pointor to a Color.
 * @param p a pointor to a Pixel.
 * @ret a pointor to a node.
 */
Node* create_node(Pixel* p, int error_val);

/**
 * @brief Initialize a node with the label and a color.
 * @param node a pointor to a Node.
 * @param color a pointor to a Color.
 * @param p a pointor to a Pixel.
 */
void init_node(Node* node, Pixel* p, int error_val);

/**
 * @brief Add sons to a quadtree.
 * @param qt a Quadtree
 * @param nb_sons the numbers of sons in the array of son.
 * @param arr_sons an array of sons
 * @ret 1 if executed correctly else 0.
 */
int add_sons(Quadtree qt, int nb_sons, Node* arr_sons); 

/**
 * @brief Verify if node is a leave.
 * @param node a pointor to a Node.
 * @ret 1 if it is a leave else 0.
 */
int is_leave(Node* node);

/**
 * @brief Verify if the Quadtree is empty.
 * @param qt a Quadtree.
 * @ret 1 if the Quadtree is empty else 0.
 */
int is_empty(Quadtree qt);

/**
 * @brief Display a Node
 * @param node a pointor to a Node structure
 */
void display_node(Node* node);

/**
 * @brief Display a Quadtree.
 * @param qt a Quadtree.
 */
void display_qt(Quadtree qt);

/**
 * @brief Free a Quadtree structure
 * @param qt a pointor to a Quadtree structure
 */
void free_quadtree(Quadtree* qt);

#endif
