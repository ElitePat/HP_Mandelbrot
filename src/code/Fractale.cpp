#include "../headers/Fractale.h"

// Dans l'image on itère sur tous les pixels
void Fractale::calculate_mandel(){

    // on calcule le pas avec lequel on doit itérer
    double pas_x = fabs(endx - startx) / width;
    double pas_y = fabs(endy - starty) / height;

    // on defini les varaibles avec lequelles on calcule
    std::complex<double> c;
    int x, y;

    // Double-boucle principale
    for(y=0; y<height; y++){
        for(x=0; x<width; x++){
            // on identifie le complexe c associé au point x;y
            c = std::complex<double>(startx + pas_x * x, starty + pas_y * y);

            // On colorie selon le niveau de divergence et la fonction rentrée en paramétre en dernier !
            color_fract(x,y,iter_fract(c), exp);
        }
    }
}