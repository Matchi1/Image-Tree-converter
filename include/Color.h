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
 * Initialize a color with black or white.
 * @parameters color a pointor to a Color. 
 * 			   bw a number representing a black(other number) or white(1)
 * @return void.
 */
void init_color_BW(int* color, int bw);

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

int black_or_white(int* color);

#endif
