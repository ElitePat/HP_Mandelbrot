#ifndef IMAGEPNG_H
#define IMAGEPNG_H

#include <iostream>
#include <vector>
#include <fstream>      // gestion des fichiers
#include <cstdlib>      // Pour FILE*
#include <png.h>        // gestion fichiers PNG
#include <zlib.h>       // compression fichiers PNG
#include <exception>    // pour gerer les exceptions

#define IMG_SIZE_LIMIT 100000000 // 10^8


class ImagePNG{
private:

    // On défini la taille de l'image (en pixels)
    const int height, width;

    // Pour la définition la zone qu'on veut déssiner.
    double startx, endx;
    double starty, endy;
    /*  Par défaut on établi -2-i;1+i, soit start=[-2;-1] et end=[1;1].
    Il faut savoir que si le choix de la zone n'est pas coherent avec la taille de l'image
    on peut avoir un dessin plus ou moins allongé/étiré. */

    // image_px must be private, in future updates

    // We also implement custom execptions who are part of the ImagePNG class
    class InvalidImageArg : public std::exception {
    private:
        const char *message = "Arguments pour la création de l'image non valides";
    public:
        InvalidImageArg() = default;
        const char* what();
    };

public:

    // Déclaration du double tableau de png_byte
    std::vector<std::vector<png_byte>> *image_px;

    // Constructeur
    ImagePNG(int h, int w);
    // Destructeur, désallue le couble vecteur
    ~ImagePNG();

    // Setter:
    // Réglage de la zone qu'on veut dessiner
    int set_zoom(double sx, double ex, double sy, double ey);

    // Affichage des pixels sur le terminal
    void printpxl();

    // Creation de l'image à partir du double tableau
    void crea_png(const char *filename);

};

#endif // IMAGEPNG_H