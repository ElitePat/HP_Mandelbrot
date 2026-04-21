#include "../headers/MandelBrot.h"


// Construeur: on utilise celui de la classe parent
MandelBrot::MandelBrot(int h, int w) : ImagePNG::ImagePNG(h,w) {
    // pour la plage des données on défini des valeurs par défaut
    startx=-2.01;
    endx=0.7;
    starty=-1.2;
    endy=1.2;
}

// Réglage de la zone qu'on veut dessiner
int MandelBrot::set_zoom(double sx, double ex, double sy, double ey){
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

// Fonction (critique) qui renvoie en sortie le resultat de l'application de la suite z*z+c jusqu'à z_MAX_ITER
double MandelBrot::iter_mandel(const std::complex<double> c){

    /** Dans cette version de iter_mandel on a choisit de scinder la boucle principale en 2, car pour certains nombres
    la suite diverge bien avant d'atteindre MAX_ITER */

    // Variables
    int i;
    std::complex<double> z(0,0);
    
    // Première boucle d'itération principale
    for(i=0; i<HALF_MAX_ITER; i++){
        // Suite originale de l'ensemble de Mandelbrot
        z = z*z + c; // z = z^2 + c
    }

    if(std::abs(z) < 2.0){
        // Deuxième boucle d'itération principale
        for(i=HALF_MAX_ITER; i<MAX_ITER; i++){
            // Suite originale de l'ensemble de Mandelbrot
            z = z*z + c; // z = z^2 + c
        }
    }

    return std::abs(z);
}

// Fonction qui associe une couleur au degrée de divergence calculé
void MandelBrot::color_mandel(int x, int y, double degree, unsigned char color_selector(int rgb, int d)){

    // On associe une couleur au degree
    unsigned char r, g, b; //teinte=0; // Attention format RVBA (rouge, vert, bleu, alpha) !

    if(degree >= 2.0){ // couleur noire OK
        r = (unsigned char)(0);
        g = (unsigned char)(0); 
        b = (unsigned char)(0); 
    }else{
        int tmp = int((degree*256) / 2.0);
        r = color_selector(0,tmp);
        g = color_selector(1,tmp);
        b = color_selector(2,tmp);
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


// Méthode pour faire plusieures images d'un seul appel
void MandelBrot::run(int const& n){
    
    // Variables
    std::string filename = "mb-cpu";
    double sx, ex, sy, ey;
    
    // on fixe un point de depart
    const double orgzx=0.2509784563981121, orgzy=-0.00004652030450813527;
    // et un zoom de départ (on tient compte ici du format de l'image: 4:3)
    //sx = orgzx - (0.5 * width/height);
    sx = 0.25097845639782700999376174877397716045379638671875;
    //ex = orgzx + (0.5 * width/height);
    ex = 0.25097845639839722053920922917313873767852783203125;
    //sy = orgzy - 0.5;
    sy = -4.6520304721948746e-05;
    //ey = orgzy + 0.5;
    ey = -4.652030429432179e-05;

    // de combien on zoom pour chaque itération
    double zoom = 0.25;

    #ifndef NDEBUG
    std::cout << "Itération\tPlage de données (en xmin,ymin - xmax,ymax)\tZoom = " << zoom << "\n";
    #endif

    // Boucle principale
    for(int i=0; i<n; ++i){

        // Debug output
        #ifndef NDEBUG
        std::cout << i << "\t\t" << "[" << printf("%.75f",sx) << ";" << std::format("{}",sy) 
        << "] -> [" << printf("%.75f",ex) << ";" << std::format("{}",ey) << "]\n";
        #endif

        
        // test sur les plages des données !
        if(!set_zoom(sx,ex,sy,ey)){
            draw_mandel();
            crea_png((filename + std::to_string(100+i)).c_str());
        }else{
            std::cout << "Erreur dans le zoom\n";
            break;
        }

        // on redefini le zoom
        /* Ici on regle le zoom par rapport à l'image precedente. On utilise fabs() pour avoir la distance entre
        l'origine du zoom et les bors de l'image et on reduit cette distance de zoom fois. Avec zoom < 1 ! */
        sx += fabs(orgzx - sx) * zoom;
        ex -= fabs(orgzx - ex) * zoom;      
        sy += fabs(orgzy - sy) * zoom;
        ey -= fabs(orgzy - ey) * zoom;

    }
}