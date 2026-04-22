#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <cmath>
#include <vector>


/**     Ce fichier source à été élaboré afin qu'on puisse rajouter des fonctions
 * de coloration personelles. Au lieu de modifier des choses dans le fichier "MandelBrot.cpp".
 * Ainsi, on collectionne dans un même fichier les differentes colorations possibles du
 * Mandelbrot.
 */


// coloration de base
std::vector<unsigned char> base(int d);

// 3 phase gradient blue green blue !!
std::vector<unsigned char> blue_green_blue(int d);

// experimental fonction
std::vector<unsigned char> experience(int d);


#endif // COLOR_H