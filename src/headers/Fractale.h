#ifndef FRACTALE_H
#define FRACTALE_H


#include <complex>
#include "ImagePNG.h"


/** La classe Fractale est une interface, soit ne doit pas être instancié.
Elle défini les méthodes que les classes dérivées doivent implèmenter      */
class Fractale : public ImagePNG {
public:

    // Dans l'image on itère sur tous les pixels
    void calculate_mandel();

    // fonction caractérisant la fractale
    virtual int iter_fract(std::complex<double> const& c) = 0;

    // fonciton de coloration de la fractale
    virtual int color_fract(int x, int y, int degre, unsigned char color_selector(int rgb, int d)) = 0; // color_selector <-- !!!!!!

};

#endif // FRACTALE_H