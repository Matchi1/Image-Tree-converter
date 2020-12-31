#include <stdio.h>
#include <string.h>
#include "../include/Extension.h"

int extension_qt(char* file_name){
	char* extension_c;
	char* extension_B_W;
	int i, len_file_name;	

	extension_c = ".qtc";
	extension_B_W = ".qtn";
	len_file_name = strlen(file_name);
	
	for(i = 0; i < len_file_name; i++){
		if(file_name[i] == '.'){
			if(strcmp(&(file_name[i]), extension_c) == 0)
				return 0;
			if(strcmp(&(file_name[i]), extension_B_W) == 0)
				return 1;
		}
	}
	return -1;
}
