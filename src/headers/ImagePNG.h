#ifndef IMAGEPNG_H
#define IMAGEPNG_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>      // gestion des fichiers
#include <cstdlib>      // Pour FILE*
#include <png.h>        // gestion fichiers PNG
#include <zlib.h>       // compression fichiers PNG
#include <exception>    // pour gerer les exceptions

#define IMG_SIZE_LIMIT 100000000 // 10^8
const std::string picture_path = "../images/";


class ImagePNG{
protected:

    // On défini la taille de l'image (en pixels)
    const int height, width;

    // Déclaration du double tableau de png_byte
    std::vector<std::vector<png_byte>> *image_px;

    // We also implement custom execptions who are part of the ImagePNG class
    class InvalidImageArg : public std::exception {
    private:
        const char *message = "Arguments pour la création de l'image non valides";
    public:
        InvalidImageArg() = default;
        const char* what();
    };

public:

    // Constructeur
    ImagePNG(int h, int w);
    // Destructeur, désallue le double vecteur 
    virtual ~ImagePNG(); // virtual pour destruction des classes derivées

    // Affichage des pixels sur le terminal
    void printpxl(); // utile pour debug

    // Creation de l'image à partir du double tableau
    void crea_png(std::string const& filename);

};

#endif // IMAGEPNG_H