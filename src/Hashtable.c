#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/Hashtable.h"

void init_ht(List* ht){
	int i;
	for(i = 0; i < HT_MAX_LEN; i++){
		ht[i] = NULL;
	}
}

List* create_ht(){
	List* ht;

	ht = (List*)malloc(sizeof(List) * HT_MAX_LEN);
	if(NULL == ht)
		return NULL;
	init_ht(ht);
	return ht;
}

void init_element(Element* elt, Node* node){
	assert(elt != NULL);
	elt->node = node;
	elt->next = NULL;
}

Element* create_element(Node* node){
	Element* elt;

	elt = (Element*)malloc(sizeof(Element));
	if(NULL == elt)
		return NULL;
	init_element(elt, node);
	return elt;
}

int get_key(Node* node){
	int x, y;
	x = node->pixel->x;
	y = node->pixel->y;
	return x ^ y;
}

int add_list_node(List* lst, Node* node){
	Element* new;

	new = create_element(node);
	if(NULL == new)
		return 0;
	new->next = (*lst);
	*lst = new;
	return 1;
}

int remove_list_node(List* lst, Node* node){
	Element* browse;
	Element* tmp;
	assert(lst != NULL);
	assert(node != NULL);
	
	if(NULL == *lst)
		return 0;
	if((*lst)->node == node){
		tmp = *lst;
		(*lst)->next = tmp->next;
		free(tmp);
		return 1;
	}
	browse = *lst;
	while(NULL != browse->next){
		if(node == browse->next->node){
			tmp = browse->next;
			browse->next = tmp->next;
			free(tmp);
			return 1;
		}
		browse = browse->next;
	}
	return 0;
}
