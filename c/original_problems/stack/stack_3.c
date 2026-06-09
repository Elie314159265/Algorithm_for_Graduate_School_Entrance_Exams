問1（難易度7）：スタックの底への挿入 関数 insert_bottom は、引数に与えられた実数をスタックの最上部ではなく、**「一番底（末尾）」**に挿入する関数である。空欄 A を埋めて関数を完成せよ。

問2（難易度8）：スタックの底の削除 関数 remove_bottom は、スタックの**「一番底（末尾）」の要素のみを削除（free）する**関数である。要素が1つしかない場合と、複数ある場合で処理が分岐する。空欄 B1 および B2 を埋めて関数を完成せよ。

問3（難易度9）：スタックの反転（Classic Pointer Puzzle） 関数 reverse_stack は、スタックに積まれているすべての要素の順番を逆にする関数である。push や pop、malloc は一切使用せず、すべてのノードの next ポインタの向きを逆転させることで実現せよ。空欄 C を埋めよ。

問4（難易度9）：指定位置でのリスト切断とメモリ解放 関数 keep_top_n は、引数 n を受け取り、スタックの上から n 個の要素だけを残し、それより下にある要素をすべて削除（free）する関数である。n が現在の深さ以上の場合は何もしない。空欄 D を埋めよ。（ヒント：リストを途中で断ち切り、切り落とした先のノード群を一つずつ free する必要があります）

問5（難易度10）：最大値ノードの引き抜きと先頭移動（最終ボス） 関数 move_max_to_top は、スタック内に存在する最大の数値を持つノードを探し出し、そのノードをスタックの最上部（先頭）に移動させる関数である。ポインタ操作のみで行うこと。なお、最大値がすでに先頭にある場合や、スタックの要素が1つ以下の場合は何もしない。空欄 E を埋めよ。



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
