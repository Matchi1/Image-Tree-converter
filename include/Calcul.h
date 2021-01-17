#ifndef __CALCUL__
#define __CALCUL__

#include "Color.h"
#include "Pixel.h"

/**
 * Calculate the distance between 2 rgba value
 * @param c1 an array of int
 *    	  c2 an array of int
 * @return the distance between the 2 rgba value
 */
float dist(const int* c1, const int* c2);

/**
 * Calculate the error value of a Pixel structure
 * compared with the current image
 * @param img a pointor to a MLV_Image structure
 * 		  area a pointor to a Pixel structure
 * @return the error value
 */
int error(MLV_Image* img, Pixel* area);

/**
 * Determine the average color of a certain zone
 * of an image
 * @param img a pointor to a MLV_Image
 * 		  area a pointor to a Pixel structure
 */
void average_color(MLV_Image* img, Pixel* area);

#endif
