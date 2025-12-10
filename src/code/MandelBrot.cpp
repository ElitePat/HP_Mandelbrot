#include "../headers/MandelBrot.h"
#include "../headers/Color.h"


int iter_mandel(const std::complex<double> c){

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


void color_mandel(int x, int y, int degree, std::vector<std::vector<png_byte>>& mandel_pixels, unsigned char mandelbrot_color(int rgb, int d)){

    // On associe une couleur au degree
    unsigned char r, g, b; //teinte=0; // Attention format RVBA (rouge, vert, bleu, alpha) !

    if(degree == MAX_ITER){ // couleur noire OK
        r = (unsigned char)(0);
        g = (unsigned char)(0); 
        b = (unsigned char)(0); 
    }else{        
        r = mandelbrot_color(0,degree);
        g = mandelbrot_color(1,degree);
        b = mandelbrot_color(2,degree);
    }
    //std::cout << "x:" << x << ",y:" << y << " => " << degree << "\n"; // debug line

    // On sauvegarde la couleur obtenue
    mandel_pixels[y][x*4] = r;
    mandel_pixels[y][x*4 + 1] = g;
    mandel_pixels[y][x*4 + 2] = b;
    mandel_pixels[y][x*4 + 3] = 255; // degre d'opacité maximal
    
}


void calculate_mandel(const double startx, const double starty, const double endx, const double endy, 
    const int h, const int w, std::vector<std::vector<png_byte>>& mandel_pixels){

    // on calcule le pas avec lequel on doit itérer
    double pas_x = fabs(endx - startx) / w;
    double pas_y = fabs(endy - starty) / h;

    // on defini les varaibles avec lequelles on calcule
    std::complex<double> c;
    int x, y;

    // Double-boucle principale
    for(y=0; y<h; y++){
        for(x=0; x<w; x++){
            // on identifie le complexe c associé au point x;y
            c = std::complex<double>(startx + pas_x * x, starty + pas_y * y);

            // On colorie selon le niveau de divergence et la fonction rentrée en paramétre en dernier !
            color_mandel(x,y,iter_mandel(c), mandel_pixels, exp);
        }
    }

}
