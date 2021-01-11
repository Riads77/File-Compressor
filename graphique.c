#include "graphique.h"



MLV_Image *load_image(){
	int width = SIZE;
	int height = SIZE;
    int image_width, image_height;
	MLV_Image *image;

	image = MLV_load_image("monster.jpg");
	//image = MLV_load_image("chess.png");
	MLV_resize_image_with_proportions(image, width, height);
	MLV_get_image_size(image, &image_width, &image_height);

	return image;
}


void display_node(Tree root,MLV_Image *image){
	MLV_Color color;
	int pos_x = root->coord->pos_image_x;
	int pos_y = root->coord->pos_image_y;
	int width_x = root->coord->width_x;
	int height_y = root->coord->height_y;

	color = root->color;
    set_average_color_image(color, image,pos_x , pos_y, width_x ,height_y);
    MLV_draw_partial_image(image, pos_x, pos_y,width_x,height_y,pos_x,pos_y);
	MLV_actualise_window();
	//free(tmp_image);

}

void display_tree(Tree root, MLV_Image *image,int display_level){
		if (root->level == display_level){
			 display_node(root,image);
		}else{

			   if (root->NO != NULL){
		        display_tree(root->NO,image,display_level);
		        display_tree(root->NE,image,display_level);
				display_tree(root->SO,image,display_level);
				display_tree(root->SE,image,display_level);
			   } 
		}
}



void dessiner_boutons(){
    int taille_interligne = 5;
    MLV_draw_text_box( X_BOUTON1+400, Y_BOUTON1, 200, 35, "LOAD AN IMAGE", taille_interligne, MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box( X_BOUTON1+400, Y_BOUTON1+50, 200, 35, "QUADTREE", 10, MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box( X_BOUTON1+370, Y_BOUTON1+100, 250, 35, "BINARY BACKUP BLACK&WHITE ", taille_interligne, MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box( X_BOUTON1+400, Y_BOUTON1+150, 200, 35, "BINARY BACKUP RGBA", taille_interligne, MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box( X_BOUTON1+400, Y_BOUTON1+200, 200, 35, "MINIMIZATION", taille_interligne, MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box( X_BOUTON1+400, Y_BOUTON1+250, 200, 35, "MINIMIZED GRAPH BLACK&WHITE", taille_interligne, MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box( X_BOUTON1+400, Y_BOUTON1+300, 200, 35, "MINIMIZED GRAPH RGBA", taille_interligne, MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box( X_BOUTON1+400, Y_BOUTON1+350, 200, 35, "EXIT", taille_interligne, MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}


int choix_menu(int x, int y){
	/* Dans cette fonction on renvoie le numero de chaque bouton de coordonne (x, y)*/
    int i = 15, h = 35;
    if ((x >= X_BOUTON1+400) && (x <= X_BOUTON1+400+550) && (y >= Y_BOUTON1) && (y <= Y_BOUTON1+h)){
        return 1; // BOUTON: CHARGER IMAGE
    }
    if ((x >= X_BOUTON1+400) && (x <= X_BOUTON1+400+600) && (y >= Y_BOUTON1+h+i) && (y <= Y_BOUTON1+2*h+i)){
        return 2; // BOUTON: CHARGER UN QUAD_TREE
    }
    if ((x >= X_BOUTON1+400) && (x <= X_BOUTON1+400+650) && (y >= Y_BOUTON1+2*h+2*i) && (y <= Y_BOUTON1+3*h+2*i)){
        return 3; // BOUTON: BACKUP BW
    }
    if ((x >= X_BOUTON1+400) && (x <= X_BOUTON1+400+700) && (y >= Y_BOUTON1+3*h+3*i) && (y <= Y_BOUTON1+4*h+3*i)){
        return 4; // BOUTON: BACKUP RGBA
    }
    if ((x >= X_BOUTON1+400) && (x <= X_BOUTON1+400+750) && (y >= Y_BOUTON1+4*h+4*i) && (y <= Y_BOUTON1+5*h+4*i)){
        return 5; // BOUTON: MINIMIZATION
    }

    if ((x >= X_BOUTON1+400) && (x <= X_BOUTON1+400+800) && (y >= Y_BOUTON1+5*h+5*i) && (y <= Y_BOUTON1+6*h+5*i)){
        return 6; // BOUTON: MINIMIZED GRAPH BW
    }

    if ((x >= X_BOUTON1+400) && (x <= X_BOUTON1+400+850) && (y >= Y_BOUTON1+6*h+6*i) && (y <= Y_BOUTON1+7*h+6*i)){
        return 7; // BOUTON: MINIMIZED GRAPH RGBA
    }

     if ((x >= X_BOUTON1+400) && (x <= X_BOUTON1+400+900) && (y >= Y_BOUTON1+7*h+7*i) && (y <= Y_BOUTON1+8*h+7*i)){
        return 8; // BOUTON: EXIT
    }
    


    return 0;
}

int gerer_bouton(Tree root,MLV_Image *image,int level_max){
	int x1, y1;
	FILE *fichier = NULL;
	MLV_wait_mouse(&x1, &y1);
	int i;
	int c1 = choix_menu(x1, y1);
	if (c1 == 1){
		printf("LOAD AN IMAGE");
	}

	if (c1 == 2){
		subdivise_nodes(root,image,level_max);
		for (i = 0;i<level_max;i++){
			 MLV_wait_seconds(1);
    		 display_tree(root, image,i);
		}
		printf("QUADTREE");
	}

	if (c1 == 3){
		
	    fichier = fopen("img/BACKUP_BW.txt","w");

    	if (fichier != NULL){
    		creerFichier_BW(root,fichier,image);
    		fclose(fichier);
    	}else{
    		perror("img/BACKUP_BW.txt.txt");
    	}
		
		printf("BINARY BACKUP BLACK&WHITE");
		remove("BACKUP_BW.txt");

	}

	if (c1 == 4){
		printf("BINARY BACKUP RGBA");
		   fichier = fopen("img/BACKUP_rgba.txt","w");

    	if (fichier != NULL){
    		creerFichier(root,fichier,image);
    		fclose(fichier);
    	}else{
    		perror("img/BACKUP_rgba.txt.txt");
    	}

		
		
	}

	if (c1 == 5){
		printf("MINIMIZATION");
	}

	if (c1 == 6){
		printf("MINIMIZED GRAPH BLACK&WHITE");
	}

	if (c1 == 7){
		printf("MINIMIZED GRAPH RGBA");
	}

	if (c1 == 8){
			MLV_free_image(image);
			MLV_free_window();
			return 0;
		
	}else{
		return 1;
	}
}

