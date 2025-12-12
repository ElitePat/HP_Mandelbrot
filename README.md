# HIGH PERFORMANCE MANDELBROT

Le but de ce projet est d'avoir un programme qui nous permette de réaliser des belles images de fractales, principalement le Mandelbrot, ses variantes et d'autres figures géometriques similiaires, uniquement en 2D. On utilisera le langage C++, tout en implementant differentes optimisations.

## Description du projet

### Mandelbrot

On se place dans un plan complexe, avec en abcsisse les nombres réels et en ordonées les nombres complexes. L'ensemble de Mndelbrot dans un tel plan est défini par tous les points $c$ bornées par l'application de la suite complexe $(Z_n)$ suivante:

$$ z_{n+1} = z_n^2 + c $$

avec

$$ z_0 = 0 $$

Le resultat obtenu est une fractale.

<img src="images\Mandelbrot.png" alt="Mandelbrot Set" style="margin-left: 100px;" width="800px"/>
<!-- marge a gauche de 100 pixels et taille de 800 pixels -->

### Objectifs

Le but de ce projet est de concevoir un programme pour réaliser cette fractale (dans un premier temps). Il est possible de modifier les differentes couleurs, mais une attention particulière sera porté à la performance du code. En effet, dans une approche naîve du problème, le calcul des points $c$ qui convergent est théoriquement infini. On est obligé de choisir un seuil maximal à partir duquel on considère que le point consideré ne diverge pas. Le choix de ce seuil peut affecter le détail du dessin final et la repartition des couleurs.

Le fichier [Documentation.pdf](doc/Documentation.pdf) explore certaines pistes pour optimiser le calcul de l'ensemble de Mandelbrot et d'autres manières d'appréhender le problème.

Ainsi nous implementerons plusieures versions (succesives), avec differentes approches/optimisations.

Le prgramme produit en sortie des images en format Portable Network Graphics (PNG). Des formats facilitant l'implémentation existent, mais ici nous avons fait le choix d'un format plus portable.

## Structure du projet

- Le dossier [data](data) contient differents jeux de données (resultats de tests de performance, pour l'instant vide)
- Le dossier [doc](doc) contient la documentation expliquant plus en détail certains points du projet ... 
- Le dossier [images](images) est le répertoire de sortie de la production d'images du programme
- Le dossier [src](src) contient les fichiers source du programme.
<!-- Le dossier build n'est pas à propager! -->

## Tester sur sa propre machine

### Prérequis

- Version minimale de CMake: 3.28 (vérifier avec la commande `cmake --version`)
- Le projet nécessite l'installation des libraries libpng (librarie de manipulation de png pour C/C++) et zlib (librairie de compression utilsé par le format png). Sans quoi le programme ne compilera pas.
    - Pour verifier leur présence:
    ```bash
    dpkg -l | grep zlib1g-dev
    dpkg -l | grep libpng-dev
    ```
    - Pour les installer en cas d'abscence de resultat des commandes precdentes:
    ```bash
    sudo apt-get install zlib1g-dev
    sudo apt-get install libpng-dev
    ```
- Il est recomandé d'utilser le compilateur GNU, sinon il faudra modifier les options de compilation en fonction du compilateur choisi dans le fichier [CMakeLists.txt](CMakeLists.txt).

### Procedure

Après avoir installé le projet sur sa machine (via git, ou autre moyen), ouvrir le terminal, créer un dossier build au sein du dossier HP_Mandelbrot et se placer dedans. 
```bash
mkdir build
cd build
```
Ensuite on tape la commande suivante pour construire le projet:
```bash
cmake ..
```
Ensuite on va compiler le projet:
```bash
cmake --build .
```
Pour executer le programme on execute la commande :
```bash
./Main.exe
```
[Si on est pas sur un OS Windows (où WSL) il faudra changer le nom de l'executable dans la fonction add_executable() dans le fichier  [CMakeLists.txt](CMakeLists.txt)]

Pour modifier la disposition des couleurs (le plus important) il faut se rendre dans le fichier [Color.cpp](src/code/Color.cpp).
L'idéal serait d'imiter l'approche utilsé par l'une des fonctions présente dans ce fichier. Il faudrait alors inclure le nom de la fonction crée où modifiée en tant que dernier argument, dans l'appel de la fonction `color_mandel()` dans le fichier [MandelBrot.cpp](src/code/MandelBrot.cpp).

Pour nettoyer le dossier build (correctement) faire:
```bash
cd build
cmake --build . --target my_clean && cd ../
```

## Autres remarques

L'utilisation de l'IA n'a été faite qu'une seule fois. Et son usage se resume dans le code du fichier source [exemple_png_mistral_ia.cpp](src/code/exemple_png_mistral_ia.cpp), qui m'a facilité l'écriture de la fonction permettant de creer une image png.
