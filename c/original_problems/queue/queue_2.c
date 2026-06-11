/*
問１．データ転送 関数 transfer_to_stack は、キューに溜まっているすべてのデータを取り出し、そのまま順番にスタックに積む関数である。ポインタは直接操作せず、既存の関数のみを用いて実装せよ。

問２．LIFO と FIFO の融合による「反転」 関数 reverse_queue は、現在キューに入っているデータの並び順を**完全に逆転（リバース）**させる関数である。ポインタの直接的な繋ぎ変えは行わず、「スタック（後入れ先出し）」の性質を一時的な保管庫としてうまく利用することで関数を実装せよ。

問３．キューからの特定要素の直接削除 関数 remove_negative_from_queue は、キューの中に含まれる負の数（0.0未満）のノードをすべて削除（free）し、残りの要素でキューを正しく再構築する関数である。今回は関数を呼び出さず、ポインタ操作のみで実現せよ。

*/



#include <stdio.h>
#include <stdlib.h>

struct node{
	double value;
	struct node *next;
};


struct node{
	double value;
	struct node *next;
}

struct node *head = NULL, *tail = NULL;

void enqueue(double value){
	struct node *new_node = (struct node*)malloc(sizeof(struct node));
	new_node -> value = value;
	new_node -> next = NULL;

	if (head == NULL){
		head = new_node;
		tail = new_node;
	}else{
		tail -> next = new_node;
		tail = tail -> next;
	}
}

double dequeue(void) {
	if(head == NULL){
		return 0.0;
	}

	double val = head -> value;
	struct node *temp = head;

	head = head -> next;
	free(temp);

	if(head == NULL){
		tail = NULL;
	}

	return val;
}

void print_queue(void){
	struct node *nodep = head;
	printf("現在のキュー\n");
	if (nodep == NULL){
		printf("空\n");
	}
	while (nodep != NULL){
		printf("|%5.2f|", nodep -> value);
		nodep = nodep -> next;
	}
	printf("\n");
}

void transfer_to_stack(void){
	while(head != NULL){
		push(dequeue());
	}
}

void reverse_queue(void){
	while(head != NULL){
		push(dequeue());
	}
	while(stack != NULL){
		enqueue(pop());
	}
}

void remove_negative_from_queue(void){
	struct node *curr = head;
	struct node *prev = NULL;

	while(curr != NULL){
		if(curr -> value < 0.0){
			prev -> next = curr -> next;
			free(curr);
			curr = prev -> next;
		}else {
			prev = curr;
			curr = curr -> next;
		}
	}
}



