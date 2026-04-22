#include "../headers/Color.h"


std::vector<unsigned char> base(int d){
    unsigned char res = (unsigned char)(30 + 20*d);
    return {res,res,res};
}

std::vector<unsigned char> blue_green_blue(int d){
    unsigned char r = (unsigned char)(95);
    unsigned char g = (unsigned char)((-1*abs(d-500))/2+255);
    unsigned char b = (unsigned char)(150);
    return {r,g,b};
}

std::vector<unsigned char> experience(int d){
    unsigned char r = (unsigned char)(-1*(d*22));
    unsigned char g = (unsigned char)(1*(abs(d-500))/2+255);
    unsigned char b = (unsigned char)(75 + 20*d);
    return {r,g,b};
}