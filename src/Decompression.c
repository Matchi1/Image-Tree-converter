#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <MLV/MLV_all.h>
#include "../include/Extension.h"
#include "../include/Decompression.h"
#include "../include/BitFile.h"
#include "../include/Color.h"

int count_bit_file(char* file_name){
	int bits;
	FILE* file;

	file = fopen(file_name, "r");
	bits = 0;
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

int* read_B_W(BitFile* in){
	int bit = read_BitFile(in);

	if(bit == 1)
		return create_color(0, 0, 0, 255);
	else 
		return create_color(255, 255, 255, 255);
}

int read_unite(BitFile* in, int* unite){
	int i, bit;

	for(i = 7; i >= 0; i--){
		bit = read_BitFile(in); 
		if(bit == 1)
			*unite += pow(2, i);
		else if(bit == EOF)
			return EOF;
	}
	return 1;
}

int* read_rgba(BitFile* in){
	int i;
	int* rgba;

	rgba = create_color(0, 0, 0, 255);

	for(i = 0; i < 4; i++){
		if(read_unite(in, &(rgba[i])) == EOF)
			return NULL;
	}
	return rgba;
}

int read_body(BitFile* in, Quadtree* qt, int* total_bits, int* (*read_color)(BitFile* in)){
	Pixel* pixel;
	int bit;
	assert(qt != NULL);	
	
	if(*total_bits == 0)
		return 1;
	pixel = create_pixel(0, 0, 1, NULL);
	*qt = create_node(NULL, 0);
	(*total_bits)--;
	bit = read_BitFile(in);

	if(bit == 0){
		if(read_body(in, &(*qt)->sonNW, total_bits, read_color) == 0)
			return 0;
		if(read_body(in, &(*qt)->sonNE, total_bits, read_color) == 0)
			return 0;
		if(read_body(in, &(*qt)->sonSE, total_bits, read_color) == 0)
			return 0;
		if(read_body(in, &(*qt)->sonSW, total_bits, read_color) == 0)
			return 0;
	} else {
		if(read_color == read_B_W)
			(*total_bits)--;
		else
			(*total_bits) -= 32;
		pixel->color = read_color(in);
		if(NULL == pixel->color){
			printf("Not enough memory space\n");
			return 0;
		}
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
	if(return_val_ext == 0){
		if(read_body(&in, qt, &total_bits, read_rgba) == 0)
			return 0;
	} else {
		if(read_body(&in, qt, &total_bits, read_B_W) == 0)
			return 0;
	}
	close_BitFile(&in);
	return 1;
}
