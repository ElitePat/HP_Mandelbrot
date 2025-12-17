#include "../headers/ImagePNG.h"


// Definition of class execption function
const char* ImagePNG::InvalidImageArg::what(){
    return message;
}

// Définition du constructeur
ImagePNG::ImagePNG(int h, int w) : height(h), width(w) {

    /* Si les arguments fournis ne sont pas bons on va lever une execption
    Il n'est pas supposé que l'erreur soit gerer (attrapé) lors de l'appel
    du constructeur, étant donnée qu'on voudrait que cela provoque l'arrêt
    du programme! */

    // aucun argument négatif
    if((height <= 0) || (width <= 0)){
        std::cout << "Les données fournies sont négatives !\n";
        std::cout << "Echec du dessin" << std::endl;
        throw InvalidImageArg();
    }

    // Limite pour la taille des images et pour la taille du double vecteur
    if(height*width >= IMG_SIZE_LIMIT){ 
        std::cout << "Image trop grande pour être calculé.\n";
        std::cout << "Échec du dessin" << std::endl;
        throw InvalidImageArg();
    }
    
    // pour la plage des données on défini des valeurs par défaut
    startx=-2.01;
    endx=0.7;
    starty=-1.2;
    endy=1.2;

    // on initalise le double vecteur
    std::vector<std::vector<png_byte>> image_px(height, std::vector<png_byte>(width*4));

}

    // Réglage de la zone qu'on veut dessiner
int ImagePNG::set_zoom(double sx, double ex, double sy, double ey){
    startx = sx;
    endx = ex;
    starty = sy;
    endy = ey;

    // >= car on veut une zone de dessin non vide !
    if((startx >= endx) || (starty >= endy)){ 
        std::cout << "Mauvaises plages de données.\n";
        std::cout << "Échec du dessin" << std::endl;
        return 1; // sortie d'echec (utile pour ctest)
    }

    return 0;
}

// On affiche les pixels sur le terminal
void ImagePNG::printpxl(){
    // On itérer sur le double vecteur
    for(std::vector<png_byte> row : image_px){
        for(png_byte px : row){
            std::cout << (unsigned int)px << " ";
        }
        std::cout << "\n";
    }
    // Utile pour vérifier les élements du double vecteur
}

// Creation de l'image à partir du double tableau
void ImagePNG::crea_png(const char *filename){

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