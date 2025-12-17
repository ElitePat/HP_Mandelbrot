#ifndef MANIPPNG_H
#define MANIPPNG_H

#include <iostream>    // sortie standard
#include <fstream>     // gestion des fichiers
#include <cstdlib>     // Pour FILE*
#include <png.h>       // gestion fichiers PNG
#include <zlib.h>      // compression fichiers PNG
#include <vector>


// Fonction de test création PNG
void test_crea_png(const char *filename);

// Creation de l'image à partir du double tableau
void crea_png(const char *filename, int height, int width, std::vector<std::vector<png_byte>> image_px);


#endif // MANIPPNG_H