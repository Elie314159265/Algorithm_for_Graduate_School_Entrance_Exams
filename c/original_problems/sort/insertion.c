#include <stdio.h>
#include <stdlib.h>

struct list {
	int val;
	struct list *next;
};



struct list *head = NULL;

void print_list(const char *msg){
	struct list *p;
	printf("%s: ", msg);
	if(head == NULL){
		printf("空です\n");
	}
	for (p = head; p != NULL; p = p -> next){
		printf("|%d|", p -> val);
	}
	printf("\n");
}

void push_list(int val){
	struct list *new_node = (struct list *)malloc(sizeof(struct list));
	new_node -> val = val;
	new_node -> next = head;
	head = new_node;
}

void free_list(void){
	struct list *p = head;
	struct list *temp = p;
	while(p != NULL){
		temp = p;
		p = p -> next;
		free(temp);
	}
	head = NULL;
}

void insertion_sort_pointers(void){
	if(head == NULL || head -> next == NULL){
		return;
	}

	struct list *sorted_head = NULL;
	struct list *curr = head;

	while (curr != NULL){
		struct list *next_node = curr -> next;

		if(sorted_head == NULL || curr -> val < sorted_head -> val){
			curr -> next = sorted_head;
			sorted_head = curr;
		}else{
			struct list *search = sorted_head;
			while(search -> next != NULL && search -> next -> val <= curr -> val){
				search = search -> next;
			}
			curr -> next = search -> next;
			search -> next = curr;
		}
		curr = next_node;
	}
	head = sorted_head;
}

int main(void) {
    printf("=== 挿入ソート(ポインタ操作)のテスト ===\n");

    /* データの追加 (LIFOなので、後に入れたものが先頭にくる) */
    push_list(10);
    push_list(4);
    push_list(7);
    push_list(2);
    push_list(6);

    print_list("ソート前");
    /* 期待値: [2] [3] [1] [4]  */

    insertion_sort_pointers();

    print_list("ソート後");
    /* 期待値: [3] [4] [2] [1]  */

    free_list();

    return 0;
}
