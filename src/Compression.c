#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../include/Extension.h"
#include "../include/Compression.h"
#include "../include/BitFile.h"

/**
 * Count the number of bit a Quadtree will generate during
 * compression.
 * @argument qt a Quadtree
 *           len_bits a pointor containing the number of bits
 *           display_bw number representing the format of compression
 *           (compression for colored image or black & white image)
 * @return void
 */
void count_bit(Quadtree qt, int* nb_bits, int display_color){
	assert(nb_bits != NULL);

	(*nb_bits)++;

	if(is_leave(qt)){
		if(display_color == 0)
			(*nb_bits)++;
		else 
			(*nb_bits) += 32;
	} else { 
		count_bit(qt->sonNW, nb_bits, display_color);
		count_bit(qt->sonNE, nb_bits, display_color);
		count_bit(qt->sonSE, nb_bits, display_color);
		count_bit(qt->sonSW, nb_bits, display_color);
	}
}

/**
 * Count the padding depending on the Quadtree structure
 * and the encription of the Quadtree.
 * @param qt a Quadtree structure
 * 		  display_bw a boolean value 
 * @return the padding 
 */
int count_padding(Quadtree qt, int display_bw){
	int padding, nb_bits;

	count_bit(qt, &nb_bits, display_bw);
	padding = (nb_bits + 3) % 8;
	return padding;
}

/**
 * Write the specified padding into a file contained in BitFile
 * @parameters out a pointor to a BitFile Structure
 * 			   padding the specified padding
 * @return 0 if the padding is too big else 1
 */
int write_padding(BitFile* out, int padding){
	int mask, i;

	if(padding > 7){
		printf("Erreur: padding trop grand.\n");
		return 0;
	}
	for(i = 2; i >= 0; i--){
		mask = 1 << i;
		if((padding & mask) != 0)
			write_BitFile(out, 1);
		else
			write_BitFile(out, 0);
	}
	return 1;
}

/**
 * Write the bit representing the black or white color
 * depending on the specified color in the Node structure
 * @parameters out a pointor to a BitFile structure
 * 			   color an array representing rgba color
 */
void write_B_W(BitFile* out, int* color){
	write_BitFile(out, black_or_white(color));
}

/**
 * Write the bits representing the specified unite color
 * into a file contained in the BitFile structure
 * @parameters out a pointor to a BitFile structure
 * 			   unite the specified unite color
 */
void write_unite(BitFile* out, int unite){
	int i, mask;

	for(i = 7; i >= 0; i--){
		mask = 1 << i;
		if((unite & mask) != 0)
			write_BitFile(out, 1);
		else
			write_BitFile(out, 0);
	}
}

/**
 * Write the bits representing the specified color
 * into a file contained in the BitFile structure
 * @parameters out a pointor to a BitFile structure
 * 			   color an array representing rgba color
 */
void write_rgba(BitFile* out, int* color){
	int i;
	for(i = 0; i < 4; i++){
		write_unite(out, color[i]);
	}
}

/**
 * Write the bits representing a tree depending on the prefix browse
 * into a file contained in the bitFile structure
 * It writes the black & white version of this tree
 * @parameters out a pointor to a BitFile structure
 * 			   qt a Quadtree structure
 * 			   bw value representing how to convert the image's color (rgba or black and white)
 */
void prefix(BitFile* out, Quadtree qt, void (*write_color)(BitFile* out, int* color)){
	if(is_leave(qt) == 1){
		write_BitFile(out, 1);
		write_color(out, qt->pixel->color);
	} else {
		write_BitFile(out, 0);
		prefix(out, qt->sonNW, write_color);
		prefix(out, qt->sonNE, write_color);
		prefix(out, qt->sonSE, write_color);
		prefix(out, qt->sonSW, write_color);
	}
}

int compression(char* file_name, Quadtree qt){
	BitFile out;
	int return_val_ext, padding;

	assert(file_name != NULL);
	if(is_empty(qt))
		return 0;
	
	return_val_ext = extension_qt(file_name);
	padding = count_padding(qt, return_val_ext);
	init_BitFile(&out, file_name, "w");
	if(return_val_ext == -1){
		fprintf(stderr, "Fichier non reconnue.\n");
		return 0;
	}
	write_padding(&out, padding);
	if(return_val_ext == 1)
		prefix(&out, qt, write_B_W);
	else 
		prefix(&out, qt, write_rgba);
	printf("OK\n");
	close_BitFile(&out);
	return 1;
}



