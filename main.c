#include "graphique.h"
#include "Pixel.h"
#include "Tree.h"


int main(int argc, char const *argv[]){

	MLV_Image *image;
	FILE *fichier = NULL;
	Tree root = NULL;
	Data *data;
    Color color;
	int bt = 1;
	int i;
	int level_max = 10;

	MLV_create_window("QuadTree", "QuadTree", SIZE+250, SIZE);

/**Afficher le menu avec les boutons */
    draw_button();
    MLV_actualise_window();

    while(bt != 0){
    	 bt = manage_button();
    	 if (bt == 1){
            printf("LOAD AN IMAGE\n");
            image = loadPicture();
            if (image != NULL) {
                MLV_resize_image_with_proportions(image, SIZE, SIZE);
                MLV_draw_image(image,0,0);
                MLV_actualise_window();
             }else{
                printf("NULL");
             }
            }
        if (bt == 2){
        printf("QUADTREE\n");
        /* Initialisation premier noeud level 0*/
        data = allocateData(0, 0, NB_LINES , NB_COLUMNS);
        root = allocateNode(color,data,0);
        /*Construction du Quadtree*/
          subdivise_nodes(root,mage,level_max);
            for (i = 0;i<level_max;i++){
                display_tree(root, image,i);
                MLV_wait_seconds(1);
            }
		}

    if (bt == 3){
        printf("BINARY BACKUP BLACK&WHITE\n");
	    fichier = fopen("save/BACKUP_BW.qtn","w");

    	if (fichier != NULL){
    		createFile_BW(root,fichier,image);
    		fclose(fichier);
    	}else{
    		perror("save/BACKUP_BW.qtn");
    	}

		remove("BACKUP_BW.txt");

	}

	if (bt == 4){
		printf("BINARY BACKUP RGBA\n");
		   fichier = fopen("save/BACKUP_rgba.qtc","w");

    	if (fichier != NULL){
            //subdivise_nodes(root,image,level_max);
    		createFile(root,fichier,image);
    		fclose(fichier);
    	}else{
    		perror("save/BACKUP_rgba.qtc");
    	}
	}
    if (bt == 5){
		printf("MINIMIZATION\n");
		if (root == NULL) {
		/* Initialisation premier noeud level 0*/
        data = allocateData(0, 0, NB_LINES , NB_COLUMNS);
        root = allocateNode(color,data,0);
        /*Construction du Quadtree*/
          subdivise_nodes(root,image,level_max);
          }
        optimise_tree_leaf(root);
         for (i = 0;i<level_max;i++){
                display_tree(root, image,i);
                MLV_wait_seconds(1);
            }
	}

	if (bt == 6){
		printf("BACKUP GRAPH BLACK&WHITE\n");
	}

	if (bt == 7){
		printf("BACKUP GRAPH RGBA\n");
	}
	} // while

    return 0;
}
