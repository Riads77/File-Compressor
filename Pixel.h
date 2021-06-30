#ifndef __PIXEL__
#define __PIXEL__

#include <MLV/MLV_all.h>
#include <stdbool.h>
#include <assert.h>

#define NB_LINES 512
#define NB_COLUMNS 512
#define LEVEL_MAX 8

typedef struct _Color {
        int red;
        int green;
        int blue;
        int alpha;
} Color;
/*
		Parametres : L'image , les coordonnées et la taille 
		Retour : La couleur de la moyenne 
		But: Permet d'avoir la couleur moyenne d'une partie de l'image 
*/
Color average_color_partial_image(MLV_Image* image, int x, int y, int nb_lines, int nb_columns);
/*
	Parametres : La couleur moyenne , l'image , les coordonnées et la taille 
	Retour : void
	But: Permet de modifier la couleur du pixel de la zone définit par les paramètres taille et coordonnées
*/

void set_average_color_image(MLV_Color color, MLV_Image* image, int x, int y, int nb_lines, int nb_columns);
/*

	Parametres : L'image , les coordonnées et la taille
		Retour :  Elle renvoie la couleur de l'image si elle est monochrome, sinon elle renvoie -1
		But: Cette fonction nous aide a savoir si une partie d'image est monochrome ou pas
*/
int isMonochrome(MLV_Image* image, int x, int y, int taille);
#endif
