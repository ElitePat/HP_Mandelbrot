#include <iostream>
#include <chrono>      // Chronométre
#include "../headers/MandelBrot.h"

#define DEF_ITER 100

// Fonction Principale
int main(){

    std::cout << "Dessin MandelBrot.\n";

    // On défini la taille de l'image (en pixels)
    const int height=750, width=1000; // 750 000 pixels à calculer par image!

    // création de l'image png
    MandelBrot* mb = new MandelBrot{height,width};
    // on laisse les marges par défaut

    // on lance le chronomètre
    const auto debut{std::chrono::steady_clock::now()};
    // On fait les calculs pour n images
    mb->run(DEF_ITER);
    // on arrete le chronomètre
    const auto fin{std::chrono::steady_clock::now()};
    // on calcule affiche le temps passé
    const std::chrono::duration<double> tcl{(fin - debut)}; // passage des nanosecondes au secondes
    std::cout << "Temps de calcul de " << DEF_ITER << " dessins = " << tcl.count() << "\n";
    std::cout << "Soit en moyenne " << tcl.count()/DEF_ITER << " secondes par image \n";

    // Libération de la mémoire
    delete mb;

    // On sort du programme
    std::cout << "Sortie du programme de dessin." << std::endl;
    return 0;

}