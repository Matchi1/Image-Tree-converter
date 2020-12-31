#ifndef __CALCUL__
#define __CALCUL__

#include "Color.h"
#include "Pixel.h"

float dist(const int* c1, const int* c2);

int error(MLV_Image* img, Pixel* area, int bw);

void average_color(MLV_Image* img, Pixel* area, int bw);

#endif
