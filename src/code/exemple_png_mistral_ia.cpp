#include <png.h>
#include <iostream>
#include <vector>
#include <cstdlib>

void writePNG(const char* filename, int width, int height) {
    // Créer un fichier pour écrire l'image PNG
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        std::cerr << "Impossible d'ouvrir le fichier pour écriture" << std::endl;
        return;
    }

    // Initialiser la structure png
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) {
        std::cerr << "Erreur lors de la création de la structure png" << std::endl;
        fclose(fp);
        return;
    }

    // Initialiser la structure info png
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        std::cerr << "Erreur lors de la création de la structure info png" << std::endl;
        png_destroy_write_struct(&png_ptr, nullptr);
        fclose(fp);
        return;
    }

    // Configurer la gestion des erreurs
    if (setjmp(png_jmpbuf(png_ptr))) {
        std::cerr << "Erreur lors de l'écriture de l'image PNG" << std::endl;
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        return;
    }

    // Lier le fichier à la structure png
    png_init_io(png_ptr, fp);

    // Configurer les informations de l'image
    png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    // Écrire les informations de l'image
    png_write_info(png_ptr, info_ptr);

    // Créer une image blanche
    std::vector<png_byte> row(width * 3, 255);
    for (int y = 0; y < height; ++y) {
        png_write_row(png_ptr, row.data());
    }

    // Terminer l'écriture de l'image
    png_write_end(png_ptr, nullptr);

    // Nettoyer et fermer le fichier
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
}

int main() {
    const char* filename = "image_blanche.png";
    int width = 800;
    int height = 600;

    writePNG(filename, width, height);

    std::cout << "Image blanche créée avec succès: " << filename << std::endl;

    return 0;
}
