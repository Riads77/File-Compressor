#ifndef H_GRAPHIQUE
#define H_GRAPHIQUE
#include <MLV/MLV_all.h>
#include "Pixel.h"
#include "Tree.h"

#define SIZE 512
/*Fonction qui permet de charger une image en 512-512 et de la recadrer*/
MLV_Image *load_image();
void display_node(Tree root,MLV_Image *image);
#endif