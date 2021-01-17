#include "graphique.h"

void display_node(Tree root,MLV_Image *image){
	MLV_Color color;
	int pos_x = root->coord->pos_image_x;
	int pos_y = root->coord->pos_image_y;
	int width_x = root->coord->width_x;
	int height_y = root->coord->height_y;

	color =  MLV_rgba(root->color.red,root->color.green,root->color.blue,root->color.alpha);
    set_average_color_image(color, image,pos_x , pos_y, width_x ,height_y);
    MLV_draw_partial_image(image, pos_x, pos_y,width_x,height_y,pos_x,pos_y);
	MLV_actualise_window();

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



void draw_button(){
    int taille_interligne = 5;
    MLV_draw_text_box( X_BOUTON1+400, Y_BOUTON1, 200, 35, "LOAD AN IMAGE", taille_interligne, MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box( X_BOUTON1+400, Y_BOUTON1+50, 200, 35, "QUADTREE", 10, MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box( X_BOUTON1+400, Y_BOUTON1+100, 200, 35, "BINARY BACKUP B&W", taille_interligne, MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box( X_BOUTON1+400, Y_BOUTON1+150, 200, 35, "BINARY BACKUP RGBA", taille_interligne, MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box( X_BOUTON1+400, Y_BOUTON1+200, 200, 35, "MINIMIZATION", taille_interligne, MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box( X_BOUTON1+400, Y_BOUTON1+250, 200, 35, "BACKUP GRAPH B&W", taille_interligne, MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box( X_BOUTON1+400, Y_BOUTON1+300, 200, 35, "BACKUP GRAPH RGBA", taille_interligne, MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box( X_BOUTON1+400, Y_BOUTON1+350, 200, 35, "EXIT", taille_interligne, MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}


int menu_choice(int x, int y){
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

MLV_Image *loadPicture(){
	/*
		Le but de cette methode est de charger une image.
	*/
    char* text;
    MLV_Image* image = NULL;

    MLV_wait_input_box(X_BOUTON1+400, Y_BOUTON1+400, 200, 35, MLV_COLOR_WHITE, MLV_COLOR_BLUE, MLV_COLOR_WHITE, "Fichier: ", &text);

    image = MLV_load_image(text);
    if (image == NULL){
     MLV_draw_text( X_BOUTON1+400, Y_BOUTON1+440, "Erreur de saisie.", MLV_COLOR_WHITE);
     MLV_actualise_window();
    }

    return image;
}

int manage_button(){
	int x1, y1;
	MLV_wait_mouse(&x1, &y1);

	int choix = menu_choice(x1, y1);

	if (choix == 8){
        return 0;

	}else{
		return choix;
	}

}

