/*
【演習問題】基礎：キューの実装

以下のプログラムは、node 構造体を用いてキューを実装したものである。外部変数 head はキューの先頭（出口）を指し、tail はキューの末尾（入口）を指す。 空欄 A と B を埋めて、キューの基本操作関数を完成させよ。

問1（Enqueue操作） 関数 enqueue は、キューの末尾（tail 側）に新しい実数データを追加する関数である。スタックが空の場合とそうでない場合でポインタの繋ぎ方が変わることに注意。

問2（Dequeue操作） 関数 dequeue は、キューの先頭（head 側）からデータを取り出し、そのノードのメモリを解放する関数である（これまでの pop 関数と同じ働き）。ただし、**「最後の1個を取り出してキューが完全に空になったとき」**の tail ポインタの扱いに注意。
*/

#include <stdio.h>
#include <stdlib.h>

struct node{
	double value;
	struct node *next;
};

struct node *head = NULL;
struct node *tail = NULL;

void enqueue(double value){
	struct node *new_node = (struct node*)malloc(sizeof(struct node));
	new_node -> value = value;
	new_node -> next = NULL;

	if(head == NULL){
		head = new_node;
		tail = new_node;
	}else{
		tail -> next = new_node;
		tail = tail -> next;
	}
}

double dequeue(void){
	if (head == NULL) {
		return 0.0;
	}

	double val = head -> value;
	struct node *temp = head;

	temp = head -> next;
	free(head);
	head = temp;

	return val;
}


