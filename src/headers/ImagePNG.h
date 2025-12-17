#ifndef IMAGEPNG_H
#define IMAGEPNG_H


#include <iostream>
#include <vector>
#include <fstream>      // gestion des fichiers
#include <cstdlib>      // Pour FILE*
#include <png.h>        // gestion fichiers PNG
#include <zlib.h>       // compression fichiers PNG



#define IMG_SIZE_LIMIT 100000000 // 10^8


class ImagePNG{
private:
    // On défini la taille de l'image (en pixels)
    const int height=750, width=1000; // 75 000 000 pixels au total !

    // On défini la zone qu'on veut déssiner.
    /*  Par défaut on établi -2-i;1+i, soit start=[-2;-1] et end=[1;1].
    Il faut savoir que si le choix de la zone n'est pas coherent avec la taille de l'image
    on peut avoir un dessin plus ou moins allongé/étiré. */
    const double startx=-2.01, endx=0.7;
    const double starty=-1.2, endy=1.2;

    // Déclaration du double tableau de png_byte
    std::vector<std::vector<png_byte>> mandel_pixels;
public:

    // Constructeur
    ImagePNG();
    // Destructeur
    /* Si jamais on alloue les vecteurs il faudra implementer un comportement correct ici ! */
    ~ImagePNG() = default;

    void printpxl();

};

#endif // IMAGEPNG_H