#include "../headers/ImagePNG.h"

// On affiche les pixels sur le terminal
void ImagePNG::printpxl(){
    for(std::vector<png_byte> row : mandel_pixels){
        for(png_byte px : row){
            std::cout << (unsigned int)px << " ";
        }
        std::cout << "\n";
    }
    // Utile pour vérifier les élements du double vecteur
}