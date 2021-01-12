#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../include/Extension.h"
#include "../include/Compression.h"
#include "../include/BitFile.h"

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

int count_padding(Quadtree qt, int display_color){
	int padding, nb_bits;

	count_bit(qt, &nb_bits, display_color);
	padding = (nb_bits + 3) % 8;
	return padding;
}

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

void write_B_W(BitFile* out, int* color){
	write_BitFile(out, black_or_white(color));
}

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

void write_rgba(BitFile* out, int* color){
	int i;
	for(i = 0; i < 4; i++){
		write_unite(out, color[i]);
	}
}

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



