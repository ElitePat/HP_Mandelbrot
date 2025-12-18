#include <chrono>      // Chronométre

#include "../headers/MandelBrot.h"
#include "../headers/ManipPNG.h"
#include "../headers/ImagePNG.h"

#define LIMIT 100000000 // 10^8


const std::string picture_path = "../images/";

// Fonction Principale
int main(){

    std::cout << "Dessin MandelBrot.\n";

    // On défini la taille de l'image (en pixels)
    const int height=750, width=1000; // 75 000 000 pixels à calculer !

    // création de l'image png
    ImagePNG* mb = new ImagePNG{height,width};
    // on laisse les marges par défaut

    // on lance le chronomètre
    const auto debut{std::chrono::steady_clock::now()};
    // On fait les calculs pour l'image
    std::cout << "ok1\n";
    //calculate_mandel(startx,starty,endx,endy,height,width,*mb->image_px);
    std::cout << "ok2\n";
    // on arrete le chronomètre
    const auto fin{std::chrono::steady_clock::now()};
    // on calcule affiche le temps passé
    const std::chrono::duration<double> tcl{(fin - debut)}; // passage des nanosecondes au secondes
    std::cout << "Temps de calcul du dessin = " << tcl.count() << "\n";    

    //mb->printpxl(); // debug line

    // Creation de l'image (avec le double vecteur modifié)
    mb->crea_png((picture_path + "Mandelbrot12.png").c_str());

    // Libération de la mémoire
    delete mb;

    // On sort du programme
    std::cout << "Sortie du programme de dessin." << std::endl;
    return 0;

}

/** Ensuite il faut coder l'héritage de ImagePNG, soit Fractale et MandelBrot
    en vue d'impléménter la fonction calculate_mandel() comme il le faut  */