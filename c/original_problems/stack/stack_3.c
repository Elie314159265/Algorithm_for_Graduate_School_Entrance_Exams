#include <stdio.h>
#include <stdlib.h>

struct node{
	double value;
	struct node *next;
};

struct node *stack = NULL;

void print_stack(void){
	struct node *nodep = stack;
	while(nodep != NULL){
		printf("|%5.2f|", nodep -> value);
		nodep = nodep -> next;
	}
	printf("\n");
}

int stack_depth(){
	double depth = 0;
	struct node *nodep = stack;
	while(nodep != NULL){
		depth++;
		nodep = nodep -> next;
	}
	return depth;
}

void push(double top_value){
	struct node *nodep = (struct node*)malloc(sizeof(struct node));
	nodep -> value = top_value;
	nodep -> next = stack;
	stack = nodep;
}

double pop(void){
	if(stack_depth() > 0){
		double val = stack -> value;
		struct node *next_node = stack -> next;
		free(stack);
		stack = next_node;
		return val;
	}
	return 0.0;
}
void clear_stack(void){
	while(stack != NULL){
		pop();
	}
}



void insert_bottom(double insert_value){
	struct node *nodep = (struct node*)malloc(sizeof(struct node));
	nodep -> value = insert_value;
	nodep -> next = NULL;
	if (stack == NULL){
		stack = nodep;
	}else{
		struct node *temp = stack;
		while(temp -> next != NULL){
			temp = temp -> next;
		}
		temp -> next = nodep;
	}
}

void remove_bottom(void){
	if(stack == NULL) return;

	if(stack -> next == NULL){
		free(stack);
		stack = NULL;
	}else{
		struct node *temp = stack;
		while (temp -> next -> next != NULL){
			temp = temp -> next;
		}
		free(temp -> next);
		temp -> next = NULL;
	}
}

void reverse_stack(void){
	struct node *prev = NULL;
	struct node *current = stack;
	struct node *next = NULL;

	while (current != NULL) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	stack = prev;
}

void keep_top(int n){
	if (n <= 0){
		clear_stack();
		return;
	}
	if(stack_depth() <= n) return;

	struct node *temp = stack;

	for (int i=1; i < n; i++){
		temp = temp -> next;
	}

	struct node* target = temp->next;
	temp->next = NULL;
	while (target != NULL) {
        	struct node* next_node = target->next;
		free(target);
        	target = next_node;
        }

}


void move_max_to_top(void){
	if(stack_depth() < 2){
	       return;
	}
	struct node *prev = stack;
	struct node *curr = stack -> next;
        struct node *max_prev = NULL;
	struct node *max_node = stack;

	while(curr != NULL){
		if(curr -> value > max_node -> value){
			max_node = curr;
			max_prev = prev;
		}
		prev = curr;
		curr = curr -> next;
	}
	
	if(max_prev == NULL){
		return;
	}
	max_prev -> next = max_node -> next;
	max_node -> next = stack;
	stack = max_node;
}


int main(void) {
    printf("=== 初期データセット（10.0, 20.0, 30.0 をPush） ===\n");
    push(10.0);
    push(20.0);
    push(30.0);
    print_stack(); /* 期待値: |30.00| |20.00| |10.00| */

    printf("\n=== 問1: insert_bottom(40.0) のテスト ===\n");
    insert_bottom(40.0);
    print_stack(); /* 期待値: |30.00| |20.00| |10.00| |40.00| */

    printf("\n=== 問2: remove_bottom() のテスト ===\n");
    remove_bottom();
    print_stack(); /* 期待値: |30.00| |20.00| |10.00| （40.0が消える）*/

    printf("\n=== 問3: reverse_stack() のテスト ===\n");
    reverse_stack();
    print_stack(); /* 期待値: |10.00| |20.00| |30.00| （順番が反転）*/

    printf("\n=== 問5: move_max_to_top() のテスト ===\n");
    /* 現在の最大値は 30.0（一番底にある） */
    move_max_to_top();
    print_stack(); /* 期待値: |30.00| |10.00| |20.00| （30.0が先頭に移動）*/

    printf("\n=== 問4: keep_top(2) のテスト ===\n");
    keep_top(2);
    print_stack(); /* 期待値: |30.00| |10.00| （上から2つだけ残る）*/

    return 0;
}
