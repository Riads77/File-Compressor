#include "Pixel.h"

Color average_color_partial_image(MLV_Image* image, int x, int y, int nb_lines, int nb_columns){
    int red = 0, green = 0, blue = 0, alpha = 0;
    int new_red = 0, new_green = 0, new_blue = 0, new_alpha = 0;
    int i, j;
    Color color;

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

    color.red = red;
    color.green = green;
    color.blue = blue;
    color.alpha = alpha;

   return color;
}


void set_average_color_image(MLV_Color color, MLV_Image* image, int x, int y, int nb_lines, int nb_columns){
    int i,j;

     for(i = x; i < x + nb_lines; i++){
        for(j = y; j < y + nb_columns; j++){
           MLV_set_pixel_on_image(i,j,color,image);
        }
    }
}

int isMonochrome(MLV_Image* image, int x, int y, int taille){
   
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
