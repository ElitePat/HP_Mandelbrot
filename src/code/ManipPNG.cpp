#include "../headers/ManipPNG.h"


// Fonction de test création PNG
void test_crea_png(const char *filename){

    int y, width=100, height=100;

    // ouverture du fichier en écriture
    FILE *fichier = fopen(filename,"wb");
    if(!fichier){// Si l'ouverture du fichier n'as pas réussi
        // Mesage d'erreur
        std::cerr << "Impossible d'ouvrir le fichier" << std::endl;
        return;
    }

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if(!png){
        // Mesage d'erreur
        std::cerr << "Impossible de creer la structure png" << std::endl;
        // On ferme le fichier
        fclose(fichier);
        return;
    }

    png_infop info = png_create_info_struct(png);
    if(!info){
        // Mesage d'erreur
        std::cerr << "Impossible de creer la structure info" << std::endl;
        // On ferme le fichier
        fclose(fichier);
        return;
    }

    if(setjmp(png_jmpbuf(png))){
        // Mesage d'erreur
        std::cerr << "Erreur au niveau de setjmp()" << std::endl;
        // On ferme le fichier
        fclose(fichier);
        // destruction des structures
        png_destroy_write_struct(&png, &info); // recomendation de la doc
        return;
    }

    png_init_io(png, fichier); // association de png avec fichier

    // Output is 8bit depth, RGBA format.
    png_set_IHDR(
        png,
        info,
        width, height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );
    // écrire les informations de l'image
    png_write_info(png, info);

    // Création image blanche
    /* -- C'est cette partie de code qui nous interresse particulièrement pour le code du Mandelbrot !! -- */
    std::vector<png_byte> row(width * 4, 150);
    for (y = 0; y < height; ++y) {
        png_write_row(png, row.data());
    }
    /* --------------------------------------------------------------------------------------------------- */

    // Terminer l'écriture de l'image
    png_write_end(png, NULL);

    // Fermeture du fichier
    fclose(fichier);

    // destruction des structures
    png_destroy_write_struct(&png, &info);
}

// Creation de l'image à partir du double tableau
void crea_png(const char *filename, int height, int width, std::vector<std::vector<png_byte>> image_px){

    // ouverture du fichier en écriture
    FILE *fichier = fopen(filename,"wb");
    if(!fichier){// Si l'ouverture du fichier n'as pas réussi
        // Mesage d'erreur
        std::cerr << "Impossible d'ouvrir le fichier" << std::endl;
        return;
    }

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if(!png){
        // Mesage d'erreur
        std::cerr << "Impossible de creer la structure png" << std::endl;
        // On ferme le fichier
        fclose(fichier);
        return;
    }

    png_infop info = png_create_info_struct(png);
    if(!info){
        // Mesage d'erreur
        std::cerr << "Impossible de creer la structure info" << std::endl;
        // On ferme le fichier
        fclose(fichier);
        return;
    }

    if(setjmp(png_jmpbuf(png))){
        // Mesage d'erreur
        std::cerr << "Erreur au niveau de setjmp()" << std::endl;
        // On ferme le fichier
        fclose(fichier);
        // destruction des structures
        png_destroy_write_struct(&png, &info); // recomendation de la doc
        return;
    }

    png_init_io(png, fichier); // association de png avec fichier

    // Output is 8bit depth, RGBA format.
    png_set_IHDR(
        png,
        info,
        width, height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );
    // écrire les informations de l'image
    png_write_info(png, info);

    // Création image
    for(int i=height-1; i>=0; --i){ // parcours en sens inverse pour que image soit à l'endroit
        png_write_row(png, image_px[i].data());
    }

    // Terminer l'écriture de l'image
    png_write_end(png, NULL);

    // Fermeture du fichier
    fclose(fichier);

    // destruction des structures
    png_destroy_write_struct(&png, &info);

}

