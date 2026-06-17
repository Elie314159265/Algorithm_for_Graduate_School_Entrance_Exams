/*バッチ処理エンジン
  本課題では外部から大量に送られてくる数値データや計算命令を一旦双方向リストに
  蓄積・編集し、準備が整った段階で計算エンジン(スタックベースの単方向リスト)に
  送り込んでバッチ的に処理を実行するシステムを実装する。*/

#include <stdio.h>
#include <stdlib.h>

// 構造体定義. nodeは単方向リスト(スタック), dnodeは双方向リスト
struct node {
	double value;
	struct node *next;
};

struct dnode {
	double value;
	struct dnode *prev;
	struct dnode *next;
};




// stackはスタックの一番上のノードを指す.
// headはキューの先頭ノードを表す.
// tailはキューの末尾ノードを表す.
struct node *stack = NULL;
struct dnode *head = NULL;
struct dnode *tail = NULL;

void print_stack(void){
	struct node *temp_node = stack;
	if(temp_node == NULL){
		printf("スタックは空です\n");
		return;
	}
	while (temp_node != NULL){
		printf("|%5.2f|", temp_node -> value);
		temp_node = temp_node -> next;
	}
	printf("\n");
}

// 数値をスタックに積む
void push(double top_value){
	struct node *top_node = (struct node*)malloc(sizeof(struct node));
	top_node -> value = top_value;
	if(stack == NULL){
		top_node -> next = NULL;
		stack = top_node;
	}else{
		top_node -> next = stack;
		stack = top_node;
	}
}

// スタックから数値を取り出す。 
double pop(void){
	double top_value;
	struct node *temp_node = stack;
	if(stack == NULL){
		return 0.0;
	}else{
		top_value = stack -> value;
		stack = stack -> next;
		// ダングリングポインタを防ぐため外部変数であるstackのノードをfree()でメモリを解放後、NULLを代入する。
		free(temp_node);
		temp_node = NULL;
		return top_value;
	}
}

// スタックの上から2番目の数値から、最上部の数値を引き、結果をスタックに積む。
void subtract(void){
	if(stack == NULL || stack -> next == NULL){
		printf("スタックの要素数が2より小さいです。\n");
		return;
	}
	double first_value, second_value;
	first_value = pop();
	second_value = pop();
	push(second_value - first_value);
}

// スタックの最上部の数値と、上から2番目の数値を入れ替える(ポインタ操作のみで実装)
void swap(void){
	if(stack == NULL || stack -> next == NULL){
		printf("スタックの要素数が2より小さいです。\n");
		return;
	}
	struct node *temp_node = stack -> next;
	stack -> next = temp_node -> next;
	temp_node -> next = stack;
	stack = temp_node;
}



// キューの末尾にデータを追加する
void enqueue_task(double value){
	struct dnode *new_dnode = (struct dnode*)malloc(sizeof(struct dnode));
	new_dnode -> value = value;
	new_dnode -> prev = NULL;
	if(tail == NULL){
		new_dnode -> next = NULL;
		head = new_dnode;
		tail = new_dnode;
	}else{
		new_dnode -> next = tail;
		tail -> prev = new_dnode;
		tail = new_dnode;
	}
}

// 要件にdequeueは無いがexecute_all実装にあたって、必要と判断したため実装
// キューの先頭からデータを取り出す。
double dequeue_task(void){
	if(head == NULL){
		return 0.0;
	}else{
		double value = head -> value;
		struct dnode *new_head = head -> prev;
		free(head);
		head = new_head;
		if(head == NULL){
			tail = NULL;
		}else{
			head -> next = NULL;
		}
		return value;
	}
}

// 現在のキュー内の最大の数値を返す。
double max_task_value(void){
	if(head == NULL || tail == NULL){
		return 0.0;
	}
	double max_value = -(2 << 28);
	struct dnode *temp_dnode = tail;
	while(temp_dnode != NULL){
		if(temp_dnode -> value > max_value){
			max_value = temp_dnode -> value;
		}
		temp_dnode = temp_dnode -> next;
	}
	return max_value;
}

// 特定ノードpをキューから直接削除する
void delete_task(struct dnode *p){
	if(p == NULL){
		printf("削除するノードがNULLです\n");
		return;
	}else if(p == tail && p == head){
		free(p);
		head = NULL;
		tail = NULL;
	}else if(p == tail){
		tail = p -> next;
		tail -> prev = NULL;
		free(p);
	}else if(p == head){
		head = p -> prev;
		head -> next = NULL;
		free(p);
	}else{
		p -> next -> prev = p -> prev;
		p -> prev -> next = p -> next;
		free(p);
	}
}

// 特定ノードpの直前に新たなノードを追加する
void insert_task_before(struct dnode *p, double value){
	if(p == NULL){
		printf("insert_task_beforeにおいて渡されたノードpはNULLです。");
		return;
	}
	struct dnode *new_dnode = (struct dnode*)malloc(sizeof(struct dnode));
	new_dnode -> value = value;
	new_dnode -> prev = p;
	new_dnode -> next = p -> next;
	if(p -> next == NULL){
		head = new_dnode;
	}else{
		p -> next -> prev = new_dnode;
	}
	p -> next = new_dnode;
}

// デバッグ用にキューの中身を出力する関数を実装
void print_queue(void){
	struct dnode *temp_dnode = head;
	if(temp_dnode == NULL){
		printf("キューは空です。\n");
		return;
	}
	while(temp_dnode != NULL){
		printf("|%5.2f|", temp_dnode -> value);
		temp_dnode = temp_dnode -> prev;
	}
	printf("\n");
}

void execute_all(void){
	while(head != NULL){
		double temp_value = dequeue_task();
		if(temp_value == -999.0){
			subtract();
		}else if(temp_value == -888.0){
			swap();
		}else{
			push(temp_value);
		}
	}
}


		

int main(void) {
    /* 1. キューにタスク（数値と命令）を登録する */
    enqueue_task(10.0);
    enqueue_task(5.0);
    enqueue_task(20.0);
    enqueue_task(-999.0); /* subtract命令 */
    enqueue_task(100.0);
    print_queue();

    /* 2. キューの編集（双方向リストのO(1)操作の威力を発揮） */
    /* キューの先頭(10.0)の次のノード(5.0)のポインタを取得 */
    struct dnode *target = head->prev; 
    
    /* 5.0は間違いだったので、直接削除する */
    delete_task(target); 
    
    /* 代わりに20.0の直前に 2.0 を割り込み挿入する */
    /* (現在の先頭10.0の次が20.0になっているので、そこをターゲットにする) */
    insert_task_before(head->prev, 2.0); 

    /* さらに 100.0 の手前に -888.0 (swap命令) を挿入する */
    insert_task_before(tail, -888.0);

    /* 3. 最大値の確認 */
    printf("実行前のキュー内最大値: %.2f\n", max_task_value()); 
    /* 期待値: 100.0 */

    /* 4. 一斉実行 */
    printf("=== バッチ処理実行 ===\n");
    execute_all();

    /* 5. 最終結果の確認 */
    print_stack(); 
    /* 
       期待されるスタックの動き:
       push(10.0) -> push(2.0) -> push(20.0) -> subtract(2.0 - 20.0 = -18.0) 
       -> swap(-18.0 と 10.0 を入れ替え) -> push(100.0)
       最終スタック: |100.00| |-18.00| | 10.00|
    */

    return 0;
}

