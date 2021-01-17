#ifndef __HASHTABLE__
#define __HASHTABLE__

#include "Quadtree.h"

#define HT_MAX_LEN 1048

/**
 * This structure represent a list of element
 * More precisely, it contains pointor to a Node structure.
 * This structure is only used for the hashtable purposes
 * Note : Hashtable is used to increase the performance
 * of the program during the computation of the tree representing
 * an image.
 */
typedef struct element {
	Node* node;
	struct element* next;
} Element, *List;

/**
 * Initialize the Hashtable with NULL value
 * @param ht the hashtable
 */
void init_ht(List* ht);

/**
 * Create a hashtable
 * @return a hashtable
 */
List* create_ht();

/**
 * Create a key for a node.
 * @parameters node a pointor to the node.
 * @return the key of the node.
 */
int get_key(Node* node);

/**
 * Add an new element into a list
 * @param lst a pointor to a List structure
 * 		  new a pointor to an Element structure
 */
void add_lst_element(List* lst, Element* new);

/**
 * Add a Node to a List.
 * @parameters lst a pointor to a List.
 * 			   node a pointor of the node to add.
 * @return 1 if the node has been added in the List
 * else 0.
 */
int add_list_node(List* lst, Node* node);

/**
 * Add a node into a hashtable
 * @param ht the hashtable
 * 		  node a pointor to a Node structure
 */
void add_ht_node(List* ht, Node* node);

/**
 * Remove a node from the a List
 * @parameters lst a pointor to a List.
 * 			   node a pointor to a node.
 * @return 1 if the node has been removed from the list
 * else 0.
 */
int remove_list_node(List* lst, Node* node);

/**
 * Remove a node from a hashtable
 * @param ht the hashtable
 * 		  node a pointor to a Node structure
 * @return 1 if the node has been removed else 0
 */

int remove_ht_node(List* ht, Node* node);
/**
 * Free the hashtable
 * @param ht the hashtable
 */
void free_ht(List* ht);

#endif
