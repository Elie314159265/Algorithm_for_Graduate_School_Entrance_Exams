#include <stdio.h>
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

void insert_before(double target_val, double new_val){
	struct dnode *curr = head;
	while (curr != NULL){
		if (curr -> value == target_val){
			break;
		}
		curr = curr -> next;
	}
	if (curr == NULL){
		return;
	}
	struct dnode *new_node = (struct dnode*)malloc(sizeof(struct dnode));
	new_node -> value = new_val;
	if (curr == head){
		head = new_node;

		curr -> prev = new_node;
		new_node -> next = curr;
		new_node -> prev = NULL;
	}else{
		new_node -> value = new_val;
		new_node -> next = curr;
		new_node -> prev = curr -> prev;
		curr -> prev -> next = new_node;
		curr -> prev = new_node;
	}
}

void reverse_list(void){
	if (head == NULL || head -> next == NULL) return;
	struct dnode *curr = head;
	struct dnode *temp = NULL;

	while (curr != NULL){
		temp = curr -> prev;
		curr -> prev = curr -> next;
		curr -> next = temp;

		curr = curr -> prev;
	}
	temp = head;
	head = tail;
	tail = temp;
}
		

void print_dlist(void){
	struct dnode *curr = head;
	printf("現在のリスト");
	if(curr == NULL){
		printf("空\n");
	}
	while(curr != NULL){
		printf("|%5.2f|", curr -> value);
		curr = curr -> next;
	}
	printf("\n");
}



int main(void) {
    printf("=== 1. 初期データセット (先頭に追加) ===\n");
    insert_head(30.0);
    insert_head(20.0);
    insert_head(10.0);
    print_dlist();
    /* 期待値: [ 10.00] [ 20.00] [ 30.00] */

    printf("\n=== 2. insert_before() のテスト ===\n");
    /* 20.0 の前に 15.0 を追加 (途中の挿入) */
    insert_before(20.0, 15.0);
    print_dlist();
    /* 期待値: [ 10.00] [ 15.00] [ 20.00] [ 30.00] */

    /* 10.0 の前に 5.0 を追加 (先頭の挿入のテスト) */
    insert_before(10.0, 5.0);
    print_dlist();
    /* 期待値: [  5.00] [ 10.00] [ 15.00] [ 20.00] [ 30.00] */

    printf("\n=== 3. reverse_list() のテスト ===\n");
    reverse_list();
    print_dlist();
    /* 期待値: [ 30.00] [ 20.00] [ 15.00] [ 10.00] [  5.00] */

    printf("\n=== 4. delete_node() のテスト ===\n");
    /* この時点で head は 30.0 のノードを指している */
    struct dnode *target = head->next; /* target は 20.0 のノード */
    printf("削除対象: %5.2f\n", target->value);

    delete_node(target);
    target = NULL; /* 呼び出し側でのダングリングポインタ対策 */
    print_dlist();
    /* 期待値: [ 30.00] [ 15.00] [ 10.00] [  5.00] */

    return 0;
}
