
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "../include/Decompression.h"
#include "../include/BitFile.h"
#include "../include/Color.h"

Byte Black[4] = {0, 0, 0, 0};
Byte White[4] = {255, 255, 255, 255};

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

void read_B_W(BitFile* in, Node* node){
	if(read_BitFile(in) == 1)
		node->rgba = create_color(Black);
	else
		node->rgba = create_color(White);
}

void read_body_B_W(BitFile* in, Quadtree* qt){
	Node* node;
	assert(qt != NULL);	
	
	node = create_node(NULL, NULL);
	if(read_BitFile(in) == 0){
		*qt = node;
		read_body_B_W(in, &(*qt)->sonNW);
		read_body_B_W(in, &(*qt)->sonNE);
		read_body_B_W(in, &(*qt)->sonSE);
		read_body_B_W(in, &(*qt)->sonSW);
	} else {
		read_B_W(in, node);
	}
}

void read_unite(BitFile* in, Byte* unite){
	int i;

	for(i = 7; i >= 0; i--){
		if(read_BitFile(in) == 1)
			*unite = pow(2, i);
	}
}

void read_color(BitFile* in, Node* node){
	int i;
	Byte color[4] = {0, 0, 0, 0};

	for(i = 0; i < 4; i++){
		read_unite(in, &(color[i]));
	}
	node->rgba = create_color(color);
}

void read_body_color(BitFile* in, Quadtree* qt){
	Node* node;
	assert(qt != NULL);	
	
	node = create_node(NULL, NULL);
	if(read_BitFile(in) == 0){
		*qt = node;
		read_body_color(in, &(*qt)->sonNW);
		read_body_color(in, &(*qt)->sonNE);
		read_body_color(in, &(*qt)->sonSE);
		read_body_color(in, &(*qt)->sonSW);
	} else {
		read_color(in, node);
	}
}

int decompression(char* file_name, Quadtree* qt, int display_type){
	BitFile in;

	assert(qt != NULL);
	assert(file_name != NULL);

	init_BitFile(&in, file_name, "r");
	if(display_type == 1){
		read_body_color(&in, qt);
	} else {
		read_body_B_W(&in, qt);
	}
	return 1;
}
