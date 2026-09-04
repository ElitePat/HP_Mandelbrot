# Fichier CMakeLists.txt à la racine du projet


# Spécification de la version minimale de CMake requise:
cmake_minimum_required(VERSION 3.28)
# Idéalement CMake 4.0 (dernière version stable Juin 2025)

# enable modern C++ (en a-t-on vraiment besoin ?)
# set(CMAKE_CXX_STANDARD 20)

# Nom du projet
project(HP_MANDELBROT CXX) # Indique que c'est un projet C++

# --- Recherche des dépendances externes ---

# Recherche de PNG (REQUIRED signifie que CMake échouera si PNG n'est pas trouvé)
find_package(PNG REQUIRED)

if(PNG_FOUND)
    message(STATUS "PNG library found at ${PNG_LIBRARIES}")
    message(STATUS "PNG include dir: ${PNG_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "PNG not found! Please install libpng development files.")
endif()

# Recherche de OpenMP, mêmes exigeances que précedement
find_package(OpenMP REQUIRED)

if(!OpenMP_FOUND)
    message(FATAL_ERROR "OpenMP not found! Please install OpenMP dependencies.")
endif()


# --- Définition des répertoires sources et headers ---

# Répertoire contenant les fichiers .cpp
# Basé sur la structure : HP_Mandelbrot/src/code/
set(CODE_DIR ${CMAKE_SOURCE_DIR}/src/code)

# Répertoire contenant les fichiers .h
# Basé sur la structure : HP_Mandelbrot/src/headers/
set(HEADERS_DIR ${CMAKE_SOURCE_DIR}/src/headers)


# --- Liste de TOUS les fichiers sources (.cpp) pour l'exécutable "Main.exe" ---

# Doit inclure TOUS les .cpp dont le code à besoin pour compiler et les lier.
set(MAIN_SRC
    ${CODE_DIR}/Main.cpp     
    ${CODE_DIR}/ImagePNG.cpp
    ${CODE_DIR}/MandelBrot.cpp
    ${CODE_DIR}/Color.cpp
    # Ajouter les fichiers sources ici au fur et à mésure de leur création.
)


# --- Configuration de compilation ---

# Ajouter les répertoires d'en-têtes
include_directories(${HEADERS_DIR}) # Ton répertoire d'en-têtes (où sont les headers)
include_directories(${PNG_INCLUDE_DIRS}) # En-têtes PNG trouvés par find_package

# Options de compilation standard
add_compile_options(-std=c++20 -Wall -Wextra -pedantic -lm -lpng -lz -mcmodel=large -march=native -funroll-loops)
# Options de warning strictes et de performances maximales !
#lm -> maths, lpng -> libpng, lz -> zlib


# --- Création des exécutables ---

# Ajout des executables
add_executable(Main.exe ${MAIN_SRC})


# --- Lier les bibliothèques aux exécutables ---

# Ici les librairies sont liées en PRIVATE
target_link_libraries(Main.exe PRIVATE OpenMP::OpenMP_CXX)

# Ici les librairies sont liées en mode PUBLIC (mode par défaut quand aucun <keyword> n'est spécifié)
target_link_libraries(Main.exe PUBLIC
    ${PNG_LIBRARIES} # Lie la bibliothèque PNG trouvée
)

# --- Création des cibles (personalisés) ---

# Cible pour réaliser le dessin
#add_custom_target() # Pour le moment ctest suffit

# Cible pour nettoyer le répertoire de build
add_custom_target(my_clean
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMENT "Cleaning all contents in the build directory (${CMAKE_BINARY_DIR})"
)

# Cibles pour le débogage avec GDB ...


# --- Ajout des test automatiques: commande ctest ---

enable_testing()
add_test(Test Main.exe)