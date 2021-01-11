#include "Tree.h"

Data *allocateData(int x, int y, int width , int height){
	Data *tmp = malloc(sizeof(Data));
		tmp->pos_image_x = x;
		tmp->pos_image_y = y;
		tmp->width_x = width;
		tmp->height_y = height;

	return tmp;
}

Node *allocateNode(MLV_Color color, Data *data,int level){
    Node *tmp = malloc(sizeof(Node));
    if(tmp != NULL){
    	tmp -> coord = data;
        tmp -> color = color;
        tmp -> NO = NULL;
        tmp -> NE = NULL;
        tmp -> SE = NULL;
        tmp -> SO = NULL;
        tmp->level = level;
    }
    return tmp;
}

/*void subdivise_nodes(Tree root,int level){
	int width = root->coord->width_x/2;
	int height = root->coord->height_y/2;
//printf("************** %d ******\n",level);

	if (level > 0){
	level--;
	Data *data_NO = allocateData(root->coord->pos_image_x,root->coord->pos_image_y,width,height);
    Data *data_SO = allocateData(root->coord->pos_image_x,root->coord->pos_image_y + height,width,height);
    Data *data_NE = allocateData(root->coord->pos_image_x + width,root->coord->pos_image_y,width,height);
    Data *data_SE = allocateData(root->coord->pos_image_x + width,root->coord->pos_image_y + height,width,height);

	Node *node1 = allocateNode(0,data_NO);
	Node *node2 = allocateNode(0,data_NE);
	Node *node3 = allocateNode(0,data_SO);
	Node *node4 = allocateNode(0,data_SE);

    node1->parent = root;
    node2->parent = root;
    node3->parent = root;
    node4->parent = root;

	root->NO = node1;
	root->NE = node2;
	root->SO = node3;
	root->SE = node4;


		subdivise_nodes(root->NO,level);
		subdivise_nodes(root->NE,level);
		subdivise_nodes(root->SO,level);
		subdivise_nodes(root->SE,level);
	}
}
*/

void subdivise_nodes(Tree root,MLV_Image *image,int remaining_level){
	int width = root->coord->width_x/2;
	int height = root->coord->height_y/2;
	MLV_Color color1,color2,color3,color4;
	int monochrome;

	if (remaining_level > 0 ){
	    remaining_level--;
		Data *data_NO = allocateData(root->coord->pos_image_x,root->coord->pos_image_y,width,height);
	    Data *data_SO = allocateData(root->coord->pos_image_x,root->coord->pos_image_y + height,width,height);
	    Data *data_NE = allocateData(root->coord->pos_image_x + width,root->coord->pos_image_y,width,height);
	    Data *data_SE = allocateData(root->coord->pos_image_x + width,root->coord->pos_image_y + height,width,height);

	    color1 = average_color_partial_image(image, root->coord->pos_image_x, root->coord->pos_image_y, width,height);
	    color2 = average_color_partial_image(image,root->coord->pos_image_x,root->coord->pos_image_y + height,width,height);
	    color3 = average_color_partial_image(image,root->coord->pos_image_x + width,root->coord->pos_image_y,width,height);
	    color4 = average_color_partial_image(image,root->coord->pos_image_x + width,root->coord->pos_image_y + height,width,height);

		Node *node1 = allocateNode(color1,data_NO,root->level + 1);
		Node *node2 = allocateNode(color2,data_NE,root->level + 1);
		Node *node3 = allocateNode(color3,data_SO,root->level + 1);
		Node *node4 = allocateNode(color4,data_SE,root->level + 1);
		root->NO = node1;
		root->NE = node2;
		root->SO = node3;
		root->SE = node4;


		monochrome = isMonochrome(image,node1->coord->pos_image_x,node1->coord->pos_image_y,width);
		if (monochrome == 0){/*Si la zone est monochrome pas besoin de subdivise*/
			subdivise_nodes(root->NO,image,remaining_level);
			subdivise_nodes(root->NE,image,remaining_level);
			subdivise_nodes(root->SO,image,remaining_level);
			subdivise_nodes(root->SE,image,remaining_level);
		}
		/*subdivise_nodes(root->NO,image,level);
			subdivise_nodes(root->NE,image,level);
			subdivise_nodes(root->SO,image,level);
			subdivise_nodes(root->SE,image,level);*/
	}
}


void creerFichier(Tree root, FILE* fichier,MLV_Image *image){
	
	MLV_Color color;
	int pos_x = root->coord->pos_image_x;
	int pos_y = root->coord->pos_image_y;
	int width_x = root->coord->width_x;
	int height_y = root->coord->height_y;

	color = average_color_partial_image(image, pos_x, pos_y, width_x,height_y);

    if (root->NO == NULL){
    	fprintf(fichier, "1(%d)",color);
        return ;
    }else{
    	fprintf(fichier, "0(%d)",color);
    }



    creerFichier(root->NO, fichier,image);
    creerFichier(root->NE, fichier,image);
    creerFichier(root->SE, fichier,image);
    creerFichier(root->SO, fichier,image);

}

void creerFichier_BW(Tree root,FILE *fichier,MLV_Image *image){

	MLV_Color color;
	int pos_x = root->coord->pos_image_x;
	int pos_y = root->coord->pos_image_y;
	int width_x = root->coord->width_x;
	int height_y = root->coord->height_y;

	color = average_color_partial_image(image, pos_x, pos_y, width_x,height_y);
	fprintf(fichier, "%d\n",MLV_rgba(169,169,169,255));

    if (root->NO == NULL){
    	if (color == MLV_rgba(255,255,255,255)){
    		fprintf(fichier, "1(0)");

    	}

    	if (color == MLV_rgba(0,0,0,255)){
    		fprintf(fichier, "1(1)");
    	}
    	
        return ;
    }else{
    	if (color == MLV_rgba(255,255,255,255)){
    		fprintf(fichier, "0(0)");
    	}

    	if (color == MLV_rgba(0,0,0,255)){
    		fprintf(fichier, "0(1)");
    	}

    	//fprintf(fichier, "test\n");
    }



   /* creerFichier_BW(root->NO, fichier,image);
    creerFichier_BW(root->NE, fichier,image);
    creerFichier_BW(root->SE, fichier,image);
    creerFichier_BW(root->SO, fichier,image);*/


}
