#ifndef __EXTENSION__
#define __EXTENSION__

/**
 * @brief Verify the extension of a file.
 * @param file_name a String containing the name of a file.
 * @ret 0 if the file have the '.qtc' extension
 * 1 if it has the '.qtn' extension else -1.
 */
int extension_qt(char *file_name);

/**
 * @brief Create a new file name with the qtc and qtn extension
 * @param file_name a String containing the name of a file.
 * @ret 0 if the file have the '.qtn' extension
 * 1 if it has the '.qtc' extension else -1.
 */
char* extension_save_file(char* file_name, int bool_color);

/**
 * @brief Create a new file name with the mtc and mtn extension
 * @param file_name a String containing the name of a file.
 * @ret 0 if the file have the '.qtn' extension
 * 1 if it has the '.qtc' extension else -1.
 */
char* extension_save_min(char* file_name, int bool_color);

#endif
