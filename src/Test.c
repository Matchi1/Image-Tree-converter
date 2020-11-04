#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "../include/Test.h"
#include "../include/Quadtree.h"
#include "../include/BitFile.h"
#include "../include/Color.h"
#include "../include/Graphic.h"

Byte* generate_rgba(){
	Byte* rgba;
	rgba = (Byte*)malloc(sizeof(Byte) * 4);
	if(rgba == NULL)
		return NULL;
	
	rgba[0] = rand() % 256;
	rgba[1] = rand() % 256;
	rgba[2] = rand() % 256;
	rgba[3] = rand() % 256;
	return rgba;
}

Color* generate_color(int len_color){
	Color* arr_color;
	int i;

	arr_color = (Color*)malloc(sizeof(Color) * len_color);
	if(arr_color == NULL)
		return NULL;
	
	for(i = 0; i < len_color; i++){
		init_color(&arr_color[i], generate_rgba());
	}
	return arr_color;
}

Node* generate_node(int len_color, Color* arr_color){
	Node* arr_node;
   	int i;

	arr_node = (Node*)malloc(sizeof(Node) * len_color);
	if(arr_node == NULL)
		return NULL;

	for(i = 0; i < len_color; i++){
		init_node(&arr_node[i], 0, &arr_color[i]);
	}
	return arr_node;
}

void generate_File(BitFile* out, int len_arr, int* arr_bit){
	int i;

	for(i = 0; i< len_arr; i++){
		write_BitFile(out, arr_bit[i]);
	}
	close_BitFile(out);
}

int test_read_BitFile(BitFile* in, int len_arr, int* arr_bit){
	int i;

	for(i = 0; i < len_arr; i++){
		if(read_BitFile(in) != arr_bit[i])
			return 0;
	}
	close_BitFile(in);
	return 1;
}

int* random_arr_bit(unsigned int len_arr){
	int* arr_bit;
	int i;

	arr_bit = (int*)malloc(sizeof(int) * len_arr);
	if(arr_bit == NULL)
		return NULL;

	for(i = 0; i < len_arr; i++){
		arr_bit[i] = rand() % 2;
	}
	return arr_bit;
}

int test_add_sons(){
	Color* arr_color;
	Node* arr_node;
	int i;
	
	printf("  TEST ADD SONS\n");
	srand(time(NULL));	

	for(i = 0; i < 10; i++){
		arr_color = generate_color(4);
		arr_node = generate_node(4, arr_color);
		if(verify_color(arr_node[0].rgba, &arr_color[0]) == 0 
			|| verify_color(arr_node[1].rgba, &arr_color[1]) == 0 
			|| verify_color(arr_node[2].rgba, &arr_color[2]) == 0 
			|| verify_color(arr_node[3].rgba, &arr_color[3]) == 0){
			printf("  Erreur\n");
			return 0;
		}
		free(arr_color);
		free(arr_node);
	}
	printf("OK\n");
	return 1;
}

int test_read_write_BitFile(){
	int* arr_bit;
	char* file_name;
	BitFile in;
	BitFile out;

	srand(time(NULL));
	file_name = "../test_file";
	arr_bit = random_arr_bit(10);
	init_BitFile(&out, file_name, "w");

	if(arr_bit == NULL){
		printf("Pas assez d'espace mémoire\n");
		return 0;
	}
	
	generate_File(&out, 10, arr_bit);
	init_BitFile(&in, file_name, "r");

	if(test_read_BitFile(&in, 10, arr_bit) == 0)
		return 0;

	printf("OK\n");
	return 1;
}

int test_Quadtree(){
	printf("TEST QUADTREE\n");
	if(test_add_sons() == 0)
		return 0;
	return 1;
}

int test_BitFile(){
	printf("  TEST BITFILE\n");
	if(test_read_write_BitFile() == 0)
		return 0;
	return 1;
}

int test(){
	if(test_Quadtree() == 0)
		return 0;
	if(test_BitFile() == 0)
		return 0;
	return 1;
}