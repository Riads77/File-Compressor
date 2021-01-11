#ifndef H_GRAPHIQUE
#define H_GRAPHIQUE
#include <MLV/MLV_all.h>
#include "Pixel.h"
#include "Tree.h"

#define SIZE 512
#define X_BOUTON1 150
#define Y_BOUTON1 50
/*Fonction qui permet de charger une image en 512-512 et de la recadrer*/
MLV_Image *load_image();
void display_node(Tree root,MLV_Image *image);
void display_tree(Tree root, MLV_Image *image,int display_level);
void dessiner_boutons();
int gerer_bouton(Tree root,MLV_Image *image,int level_max);
#endif