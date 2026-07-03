#include <stdio.h>
#include <stdlib.h>

struct node {
	int val;
	struct node *left;
	struct node *right;
};

struct node *root = NULL;

// 値keyを受け取ってそれと一致するノードのポインタを返す関数
struct node *search(struct node *root, int key){
	if(root == NULL || root -> val == key){
		return root;
	}

	if(key < root -> val){
		return search(root -> left, key);
	}else{
		return search(root -> right, key);
	}
}

struct node *find_min(struct node *p){
	if(p == NULL){
		return NULL;
	}
	while(p -> left != NULL){
		p = p -> left;
	}
	return p;
}

struct node *insert(struct node *p, int value){
	if(p == NULL){
		struct node *new_node = (struct node *)malloc(sizeof(struct node));
		new_node -> val = value;
		new_node -> left = NULL;
		new_node -> right = NULL;
		return new_node;
	}
	if(value < p -> val){
		p -> left =  insert(p -> left, value);
	}
	else if(value > p -> val){
		p -> right = insert(p -> right);
	}
	return p;
}


