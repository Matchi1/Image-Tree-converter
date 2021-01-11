#ifndef __EXTENSION__
#define __EXTENSION__

/**
 * Verify the extension of a file.
 * @parameters file_name a String containing the name of a file.
 * @return 0 if the file have the '.qtc' extension
 * 1 if it has the '.qtn' extension else -1.
 */
int extension_qt(char* file_name);

/**
 * Verify the extension of a file.
 * @parameters file_name a String containing the name of a file.
 * @return 0 if the file have the '.qtn' extension
 * 1 if it has the '.qtc' extension else -1.
 */
int extension_min(char* file_name);

char* extension_save_file(char* file_name, int bool_color);

#endif
