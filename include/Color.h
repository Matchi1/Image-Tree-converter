#ifndef __COLOR__
#define __COLOR__

/**
 * Initialize the rgba array with the specified values
 * @parameters rgba an array representing rgba values
 * 			   r red value
 * 			   g green value
 * 			   b blue value 
 * 			   a alpha value
 */
void init_color(int* rgba, int r, int g, int b, int a);

/**
 * Create a new color depending on the argument.
 * @parameters rgba an array representing a color.
 * @return a pointor to this color.
 */
int* create_color(int r, int g, int b, int a);

/**
 * Display the colors contained in color.
 * @parameters color a pointor to a Color. 
 * @return void.
 */
void display_color(int* color);

/**
 * Compare c1 and c2.
 * @parameters c1 a pointor to a Color. 
 * 			   c2 a pointor to a Color.
 * @return 1 if c1 is the same color as c2 else 0.
 */
int verify_color(int* c1, int* c2);

/**
 * Convert a color into black or white color.
 * @parameters color a pointor to a Color.
 * @return void.
 */
void convert_rgba_to_BW(int* color);

/**
 * Determine which color, between black and white,
 * the specified color is closer to
 * @param color an array representing a color
 * @return 0 means the color is closer to white
 * than black else 1
 */
int black_or_white(int* color);

/**
 * Verify if 2 colors are the same or not
 * @param c1 an array representing a color
 * 		  c2 an array representing a color
 * @return 1 if the 2 colors are equals else 0
 */
int color_equals(int* c1, int* c2);

/**
 * Free the memory space used by a color
 * @param color a an array representing a color
 */
void free_color(int* color);

#endif
