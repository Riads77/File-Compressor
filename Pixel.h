#ifndef __PIXEL__
#define __PIXEL__

#include <MLV/MLV_all.h>
#include <stdlib.h>
#include <assert.h>

#define NB_LINES 512
#define NB_COLUMNS 512



MLV_Color average_color_partial_image(MLV_Image* image, int x, int y, int nb_lines, int nb_columns);
void average_color_image(MLV_Image* image);

void set_average_color_image(MLV_Color color, MLV_Image* image, int x, int y, int nb_lines, int nb_columns);
#endif