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

void add_ht_node(List* ht, Node* node){
	int key = get_key(node) % HT_MAX_LEN;
	add_list_node(&(ht[key]), node);
}

void add_lst_element(List* lst, Element* new){
	Element* browse;
	int error_val, next_error_val;

	assert(lst != NULL);
	assert(new != NULL);
	error_val = new->node->error_val;

	if(NULL == *lst){
		*lst = new;
	} else if(error_val > (*lst)->node->error_val){
		new->next = *lst;
		*lst = new;
	} else {
		browse = *lst;
		while(browse->next != NULL){
			next_error_val = browse->next->node->error_val;
			if(error_val > next_error_val){
				new->next = browse->next;
				browse->next = new;
				return;
			}
			browse = browse->next;
		}
		browse->next = new;
	}
}

int add_list_node(List* lst, Node* node){
	Element* new;

	new = create_element(node);
	if(NULL == new)
		return 0;
	add_lst_element(lst, new);
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
		*lst = tmp->next;
		free(tmp);
		return 1;
	}
	browse = *lst;
	while(browse->next != NULL){
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

int remove_ht_node(List* ht, Node* node){
	int key = get_key(node) % HT_MAX_LEN;
	if(remove_list_node(&(ht[key]), node) == 0)
		return 0;
	return 1;
}

void free_list(List* lst){
	if(NULL == *lst)
		return;
	else {
		free_list(&(*lst)->next);
		free(*lst);
		*lst = NULL;
	}
}

void free_ht(List* ht){
	int i;

	for(i = 0; i < HT_MAX_LEN; i++){
		free_list(&(ht[i]));
	}
	free(ht);
}
