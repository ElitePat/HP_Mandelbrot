#include "../headers/MandelBrot.h"


// Construeur: on utilise celui de la classe parent
MandelBrot::MandelBrot(int h, int w) : ImagePNG::ImagePNG(h,w) {}


// Fonction qui renvoie en sortie le nombre d'itérations pour que le complexe donné diverge
int MandelBrot::iter_mandel(const std::complex<double> c){

    // Variables
    int cmpt = 0;
    std::complex<double> z(0,0);

    // Boucle d'itération principale
    while((std::abs(z) < 2.0) && (cmpt < MAX_ITER)){
        // Fonction du Mandelbrot par défaut
        z = pow(z,2) + c; // z = z^2 + c
        ++cmpt;
    }

    return cmpt;
}

// Fonction qui associe une couleur au degrée de divergence calculé
void MandelBrot::color_mandel(int x, int y, int degree, unsigned char color_selector(int rgb, int d)){

    // On associe une couleur au degree
    unsigned char r, g, b; //teinte=0; // Attention format RVBA (rouge, vert, bleu, alpha) !

    if(degree == MAX_ITER){ // couleur noire OK
        r = (unsigned char)(0);
        g = (unsigned char)(0); 
        b = (unsigned char)(0); 
    }else{        
        r = color_selector(0,degree);
        g = color_selector(1,degree);
        b = color_selector(2,degree);
    }
    //std::cout << "x:" << x << ",y:" << y << " => " << degree << "\n"; // debug line

    // On sauvegarde la couleur obtenue
    image_px->at(y).at(x*4) = r;
    image_px->at(y).at(x*4 + 1) = g;
    image_px->at(y).at(x*4 + 2) = b;
    image_px->at(y).at(x*4 + 3) = 255; // degre d'opacité maximal
    
}

// Fonction qui modifie le double vecteur de l'image pour obtenir le dessin du Mandelbrot
void MandelBrot::draw_mandel(){

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
            color_mandel(x,y,iter_mandel(c), experience);
        }
    }

}
