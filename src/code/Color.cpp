#include "../headers/Color.h"


unsigned char base(int rgb, int d){
    unsigned char res;
    switch (rgb)
    {
    case 0:
        res = (unsigned char)(30 + 20*d);
        break;
    case 1:
        res = (unsigned char)(30 + 20*d);
        break;

    case 2:
        res = (unsigned char)(30 + 20*d);
        break;

    default:
        std::cerr << "Not expected value given" << std::endl;
        res = 0;
        break;
    }
    return res;
}

unsigned char blue_green_blue(int rgb, int d){
    unsigned char res;
    switch (rgb)
    {
    case 0:
        res = (unsigned char)(95);
        break;
    case 1:
        res = (unsigned char)((-1*abs(d-500))/2+255);
        break;

    case 2:
        res = (unsigned char)(150);
        break;

    default:
        std::cerr << "Not expected value given" << std::endl;
        res = 0;
        break;
    }
    return res;
}

unsigned char experience(int rgb, int d){
        unsigned char res;
    switch (rgb)
    {
    case 0:
        res = (unsigned char)(-1*(d*22));
        break;
    case 1:
        res = (unsigned char)(1*(abs(d-500))/2+255);
        break;

    case 2:
        res = (unsigned char)(75 + 20*d); // 150 de base
        break;

    default:
        std::cerr << "Not expected value given" << std::endl;
        res = 0;
        break;
    }
    return res;
}