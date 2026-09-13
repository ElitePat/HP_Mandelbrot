#include <iostream>
#include <chrono>      // Chronométre
#include "../headers/MandelBrot.h"

#define DEF_ITER 20

// Fonction Principale
int main(){

    std::cout << "Programme du dessin du MandelBrot.\n";

    // On défini la taille de l'image (en pixels)
    const int height=750, width=1000; // 750 000 pixels à calculer par image!

    // création de l'image png
    MandelBrot* mb = new MandelBrot{height,width};
    // on laisse les marges par défaut

    // vérifications au niveau du zoom à réaliser
    if(!mb->verif_data(DEF_ITER)){ // si tout est OK

        // on lance le chronomètre
        const auto debut{std::chrono::steady_clock::now()};
        // On fait les calculs pour n images
        mb->run(DEF_ITER);
        // on arrete le chronomètre
        const auto fin{std::chrono::steady_clock::now()};
        // on calcule et affiche le temps passé
        const std::chrono::duration<double> tcl{(fin - debut)}; // passage des nanosecondes au secondes
        std::cout << "Temps de calcul pour " << DEF_ITER << " dessins du Mandelbrot = " << tcl.count() << "\n";
        std::cout << "Soit en moyenne " << tcl.count()/DEF_ITER << " secondes par image \n";

    } // sinon on sort du programme

    // Libération de la mémoire
    delete mb;

    // On sort du programme
    std::cout << "Sortie du programme de dessin." << std::endl;
    return 0;

}