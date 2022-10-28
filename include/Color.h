#ifndef __COLOR__
#define __COLOR__

/**
 * @brief Initialize the rgba array with the specified values
 * @param rgba an array representing rgba values
 * @param r red value
 * @param g green value
 * @param b blue value 
 * @param a alpha value
 */
void init_color(int* rgba, int r, int g, int b, int a);

/**
 * @brief Create a new color depending on the argument.
 * @param rgba an array representing a color.
 * @ret a pointor to this color.
 */
int* create_color(int r, int g, int b, int a);

/**
 * @brief Display the colors contained in color.
 * @param color a pointor to a Color. 
 * @ret void.
 */
void display_color(int* color);

/**
 * @brief Compare c1 and c2.
 * @param c1 a pointor to a Color. 
 * @param c2 a pointor to a Color.
 * @ret 1 if c1 is the same color as c2 else 0.
 */
int verify_color(int* c1, int* c2);

/**
 * @brief Convert a color into black or white color.
 * @param color a pointor to a Color.
 * @ret void.
 */
void convert_rgba_to_BW(int* color);

/**
 * @brief Determine which color, between black and white,
 * the specified color is closer to
 * @param color an array representing a color
 * @ret 0 means the color is closer to white than black else 1
 */
int black_or_white(int* color);

/**
 * Verify if 2 colors are the same or not
 * @param c1 an array representing a color
 * @param c2 an array representing a color
 * @ret 1 if the 2 colors are equals else 0
 */
int color_equals(int* c1, int* c2);

/**
 * Free the memory space used by a color
 * @param color a an array representing a color
 */
void free_color(int* color);

#endif
