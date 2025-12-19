#ifndef MANDELBROT_H
#define MANDELBROT_H


#include <iostream>
#include <vector>
#include <png.h>       // gestion des png_bytes
#include <cmath>       // pour les opération mathématiques
#include <complex>     // pour la manipulation de nombres complexes (à faire seulement lors des itérations de convergence)
#include "ImagePNG.h"
#include "Color.h"

#define MAX_ITER 1024


class MandelBrot : public ImagePNG {
private:

    // Fonction qui renvoie en sortie le nombre d'itérations pour que le complexe donné diverge
    int iter_mandel(const std::complex<double> c);

    // Fonction qui associe une couleur au degrée de divergence calculé
    void color_mandel(int x, int y, int degre, unsigned char color_selector(int rgb, int d));

public:

    // Constructeur
    MandelBrot(int h, int w);

    // Fonction qui modifie le double vecteur de l'image pour obtenir le dessin du Mandelbrot
    void draw_mandel();

};


#endif // MANDELBROT_H