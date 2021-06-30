#include "Tree.h"

Data *allocateData(int x, int y, int width , int height){
	Data *tmp = malloc(sizeof(Data));
		tmp->pos_image_x = x;
		tmp->pos_image_y = y;
		tmp->width_x = width;
		tmp->height_y = height;

	return tmp;
}

Node *allocateNode(Color color, Data *data,int level){
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


void optimise_tree_leaf(Node *node){
MLV_Color colorNO;
MLV_Color colorNE;
MLV_Color colorSO;
MLV_Color colorSE;
Node *parent = NULL;

   if (node->SO == NULL) {
      /* node est une feuille, on remonter vers le parent pour récupèrer les 4 feuilles*/
       parent = node->parent;
       colorNO = MLV_rgba(parent->NO->color.red,parent->NO->color.green,parent->NO->color.blue,parent->NO->color.alpha);
       colorNE = MLV_rgba(parent->NE->color.red,parent->NE->color.green,parent->NE->color.blue,parent->NE->color.alpha);
        colorSO = MLV_rgba(parent->SO->color.red,parent->SO->color.green,parent->SO->color.blue,parent->SO->color.alpha);
        colorSE = MLV_rgba(parent->SE->color.red,parent->SE->color.green,parent->SE->color.blue,parent->SE->color.alpha);

             if (colorNO == colorNE) {
                parent->NO = parent->NE ;
             }
             if (colorNO == colorSO) {
                parent->NO = parent->SO ;
             }
             if (colorNO == colorSE) {
                parent->NO = parent->SE ;
             }
             if (colorNE == colorSO) {
                parent->NE = parent->SO ;
             }
             if (colorNE == colorSE) {
                parent->NE = parent->SE ;
             }
             if (colorSO == colorSE) {
                parent->SO = parent->SE ;
             }
    } else {
     optimise_tree_leaf(node->NO);
     optimise_tree_leaf(node->NE);
     optimise_tree_leaf(node->SO);
     optimise_tree_leaf(node->SE);
    };

}


void Converttobinary(int rgba , int *byte) {
  int i;

for(i=0;i < 8;i++)
  {
    byte[i] = rgba%2;
    rgba /= 2;
  };

}


void subdivise_nodes(Tree root,MLV_Image *image,int remaining_level){
	int width = root->coord->width_x/2;
	int height = root->coord->height_y/2;
	Color color1,color2,color3,color4;
	int monochrome;

	if (remaining_level > 0 ){/*Tant qu'il reste des levels on continue à subdiviser */
	    remaining_level--;
        /*On en profite pour rajouter les positions des carrés de couleur et leurs tailles à placer dans les variables data*/
		Data *data_NO = allocateData(root->coord->pos_image_x,root->coord->pos_image_y,width,height);
	    Data *data_SO = allocateData(root->coord->pos_image_x,root->coord->pos_image_y + height,width,height);
	    Data *data_NE = allocateData(root->coord->pos_image_x + width,root->coord->pos_image_y,width,height);
	    Data *data_SE = allocateData(root->coord->pos_image_x + width,root->coord->pos_image_y + height,width,height);
        /*On calcul la couleur moyenne de chaque carré*/
	    color1 = average_color_partial_image(image, root->coord->pos_image_x, root->coord->pos_image_y, width,height);
	    color2 = average_color_partial_image(image,root->coord->pos_image_x,root->coord->pos_image_y + height,width,height);
	    color3 = average_color_partial_image(image,root->coord->pos_image_x + width,root->coord->pos_image_y,width,height);
	    color4 = average_color_partial_image(image,root->coord->pos_image_x + width,root->coord->pos_image_y + height,width,height);

		Node *node1 = allocateNode(color1,data_NO,root->level + 1);
		Node *node2 = allocateNode(color2,data_NE,root->level + 1);
		Node *node3 = allocateNode(color3,data_SO,root->level + 1);
		Node *node4 = allocateNode(color4,data_SE,root->level + 1);

        /*On rattache le noeud actuel au noeud parent*/
		node1->parent = root;
        node2->parent = root;
        node3->parent = root;
        node4->parent = root;

		root->NO = node1;
		root->NE = node2;
		root->SO = node3;
		root->SE = node4;

        /*Pour chaque zone on vérifie si les pixels ont la même couleur. Si oui on continue à subdiviser*/
		monochrome = isMonochrome(image,node1->coord->pos_image_x,node1->coord->pos_image_y,width);
		if (monochrome == 0){
        /*La zone a plusieurs couleur donc appel récursive pour diviser*/
			subdivise_nodes(root->NO,image,remaining_level);
			subdivise_nodes(root->NE,image,remaining_level);
			subdivise_nodes(root->SO,image,remaining_level);
			subdivise_nodes(root->SE,image,remaining_level);
		}

	}
}


void createFile(Tree root, FILE* fichier,MLV_Image *image){
 
    int byte[8] = {0};

 if (root != NULL){

    if (root->NO == NULL){
        /*Conversion d'une couleur en binaire dans le tableau byte[]*/
    	Converttobinary(root->color.red , byte);
        /*Écriture en sortie*/
        fprintf(fichier, "1(%d%d%d%d%d%d%d%d)", byte[0],byte[1],byte[2], byte[3], byte[4], byte[5], byte[6], byte[7]);
        Converttobinary(root->color.green , byte);
        fprintf(fichier, "(%d%d%d%d%d%d%d%d)", byte[0],byte[1],byte[2], byte[3], byte[4], byte[5], byte[6], byte[7]);
        Converttobinary(root->color.blue , byte);
        fprintf(fichier, "(%d%d%d%d%d%d%d%d)", byte[0],byte[1],byte[2], byte[3], byte[4], byte[5], byte[6], byte[7]);
        Converttobinary(root->color.alpha , byte);
        fprintf(fichier, "(%d%d%d%d%d%d%d%d)", byte[0],byte[1],byte[2], byte[3], byte[4], byte[5], byte[6], byte[7]);
        return ;
    }else{
        Converttobinary(root->color.red , byte);
        fprintf(fichier, "0(%d%d%d%d%d%d%d%d)", byte[0],byte[1],byte[2], byte[3], byte[4], byte[5], byte[6], byte[7]);
        Converttobinary(root->color.green , byte);
        fprintf(fichier, "(%d%d%d%d%d%d%d%d)", byte[0],byte[1],byte[2], byte[3], byte[4], byte[5], byte[6], byte[7]);
        Converttobinary(root->color.blue , byte);
        fprintf(fichier, "(%d%d%d%d%d%d%d%d)", byte[0],byte[1],byte[2], byte[3], byte[4], byte[5], byte[6], byte[7]);
        Converttobinary(root->color.alpha , byte);
        fprintf(fichier, "(%d%d%d%d%d%d%d%d)", byte[0],byte[1],byte[2], byte[3], byte[4], byte[5], byte[6], byte[7]);

        createFile(root->NO, fichier,image);
	    createFile(root->NE, fichier,image);
	    createFile(root->SE, fichier,image);
	    createFile(root->SO, fichier,image);

    }

    }

}

void createFile_BW(Tree root,FILE *fichier,MLV_Image *image){

	Color color;
    color = root->color;

if (root != NULL){
    if (root->NO == NULL){
        /*On appelle la fonction MLV_rgba pour avoir un entier sur 32 bits pour pouvoir comparer avec un MLV_Color*/
    	if (MLV_rgba(color.red,color.green,color.blue,color.alpha) == MLV_COLOR_WHITE){
    		fprintf(fichier, "1(0)");
    	}

    	if (MLV_rgba(color.red,color.green,color.blue,color.alpha) == MLV_COLOR_BLACK){
    		fprintf(fichier, "1(1)");
    	}

        return ;
    }else{
    	if (MLV_rgba(color.red,color.green,color.blue,color.alpha) == MLV_COLOR_WHITE){
    		fprintf(fichier, "0(0)");
    	}

    	if (MLV_rgba(color.red,color.green,color.blue,color.alpha) == MLV_COLOR_BLACK){
    		fprintf(fichier, "0(1)");
    	}

    createFile_BW(root->NO, fichier,image);
    createFile_BW(root->NE, fichier,image);
    createFile_BW(root->SE, fichier,image);
    createFile_BW(root->SO, fichier,image);

    }
}
}
