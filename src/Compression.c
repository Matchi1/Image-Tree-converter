#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../include/Extension.h"
#include "../include/Compression.h"
#include "../include/BitFile.h"

int is_white(Color* color){
	if(color->r == 255 && color->g == 255 && color->b == 255 && color->a == 255)
		return 1;
	return 0;
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
	int mask, bit;
	int i;

	if(padding > 7){
		printf("Erreur: padding trop grand.\n");
		return 0;
	}
	for(i = 2; i >= 0; i--){
		bit = 0;
		mask = 1 << i;
		if((padding & mask) != 0)
			bit = 1;
		write_BitFile(out, bit);
	}
	return 1;
}

void write_B_W(BitFile* out, Node* node){
	if(!is_white(node->pixel->color))
		write_BitFile(out, 0);
	else 
		write_BitFile(out, 1);
}

void write_unite(BitFile* out, int unite){
	int i;
	int bit;
	int mask;

	for(i = 7; i >= 0; i--){
		bit = 0;
		mask = 1 << i;
		if((unite & mask) != 0)
			bit = 1;
		write_BitFile(out, bit);
	}
}

void write_color(BitFile* out, Color* color){
	write_unite(out, color->r);
	write_unite(out, color->g);
	write_unite(out, color->b);
	write_unite(out, color->a);
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
		write_color(out, qt->pixel->color);
	} else {
		write_BitFile(out, 0);
		prefix_color(out, qt->sonNW);
		prefix_color(out, qt->sonNE);
		prefix_color(out, qt->sonSE);
		prefix_color(out, qt->sonSW);
	}
}

int compression(char* file_name, Quadtree qt){
	BitFile out;
	int return_val_ext;
	int nb_bits;
	int padding;

	assert(file_name != NULL);
	if(is_empty(qt))
		return 0;
	
	nb_bits = 0;
	return_val_ext = extension_qt(file_name);
	count_bit(qt, &nb_bits, return_val_ext);
	padding = (nb_bits + 3) % 8; 
	init_BitFile(&out, file_name, "w");
	
	if(return_val_ext == -1){
		printf("Fichier non reconnue.\n");
		return 0;
	} else if(return_val_ext == 0){
		write_padding(&out, padding);
		prefix_B_W(&out, qt);
	} else {
		write_padding(&out, padding);
		prefix_color(&out, qt);
	}
	printf("OK\n");
	close_BitFile(&out);
	return 1;
}



