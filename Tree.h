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

typedef struct node{

	Data *coord;
	Color color;
	struct node *parent;
	struct node *NO, *NE, *SE, *SO;
    int level;

}Node, *Tree;
	/*
		Parametres : La couleur a associé à un noeud , une variable data qui contient les informations sur l'image (position,taille), le level 
		Retour : Un noeud 
		But : Permet d'initialiser les attributs de Node
	*/
	Node *allocateNode(Color color, Data *data,int level);

	/*
		Parametres : La couleur a associé à un noeud , une variable data qui contient les informations sur l'image (position,taille), le level 
		Retour : Un noeud 
		But : Permet d'initialiser les attributs de Node
	*/

	Data *allocateData(int x, int y, int width , int height);
	/*
		Parametres : Un noeud, un pointeur d'image et le niveau
		Retour : void
		But: Divise le root en 4 nodes.
	*/
	void subdivise_nodes(Tree root,MLV_Image *image,int remaining_level);
	/*
		Parametres : Un noeud
		Retour : void
		But: Fusionner les feuilles de la même couleur.
    */
	void optimise_tree_leaf(Node *node);
	/*
		Parametres : Une couleur et un table d'entier
		Retour : void
		But: Convertir un nombre décimal et binaire.
	*/
	void Converttobinary(int rgba , int *byte);
	/*
		Parametres : Un noeud,un pointeur de fichier et un pointeur d'image
		Retour : void
		But: Convertir un quadtree dan un fichier texte.
	*/
	void createFile(Tree root, FILE* fichier,MLV_Image *image);	
	void createFile_BW(Tree root,FILE *fichier,MLV_Image *image);



#endif
