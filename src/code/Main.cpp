#include <iostream>
#include <chrono>      // Chronométre

#include "../headers/MandelBrot.h"


const std::string picture_path = "../images/";

// Fonction Principale
int main(){

    std::cout << "Dessin MandelBrot.\n";

    // On défini la taille de l'image (en pixels)
    const int height=7500, width=1000; // 7 500 000 pixels à calculer !

    // création de l'image png
    MandelBrot* mb = new MandelBrot{height,width};
    // on laisse les marges par défaut

    // on lance le chronomètre
    const auto debut{std::chrono::steady_clock::now()};
    // On fait les calculs pour l'image
    mb->draw_mandel();
    // on arrete le chronomètre
    const auto fin{std::chrono::steady_clock::now()};
    // on calcule affiche le temps passé
    const std::chrono::duration<double> tcl{(fin - debut)}; // passage des nanosecondes au secondes
    std::cout << "Temps de calcul du dessin = " << tcl.count() << "\n";    

    //mb->printpxl(); // debug line

    // Creation de l'image (avec le double vecteur modifié)
    mb->crea_png((picture_path + "Mandelbrot10.png").c_str());

    // Libération de la mémoire
    delete mb;

    // On sort du programme
    std::cout << "Sortie du programme de dessin." << std::endl;
    return 0;

}