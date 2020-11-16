#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <MLV/MLV_all.h>
#include "../include/Extension.h"
#include "../include/Decompression.h"
#include "../include/BitFile.h"
#include "../include/Color.h"

int Black[4] = {0, 0, 0, 0};
int White[4] = {255, 255, 255, 255};

int count_bit_file(char* file_name){
	int bits;
	FILE* file;

	file = fopen(file_name, "r");
	bits = 0;
	fseek(file, 0, SEEK_SET);
	while(fgetc(file) != EOF)
		bits += 8;
	fclose(file);
	return bits;
}

int read_padding(BitFile* in){
	int padding, bit;
	int i;
	assert(in != NULL);

	padding = 0;
	for(i = 2; i >= 0; i--){
		bit = read_BitFile(in);
		if(bit == 1)
			padding += pow(2, i);
	}
	return padding;
}

int read_B_W(BitFile* in, Node* node){
	int bit = read_BitFile(in);

	if(bit == 1)
		node->pixel->color = create_color(Black);
	else if(bit == 0)
		node->pixel->color = create_color(White);
	else 
		return 0;
	return 1;
}

int read_body_B_W(BitFile* in, Quadtree* qt, int* total_bits){
	Node* node;
	int bit;
	assert(qt != NULL);	
	
	if(*total_bits == 0){
		close_BitFile(in);
		return 1;
	}
	(*total_bits)--;

	node = create_node(NULL, 0);
	bit = read_BitFile(in);
	if(bit == 0){
		*qt = node;
		if(read_body_B_W(in, &(*qt)->sonNW, total_bits) == 0)
			return 0;
		if(read_body_B_W(in, &(*qt)->sonNE, total_bits) == 0)
			return 0;
		if(read_body_B_W(in, &(*qt)->sonSE, total_bits) == 0)
			return 0;
		if(read_body_B_W(in, &(*qt)->sonSW, total_bits) == 0)
			return 0;
	} else if(bit == 1) {
		(*total_bits)--;
		if(read_B_W(in, node) == 0)
			return 0;
	} else {
		return 0;
	}
	return 1;
}

int read_unite(BitFile* in, int* unite){
	int i, bit;

	for(i = 7; i >= 0; i--){
		bit = read_BitFile(in); 
		if(bit == 1)
			*unite += pow(2, i);
		else if(bit == EOF)
			return 0;
	}
	return 1;
}

Color* read_color(BitFile* in){
	int i;
	int* rgba;
	Color* color; 

	rgba = (int*)calloc(4, sizeof(int));

	for(i = 0; i < 4; i++){
		if(read_unite(in, &(rgba[i])) == EOF)
			return NULL;
	}
	color = create_color(rgba);
	return color;
}

int read_body_color(BitFile* in, Quadtree* qt, int* total_bits){
	Pixel* pixel;
	int bit;
	assert(qt != NULL);	
	
	if(*total_bits == 0){
		close_BitFile(in);
		return 1;
	}
	
	pixel = create_pixel(0, 0, 1, NULL);
	(*total_bits)--;
	bit = read_BitFile(in);
	*qt = create_node(NULL, 0);

	if(bit == 0){
		if(read_body_color(in, &(*qt)->sonNW, total_bits) == 0)
			return 0;
		if(read_body_color(in, &(*qt)->sonNE, total_bits) == 0)
			return 0;
		if(read_body_color(in, &(*qt)->sonSE, total_bits) == 0)
			return 0;
		if(read_body_color(in, &(*qt)->sonSW, total_bits) == 0)
			return 0;
	} else {
		(*total_bits) -= 32;
		pixel->color = read_color(in);
		if(NULL == pixel->color)
			return 0;
		(*qt)->pixel = pixel;
	}
	return 1;
}

int decompression(char* file_name, Quadtree* qt){
	BitFile in;
	int return_val_ext, total_bits, padding;

	assert(qt != NULL);
	assert(file_name != NULL);
	
	return_val_ext = extension_qt(file_name);
	init_BitFile(&in, file_name, "r");
	padding = read_padding(&in);
	total_bits = count_bit_file(file_name) - 3 - padding;
	if(return_val_ext == -1)
		return -1;
	if(return_val_ext == 1){
		if(read_body_color(&in, qt, &total_bits) == 0)
			return 0;
	} else {
		if(read_body_B_W(&in, qt, &total_bits) == 0)
			return 0;
	}
	printf("OK\n");
	close_BitFile(&in);
	return 1;
}
