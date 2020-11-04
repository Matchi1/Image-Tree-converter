#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../include/Compression.h"
#include "../include/BitFile.h"

int extension(char* file_name){
	char* extension_c;
	char* extension_B_W;
	int i, len_file_name;	

	extension_c = ".qtc";
	extension_B_W = ".qtn";
	len_file_name = strlen(file_name);
	
	for(i = 0; i < len_file_name; i++){
		if(file_name[i] == '.'){
			if(strcmp(&(file_name[i]), extension_c) == 0)
				return 1;
			if(strcmp(&(file_name[i]), extension_B_W) == 0)
				return 0;
		}
	}
	return -1;
}

void count_bit(Quadtree qt, int* len_bits, int display_color){
	assert(len_bits != NULL);

	(*len_bits)++;

	if(is_leave(qt)){
		if(display_color == 0)
			(*len_bits)++;
		else 
			(*len_bits) += 32;
	} else { 
		count_bit(qt->sonNW, len_bits, display_color);
		count_bit(qt->sonNE, len_bits, display_color);
		count_bit(qt->sonSE, len_bits, display_color);
		count_bit(qt->sonSW, len_bits, display_color);
	}
}

int write_padding(BitFile* out, int padding){
	int mask;
	int i;

	if(padding > 7){
		printf("Erreur: padding trop grand.\n");
		return 0;
	}
	fseek(out->file, 0, SEEK_SET);
	for(i = 2; i >= 0; i++){
		mask = 1 << i;
		write_BitFile(out, 1 & mask);
	}
	return 1;
}

void write_B_W(BitFile* out, Node* node){
	if(node->rgba->r == 255 && node->rgba->g == 255
		&& node->rgba->b == 255 && node->rgba->a == 255)
		write_BitFile(out, 0);
	else 
		write_BitFile(out, 1);
}

void write_unite(BitFile* out, Byte rgba){
	int i;
	int bit;
	int mask;

	for(i = 7; i >= 0; i++){
		mask = 1 << i;
		bit = rgba & mask;	
		write_BitFile(out, bit);
	}
}

void write_color(BitFile* out, Node* node){
	write_unite(out, node->rgba->r);
	write_unite(out, node->rgba->g);
	write_unite(out, node->rgba->b);
	write_unite(out, node->rgba->a);
}

void prefix_B_W(BitFile* out, Quadtree qt){
	if(is_leave(qt) == 1){
		write_BitFile(out, 1);
		write_B_W(out, qt);
	} else {
		write_BitFile(out, 0);
		prefix_B_W(out, qt->sonNW);
		prefix_B_W(out, qt->sonNE);
		prefix_B_W(out, qt->sonSE);
		prefix_B_W(out, qt->sonSW);
	}
}

void prefix_color(BitFile* out, Quadtree qt){
	if(is_leave(qt) == 1){
		write_BitFile(out, 1);
		write_color(out, qt);
	} else {
		write_BitFile(out, 0);
		prefix_B_W(out, qt->sonNW);
		prefix_B_W(out, qt->sonNE);
		prefix_B_W(out, qt->sonSE);
		prefix_B_W(out, qt->sonSW);
	}
}

int compression(char* file_name, Quadtree qt, int display_type){
	BitFile out;
	int return_val_ext;

	assert(file_name != NULL);
	if(is_empty(qt))
		return 0;
	
	return_val_ext = extension(file_name);
	init_BitFile(&out, file_name, "w");

	if(return_val_ext == -1){
		printf("Fichier non reconnue.\n");
		return 0;
	} else if(return_val_ext == 0){
		prefix_B_W(&out, qt);
	} else {
		prefix_color(&out, qt);
	}
	close_BitFile(&out);
	return 1;
}



