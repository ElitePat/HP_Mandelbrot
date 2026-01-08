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

    // Variables
    // Pour la définition de la zone qu'on veut déssiner.
    double startx, endx;
    double starty, endy;
    /*  Par défaut on établi -2-i;1+i, soit start=[-2;-1] et end=[1;1].
    Il faut savoir que si le choix de la zone n'est pas coherent avec la taille de l'image
    on peut avoir un dessin plus ou moins allongé/étiré. */

    // Méethodes
    // Fonction qui renvoie en sortie le nombre d'itérations pour que le complexe donné diverge
    int iter_mandel(const std::complex<double> c);

    // Fonction qui associe une couleur au degrée de divergence calculé
    void color_mandel(int x, int y, int degre, unsigned char color_selector(int rgb, int d));

public:

    // Constructeur
    MandelBrot(int h, int w);

    // Réglage de la zone qu'on veut dessiner
    int set_zoom(double sx, double ex, double sy, double ey);

    // Fonction qui modifie le double vecteur de l'image pour obtenir le dessin du Mandelbrot
    void draw_mandel();

    // Méthode pour faire n images d'un seul appel
    void run(int const& n);

};


#endif // MANDELBROT_H