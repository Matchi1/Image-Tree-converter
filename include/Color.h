#ifndef __COLOR__
#define __COLOR__

typedef unsigned char Byte;

typedef struct color{
	Byte r,g,b,a;
}Color;

/**
 * Create a new color depending  on the argument.
 * @return a pointor to this color.
 */
Color* create_color(Byte* rgba);

/**
 * Initialize a color depending on the argument.
 * @return void.
 */
void init_color(Color* color, Byte* rgba);

/**
 * Display the colors contained in color.
 * @return void.
 */
void display_color(Color* color);

/**
 * Compare c1 and c2.
 * @return 1 if c1 is the same color as c2 else 0.
 */
int verify_color(Color* c1, Color* c2);

#endif