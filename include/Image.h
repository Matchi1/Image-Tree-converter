#ifndef __IMAGE__
#define __IMAGE__

#include <MLV/MLV_all.h>
#include "Quadtree.h"

/**
 * This structure contains informations about an image
 * More specifically its name and its representation
 * in the MLV_Image structure
 * This structure is useful to understand the coding
 */
typedef struct {
	char* file_name;
	MLV_Image* img;
}Image;

/**
 * @brief Return the path of the specified file name
 * @param file_name a file name
 * @ret the path of this file
 */
char* path_image(char* file_name);

/**
 * @brief Load an image with the path of a file
 * @param path the path of the file
 * @ret a MLV_Image structure representing an image
 */
MLV_Image* load_image(char* path);

/**
 * @brief Initialize an Image structure
 * @param info a pointor to an image structure
 * @param file_name a file_name
 */
void init_image(Image* info, char* file_name);

/**
 * @brief free an Image structure
 * @param info a pointor to an Image structure
 */
void free_image(Image* info);

#endif
