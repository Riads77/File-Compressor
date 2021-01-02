#ifndef __TREE__
#define __TREE__

#include <stdlib.h>
#include <MLV/MLV_all.h>


typedef struct data{
	int pos_image_x; //centre de la feuille en x et y
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
	Binary_color colo;
	struct node *NO, *NE, *SE, *SO;


}Node, *Tree;

	Node *allocateNode(Binary_color Color, Data *data);
	Data *allocateData(int x, int y, int width , int height);
	void subdivise_nodes(Tree root);


#endif