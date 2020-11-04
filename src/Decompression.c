
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "../include/Decompression.h"
#include "../include/BitFile.h"

int read_padding(BitFile* in){
	int padding, bit;
	int i;
	assert(in != NULL);
	fseek(in->file, 0, SEEK_SET);

	padding = 0;
	for(i = 2; i >= 0; i++){
		bit = read_BitFile(in);
		if(bit == 1)
			padding += pow(2, i);
	}
	return padding;
}

void read_body(BitFile* in, Quadtree* qt){
	if(read_BitFile(in) == 0){
	}
}

void translate(BitFile* in, Quadtree* qt){
}

int decompression(char* file_name, Quadtree* qt){
	BitFile in;

	assert(qt != NULL);
	assert(file_name != NULL);

	init_BitFile(&in, file_name, "r");
	translate(&in, qt);
	
	return 1;
}
