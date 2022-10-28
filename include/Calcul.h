#ifndef __CALCUL__
#define __CALCUL__

#include "Color.h"
#include "Pixel.h"

/**
 * @brief Calculate the distance between 2 rgba value
 * @param c1 an array of int
 * @param c2 an array of int
 * @ret the distance between the 2 rgba value
 */
float dist(const int* c1, const int* c2);

/**
 * @brief Calculate the error value of a Pixel structure
 * compared with the current image
 * @param img a pointor to a MLV_Image structure
 * @param area a pointor to a Pixel structure
 * @ret the error value
 */
int error(MLV_Image* img, Pixel* area);

/**
 * @brief Determine the average color of a certain zone
 * of an image
 * @param img a pointor to a MLV_Image
 * @param area a pointor to a Pixel structure
 */
void average_color(MLV_Image* img, Pixel* area);

#endif
