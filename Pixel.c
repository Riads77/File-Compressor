#include "Pixel.h"

MLV_Color average_color_partial_image(MLV_Image* image, int x, int y, int nb_lines, int nb_columns){
    int red = 0, green = 0, blue = 0, alpha = 0;
    int new_red = 0, new_green = 0, new_blue = 0, new_alpha = 0;
    int i, j;

    //assert(color != NULL && image != NULL);
    assert(x >= 0 && x < NB_LINES && y >= 0 && y < NB_COLUMNS);
    //assert(nb_lines >= 0 && nb_lines < NB_LINES && nb_columns >= 0 && nb_columns < NB_COLUMNS);
   // assert( x + nb_lines >= 0 && x + nb_lines < NB_LINES && y + nb_columns >= 0 && y + nb_columns < NB_COLUMNS);

    for(i = x; i < x + nb_lines; i++){
        for(j = y; j < y + nb_columns; j++){
            MLV_get_pixel_on_image(image, i, j, &new_red, &new_green, &new_blue, &new_alpha);
            red = red + new_red;
            green = green + new_green;
            blue = blue + new_blue;
            alpha = alpha + new_alpha;
            new_red = 0;
            new_green = 0;
            new_blue = 0;
            new_alpha = 0;
        }
    }
    red /= (nb_lines * nb_columns);
    green /= (nb_lines * nb_columns);
    blue /= (nb_lines * nb_columns);
    alpha /= (nb_lines * nb_columns);

    return MLV_rgba(red,green,blue,alpha);
}


void set_average_color_image(MLV_Color color, MLV_Image* image, int x, int y, int nb_lines, int nb_columns){
    int i,j;

    /*assert(color != NULL && image != NULL);
    assert(x >= 0 && x < NB_LINES && y >= 0 && y < NB_COLUMNS);
    assert(nb_lines >= 0 && nb_lines < NB_LINES && nb_columns >= 0 && nb_columns < NB_COLUMNS);
    assert( x + nb_lines >= 0 && x + nb_lines < NB_LINES && y + nb_columns >= 0 && y + nb_columns < NB_COLUMNS);*/

     for(i = x; i < x + nb_lines; i++){
        for(j = y; j < y + nb_columns; j++){
           MLV_set_pixel_on_image(i,j,color,image);
        }
    }
}

int isMonochrome(MLV_Image* image, int x, int y, int taille){
    /*
        Cette fonction nous aide a savoir si une partie d'image est monochrome ou pas.
        Elle renvoie la couleur de l'image si elle est monochrome, sinon elle renvoie -1.
    */
    int i, j, couleurHG, couleur;
    MLV_get_pixel_on_image(image, x, y, &couleurHG, NULL, NULL, NULL);
    for (i=x; i<x+taille; i++){
        for (j=y; j<y+taille; j++){
            MLV_get_pixel_on_image(image, i, j, &couleur, NULL, NULL, NULL);
            if (couleurHG != couleur)
                return 0;
        }
    }
    return 1;
}


/*
int distance_pixels(MLV_Color *color1, MLV_Color *color2){
    assert(color1 != NULL && color2 != NULL);
    return sqrt((color1 -> R - color2 -> R) * (color1 -> R - color2 -> R)
            + (color1 -> G - color2 -> G) * (color1 -> G - color2 -> G)
            + (color1 -> B - color2 -> B) * (color1 -> B - color2 -> B)
            + (color1 -> A - color2 -> A) * (color1 -> A - color2 -> A));
}

int error_color_image(MLV_Color *average_color, const MLV_Image* image, int x, int y, int nb_lines, int nb_columns){
    int error = 0;
    int i, j;

    MLV_Color *pixel;

    assert(average_color != NULL && image != NULL);
    assert(x >= 0 && x < NB_LINES && y >= 0 && y < NB_COLUMNS);
    assert(nb_lines >= 0 && nb_lines < NB_LINES && nb_columns >= 0 && nb_columns < NB_COLUMNS);
    assert( x + nb_lines >= 0 && x + nb_lines < NB_LINES && y + nb_columns >= 0 && y + nb_columns < NB_COLUMNS);

    for(i = x; i < x + nb_lines; i++){
        for(j = y; j < nb_columns; j++){
            MLV_get_pixel_on_image(image, i, j, &(pixel -> R), &(pixel -> G), &(pixel -> B), &(pixel -> A));
            error += distance_pixels(average_color, pixel);
        }
    }
    return error;

}*/