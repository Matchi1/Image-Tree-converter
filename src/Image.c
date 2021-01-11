#include <stdio.h>
#include <string.h>
#include "../include/Image.h"
#include "../include/Extension.h"

char* path_image(char* file_name){
	int file_name_len;
	int path_len;
	char* path;
	if(file_name != NULL){
		file_name_len = strlen(file_name);	
		path_len = file_name_len + 4 + 1;
		path = (char*)malloc(sizeof(char) * path_len);
		if(NULL == path)
			return NULL;
		strcpy(path, "img/");
		strcat(path, file_name);
	}
	return path;
}

MLV_Image* load_image(char* path){
	MLV_Image* image = MLV_load_image(path); 
	MLV_resize_image(image, 512, 512);
	return image;
}

void init_image(Image* info, char* file_name){
	char* path_img;

	path_img = path_image(file_name);
	info->file_name = path_img;
	if(extension_qt(path_img) == -1)
		info->img = load_image(path_image(file_name));
	else
		info->img = NULL;
	free(file_name);
}
