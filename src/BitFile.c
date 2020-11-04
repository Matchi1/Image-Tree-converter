#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/BitFile.h"

#define BIT_MAX 8

BitFile* create_BitFile(char* file_name, char* format){
	BitFile* f;

	assert(file_name != NULL);
	assert(format != NULL);

	f = (BitFile*)malloc(sizeof(BitFile));
	if(f == NULL)
		return NULL;

	init_BitFile(f, file_name, format);
	return f;
}

void init_BitFile(BitFile* f, char* file_name, char* format){
	f->file = fopen(file_name, format);
	f->nb_bit = 0;
	f->buf = 0;
}

int close_BitFile(BitFile* f){
	if(f->nb_bit != BIT_MAX){
		f->buf <<= BIT_MAX - f->nb_bit;
		fputc(f->buf, f->file);
	}
	return fclose(f->file);
}

int buffer_full(BitFile* f){
	if(f->nb_bit == BIT_MAX)
		return 1;
	return 0;	
}

int read_BitFile(BitFile* in){
	char n;
	if(in->nb_bit == 0){
		n = fgetc(in->file);	
		if(n == EOF)
			return EOF;
		in->buf = n;
		in->nb_bit = BIT_MAX;
	}
	in->nb_bit--;
	return (in->buf >> in->nb_bit) & 1;
}

void write_BitFile(BitFile* out, int bit){

	if(buffer_full(out)){
		out->nb_bit = 0;
		fputc(out->buf, out->file);
	}
	out->nb_bit++;
	out->buf = (out->buf << 1) | bit;
}
