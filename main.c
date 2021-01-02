#include <stdio.h>
#include "graphique.h"
#include "Pixel.h"
#include "Tree.h"

int main(int argc, char const *argv[]){

	MLV_Image *image;
	Data *data = allocateData(0, 0, NB_LINES , NB_COLUMNS);
	Tree root = allocateNode(0,data);

	MLV_create_window("puzzle", "puzzle", SIZE+250, SIZE);
    image = load_image();
    
    subdivise_nodes(root);
   // display_node(root,image);
    display_tree(root, image);
    //MLV_draw_image(image, root->coord->pos_image_x, root->coord->pos_image_y);
    MLV_draw_image(image,0,0);
    MLV_actualise_window();
    MLV_wait_seconds(60);
	MLV_free_image(image);
	MLV_free_window();


    return 0;
}