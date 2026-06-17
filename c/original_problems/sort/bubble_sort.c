#include <stdio.h>
#include <stdlib.h>

struct node {
	double value;
	struct node *next;
}

struct node *head = NULL;


void bubble_sort_values(void){
	if (head == NULL || head -> next == NULL){
		return;
	}

	int swapped;
	struct node *curr;

	do{
		swapped = false;
		curr = head;

		while(curr -> next != NULL){
			if(curr -> value > curr -> next -> value){
				swapped = curr -> value;
				curr -> value = curr -> next -> value;
				curr -> next -> value = swapped;
			}
			curr = curr -> next;
		}
	}while(swapped);
}

void insertion_sort_pointers(void){
	if (head == NULL || head -> next == NULL) return;
	struct node *sorted_head = NULL;
	struct node *curr = head;

	while (curr != NULL){
		struct node *next_node = curr -> next;


