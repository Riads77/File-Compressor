#include "graphique.h"
#include "Pixel.h"
#include "Tree.h"



int main(int argc, char const *argv[]){

	MLV_Image *image;
	
	int exit = 1;
	int current_lvl = 1;
	Data *data = allocateData(0, 0, NB_LINES , NB_COLUMNS);
	Tree root = allocateNode(0,data,0);

	MLV_create_window("QuadTree", "QuadTree", SIZE+250, SIZE);
    image = load_image();
    MLV_draw_image(image,0,0);
    dessiner_boutons();
    MLV_actualise_window();

    while(exit != 0){
    	 exit = gerer_bouton(root,image,8);
    }

    return 0;
}