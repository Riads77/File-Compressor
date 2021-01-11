#ifndef __TREE__
#define __TREE__

#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include "Pixel.h"

typedef struct data{
	int pos_image_x; //coordonnées au coin NORD OUEST de l'image
	int pos_image_y;

	int width_x; // l'image en largeur hauteur
	int height_y;
}Data;



typedef enum binary_color{
	NODE = 0,
	WHITE = 10,
	BLACK = 11
}Binary_color;

typedef struct node{

	Data *coord;
	MLV_Color color;
	struct node *NO, *NE, *SE, *SO;
    int level;

}Node, *Tree;

	Node *allocateNode(MLV_Color color, Data *data,int level);
	Data *allocateData(int x, int y, int width , int height);
	void subdivise_nodes(Tree root,MLV_Image *image,int remaining_level);
	void creerFichier(Tree root, FILE* fichier,MLV_Image *image);
	void creerFichier_BW(Tree root,FILE *fichier,MLV_Image *image);



#endif