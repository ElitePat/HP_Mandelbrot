#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <cmath>


/**     Ce fichier source à été élaboré afin qu'on puisse rajouter des fonctions
 * de coloration personelles. Au lieu de modifier des choses dans le fichier "MandelBrot.cpp".
 * Ainsi, on collectionne dans un même fichier les differentes colorations possibles du
 * Mandelbrot.
 */


// coloration de base
unsigned char base(int rgb, int d);

// 3 phase gradient blue green blue !!
unsigned char blue_green_blue(int rgb, int d);

// experimental fonction
unsigned char exp(int rgb, int d);


#endif // COLOR_H