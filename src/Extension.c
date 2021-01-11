#include <stdio.h>
#include <stdlib.h>
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

int index_dot(char* file_name){
	int i, file_len;

	file_len = strlen(file_name);
	for(i = 0; i < file_len && file_name[i] != '.'; i++);
	return i;
}

char* extension_save_file(char* file_name, int bool_color){
	int len_new_name, len_name;
	char* new_name;

	len_name = index_dot(file_name) + 1;
	len_new_name = len_name + 3 + 1;
	new_name = (char*)malloc(sizeof(char) * len_new_name);
	if(new_name == NULL)
		return new_name;
	strncpy(new_name, file_name, len_name);
	if(bool_color == 1)
		strcat(new_name, "qtc");
	else
		strcat(new_name, "qtn");
	return new_name;
}
