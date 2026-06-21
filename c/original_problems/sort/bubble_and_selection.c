#include <stdio.h>
#include <stdlib.h>

struct list{
	int val;
	struct list *next;
};

struct list *head = NULL;

void bubble_sort(void){
	if (head == NULL || head -> next == NULL){
		return;
	}
	int swapped;
	struct list *curr;

	do{
		swapped = 0;
		curr = head;
		while(curr -> next != NULL){
			if(curr -> val > curr -> next -> val){
				int temp = curr -> val;
				curr -> val = curr -> next -> val;
				curr -> next -> val = temp;

				swappwd = 1;
			}
			curr = curr -> next;
		}
	}while(swapped);
}

void selection_sort(void){
	if(head == NULL || head -> next == NULL){
		return;
	}

	struct list *curr = head;
	while(curr != NULL){
		struct list *min_node = curr;
		struct list *search = curr -> next;

		while(search != NULL){
			if(search -> val < min_node -> val){
				min_node = search;
			}
			search = search -> next;
		}
		if (min_node != curr){
			int temp = curr -> val;
			curr -> val = min_node -> val;
			min_node -> val = temp;
		}
		curr = curr -> next;
	}
}
