#ifndef MANDELBROT_H
#define MANDELBROT_H


#include <iostream>
#include <vector>
#include <png.h>       // gestion des png_bytes
#include <cmath>       // pour les opération mathématiques
#include <complex>     // pour la manipulation de nombres complexes (à faire seulement lors des itérations de convergence)


#define MAX_ITER 1024
//const int MAX_ITER = 1024;

// Fonction qui renvoie en sortie le nombre d'itérations pour que le complexe donné diverge
int iter_mandel(const std::complex<double> c);

// Fonction qui associe une couleur au degrée de divergence calculé
void color_mandel(int x, int y, int degree, std::vector<std::vector<png_byte>>& mandel_pixels);

// Fonction qui modifie le double tableau pour obtenir le dessin du Mandelbrot
void calculate_mandel(const double startx, const double starty, const double endx, const double endy, 
    const int h, const int w, std::vector<std::vector<png_byte>>& mandel_pixels);


#endif // MANDELBROT_H