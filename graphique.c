#include "graphique.h"



MLV_Image *load_image(){
	int width = 512;
	int height = 512;
    int image_width, image_height;
	MLV_Image *image;

	image = MLV_load_image("monster.jpg");
	MLV_resize_image_with_proportions(image, width, height);
	MLV_get_image_size(image, &image_width, &image_height);	
	
	return image;
}


void display_node(Tree root,MLV_Image *image){
	MLV_Color color;

	color = average_color_partial_image(image, root->coord->pos_image_x, root->coord->pos_image_y, root->coord->width_x, root->coord->height_y);
    set_average_color_image(color, image,root->coord->pos_image_x , root->coord->pos_image_y, root->coord->width_x ,root->coord->height_y);
    MLV_draw_image(image, root->coord->pos_image_x, root->coord->pos_image_y);
	MLV_actualise_window();
	
}