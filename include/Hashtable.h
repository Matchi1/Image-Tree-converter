#ifndef __HASHTABLE__
#define __HASHTABLE__

#include "Quadtree.h"

#define HT_MAX_LEN 500

typedef struct element {
	Node* node;
	struct element* next;
} Element, *List;

/**
 * Create a key for a node.
 * @parameters node a pointor to the node.
 * @return the key of the node.
 */
int get_key(Node* node);

/**
 * Add a Node to a List.
 * @parameters lst a pointor to a List.
 * 			   node a pointor of the node to add.
 * @return 1 if the node has been added in the List
 * else 0.
 */
int add_list_node(List* lst, Node* node);

/**
 * Remove a node from the a List
 * @parameters lst a pointor to a List.
 * 			   node a pointor to a node.
 * @return 1 if the node has been removed from the list
 * else 0.
 */
int remove_list_node(List* lst, Node* node);

#endif
