#include <chrono>      // Chronométre

#include "../headers/MandelBrot.h"
#include "../headers/ManipPNG.h"

#define LIMIT 100000000 // 10^8


const std::string picture_path = "../images/";

// Fonction Principale
int main(){
    std::cout << "Dessin MandelBrot.\n";


    // On défini la taille de l'image (en pixels)
    const int height=750, width=1000; // 75 000 000 pixels à calculer !

    /* On défini la zone qu'on veut déssiner.
    Par défaut on établi -2-i;1+i, soit start=[-2;-1] et end=[1;1].
    Il faut savoir que si le choix de la zone n'est pas coherent avec la taille de l'image
    on peut avoir un dessin plus ou moins allongé/étiré. */
    const double startx=-2.01, endx=0.7;
    const double starty=-1.2, endy=1.2;


    // Vérifications de sécurité (data unit tests)
    if(height*width >= LIMIT){ // Limite pour la taille des images et pour la taille du double vecteur
        std::cout << "Image trop grande pour être calculé.\n";
        std::cout << "Échec du dessin" << std::endl;
        return 1; // sortie d'echec (utile pour ctest)
    }
    if((startx >= endx) || (starty >= endy)){ // >= car on veut une zone de dessin non vide !
        std::cout << "Mauvaises plages de données.\n";
        std::cout << "Échec du dessin" << std::endl;
        return 1; // sortie d'echec (utile pour ctest)
    }

    // Création du double tableau de png_byte
    std::vector<std::vector<png_byte>> mandel_pixels(height, std::vector<png_byte>(width*4)); // 4 valeurs pour chaque pixel !
    //std::cout << "Taille maximale de l'image = " << mandel_pixels.max_size() << "\n"; // debug line

    
    // on lance le chronomètre
    const auto debut{std::chrono::steady_clock::now()};
    // On fait les calculs pour l'image
    calculate_mandel(startx,starty,endx,endy,height,width,mandel_pixels);
    // on arrete le chronomètre
    const auto fin{std::chrono::steady_clock::now()};
    // on calcule affiche le temps passé
    const std::chrono::duration<double> tcl{(fin - debut)}; // passage des nanosecondes au secondes
    std::cout << "Temps de calcul du dessin = " << tcl.count() << "\n";

    /* Debug lines
    // Verifier les élements du double tableau/vecteur
    for(std::vector<png_byte> row : mandel_pixels){
        for(png_byte px : row){
            std::cout << (unsigned int)px << " ";
        }
        std::cout << "\n";
    }
    */
    

    // Creation de l'image (avec le double tableau modifié)
    crea_png((picture_path + "Mandelbrot11.png").c_str(),height,width,mandel_pixels);


    // On sort du programme
    std::cout << "Sortie du programme de dessin." << std::endl;
    return 0;
}