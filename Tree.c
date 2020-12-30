#include "Tree.h"

Data *allocateData(int x, int y, int width , int height){
	Data *tmp = malloc(sizeof(Data));
		tmp->pos_image_x = x;
		tmp->pos_image_y = y;
		tmp->width_x = width;
		tmp->height_y = height;

	return tmp;
}

Node *allocateNode(Binary_color Color, Data *data){
    Node *tmp = malloc(sizeof(Node));
    if(tmp != NULL){
    	tmp -> coord = data;
        tmp -> colo = Color;
        tmp -> NO = NULL;
        tmp -> NE = NULL;
        tmp -> SE = NULL;
        tmp -> SO = NULL;
    }
    return tmp;
}

void subdivise_nodes(Tree root){
	int width = root->coord->width_x/2;
	int height = root->coord->height_y/2;
	Data *data_NO = allocateData(root->coord->pos_image_x,root->coord->pos_image_y,width,height);
	Data *data_SO = allocateData(root->coord->pos_image_x,height/2,width,height);
	Data *data_NE = allocateData(width/2,root->coord->pos_image_y,width,height);
	Data *data_SE = allocateData(width/2,height/2,width,height);

	Node *node1 = allocateNode(0,data_NO);
	Node *node2 = allocateNode(0,data_NE);
	Node *node3 = allocateNode(0,data_SO);
	Node *node4 = allocateNode(0,data_SE);

	root->NO = node1;
	root->NE = node2;
	root->SO = node3;
	root->SE = node4;

	printf("[%d,%d]\n",data_NO->pos_image_x,data_NO->pos_image_y);
	
	printf("[%d,%d]\n",data_NE->pos_image_x,data_NE->pos_image_y);

	printf("[%d,%d]\n",data_SO->pos_image_x,data_SO->pos_image_y);

	printf("[%d,%d]\n",data_SE->pos_image_x,data_SE->pos_image_y);

}

void browse_tree(Tree root, MLV_Image *image){
	//display_node(root->NO,image);
	//display_node(root->NE,image);
	display_node(root->SO,image);
	//display_node(root->SE,image);

}
