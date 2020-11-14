#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>
#include <MLV/MLV_all.h>
#include "../include/Test.h"
#include "../include/Quadtree.h"
#include "../include/BitFile.h"
#include "../include/Color.h"
#include "../include/Graphic.h"
#include "../include/Compression.h"
#include "../include/Decompression.h"
#include "../include/Display_qt.h"

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

Node* generate_node(int nb_node, Pixel* pixel){
	Node* arr_node;
   	int i;

	arr_node = (Node*)malloc(sizeof(Node) * nb_node);
	if(arr_node == NULL)
		return NULL;

	for(i = 0; i < nb_node; i++){
		init_node(&arr_node[i], pixel, 0);
	}
	return arr_node;
}

Pixel* generate_pixel(int nb_pixel){
	int x, y, length, i;
	Pixel* arr_pixel;
	Color* color;
	
	arr_pixel = (Pixel*)malloc(sizeof(Pixel) * nb_pixel);
	if(arr_pixel == NULL)
		return NULL;

	for(i = 0; i < nb_pixel; i++){
		x = rand() % MAXPIXEL;
		y = rand() % MAXPIXEL;
		length = rand() % MAXPIXEL;
		color = generate_color(1);
		init_pixel(&(arr_pixel[i]), x, y, length, color);
	}
	return arr_pixel;
}

void generate_qt(Quadtree *qt){

	*qt = create_node(generate_pixel(1), 0);
	(*qt)->sonNW = create_node(generate_pixel(1), 0);
	(*qt)->sonNE = create_node(generate_pixel(1), 0);
	(*qt)->sonSE = create_node(generate_pixel(1), 0);
	(*qt)->sonSW = create_node(generate_pixel(1), 0);
	(*qt)->sonNW->sonNW = create_node(generate_pixel(1), 0);
	(*qt)->sonNW->sonNE = create_node(generate_pixel(1), 0);
	(*qt)->sonNW->sonSE = create_node(generate_pixel(1), 0);
	(*qt)->sonNW->sonSW = create_node(generate_pixel(1), 0);
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

int comp_decomp(){
	Quadtree qt;
	Quadtree qt_decomp;
	char file_name[] = "test/test.qtc";
	
	srand(time(NULL));
	generate_qt(&qt);
	qt_decomp = NULL;

	if(qt == NULL)
		return 0;
	
	printf("\tCompression... ");
	compression(file_name, qt);
	display_qt_pdf(qt);
	MLV_wait_milliseconds(100);
	
	printf("\tDecompression... ");
	decompression(file_name, &qt_decomp);	
	display_qt_pdf(qt_decomp);

	return 1;
}

int test_Quadtree(){
	printf("TEST QUADTREE\n");
	return 1;
}

int test_BitFile(){
	printf("  TEST BITFILE\n");
	if(test_read_write_BitFile() == 0)
		return 0;
	return 1;
}

int test_Comp_Decomp(){
	printf("  TEST COMPRESSION ET DECOMPRESSION\n");
	if(comp_decomp() == 0)
		return 0;
	return 1;
}

int test(){
	if(test_Quadtree() == 0)
		return 0;
	if(test_BitFile() == 0)
		return 0;
	if(test_Comp_Decomp() == 0)
		return 0;
	return 1;
}
