#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include "../include/Graphic.h"
#include "../include/Quadtree.h"
#include "../include/Compression.h"
#include "../include/Decompression.h"
#include "../include/Test.h"

int main(int argc, char const *argv[]){
	if(test() == 1)
		printf("Test réussi.\n");

	return 0;
}
