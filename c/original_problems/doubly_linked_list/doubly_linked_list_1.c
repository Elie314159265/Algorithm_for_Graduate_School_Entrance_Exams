#include <stdui.h>
#include <stdlib.h>

struct dnode{
	double value;
	struct dnode *next;
	struct dnode *prev;
};

struct dnode *head = NULL;
struct dnode *tail = NULL;


void insert_head(double value){
	struct dnode *new_node = (struct dnode*)malloc(sizeof(struct dnode));
	new_node -> value = value;

	new_node -> prev = NULL;
	new_node -> next = head;

	if(head == NULL){
		tail = new_node;
	}else{
		head -> prev = new_node;
	}
	head = new_node;
}

void delete_node(struct dnode *target){
	if (target == NULL)return;
	
	if(target -> prev != NULL){
		target -> prev -> next = target -> next;
	}else{
		head = target -> next;
	}

	if (target -> next != NULL){
		target -> next -> prev = target -> prev;
	}else{
		tail = target -> prev;
	}

	free(target);
}

		


