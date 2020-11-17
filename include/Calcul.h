#ifndef __CALCUL__
#define __CALCUL__

#include "Color.h"
#include "Pixel.h"

float dist(const Color* c1, const Color* c2);

int error(MLV_Image* img, Pixel* area);

void average_color(MLV_Image* img, Pixel* area);

#endif