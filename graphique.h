#ifndef H_GRAPHIQUE
#define H_GRAPHIQUE
#include <MLV/MLV_all.h>
#include "Pixel.h"
#include "Tree.h"

#define SIZE 512
#define X_BOUTON1 150
#define Y_BOUTON1 50
/*
        Parametres : La racine ,l'image
		Retour: void
		But: Affiche le noeud de l'arbre actuel 
*/
void display_node(Tree root,MLV_Image *image);

/*
	Parametres: La racine , l'image , les levels restant
	Retour: void
	But: Fais un parcours préfixe pour afficher tout les noeuds de l'arbre
*/
void display_tree(Tree root, MLV_Image *image,int display_level);

/*
	Parametres: Rien
	Retour: void
	But: Dessine tout les boutons sur la fenêtre d'affichage
*/
void draw_button();
/*
	Parametres: Rien
	Retour: 0 si l'utilisateur quitte sinon un int
	But : Permet de gèrer le click de l'utilisateur sur l'interface graphique
*/
int manage_button();

/*
	Parametres : Rien
		Retour : Une image
		But: Permet à l'utilisateur de pouvoir choisir l'image à charger
*/

MLV_Image *loadPicture();
#endif