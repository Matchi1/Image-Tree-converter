#ifndef __EXTENSION__
#define __EXTENSION__

/**
 * Verify the extension of a file.
 * @parameters file_name a String containing the name of a file.
 * @return 1 if the file have the '.qtc' extension
 * 0 if it has the '.qtn' extension else -1.
 */
int extension_qt(char* file_name);

/**
 * Verify the extension of a file.
 * @parameters file_name a String containing the name of a file.
 * @return 1 if the file have the '.qtn' extension
 * 0 if it has the '.qtc' extension else -1.
 */
int extension_min(char* file_name);

#endif
