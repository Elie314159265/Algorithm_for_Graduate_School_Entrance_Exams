#include <stdlib.h>
#include <stdio.h>

typedef struct alist{
	int sn;
	char ac;
	int freq;
	struct alist *prev;
	struct alist *next;
} ALIST;

ALIST *head = NULL, *tail = NULL;

// add_node関数は１文字の引数であり、線形リストにその文字のノードを追加していく。
// この関数は選択した文字の数だけ呼び出される。例えば１０文字選択した場合はそれぞれの
//  文字を引数として合計１０回呼び出される。その後各ノードの頻度とtailが設定される
void add_node(char c){
	ALIST *cr, *cr_prev;
	if(head == NULL){
		head = (ALIST *)malloc(sizeof(ALIST));
		head -> ac = c;
		head -> sn = 0;
		head -> prev = NULL;
		head -> next = NULL;
	}else{
		cr = head;
		while(1){
			if(cr -> next == NULL){
				break;
			}else{
				cr = cr -> next;
			}
		}
		cr_prev = cr;
		cr = cr -> next;
		cr -> ac = c;
		cr -> sn = cr_prev -> sn + 1;
		cr -> prev = cr_prev;
		cr -> next = NULL;
	}
}

// show_list_rec関数はheadを引数として受け取り、線形リストの先頭から順に各ノードの
// ac, freqの値を再帰的に出力する。
void show_list_rec(ALIST *cr){
	if(cr == NULL){
		return;
	}
	printf("ac: %c, freq: %d\n",cr -> ac, cr -> freq);
	show_list_rec(cr -> next);
}

void rm_zero(){
	ALIST *cr, *temp;

	cr = head;
	while(1){
		if(cr -> freq == 0){
			if(cr -> prev == NULL){
				head = head -> next;
				if(head != NULL){
					head -> prev = NULL;
				}
				free(cr);
				cr = head;
			}else if(cr -> next == NULL){
				tail = tail -> prev;
				tail -> next = NULL;
				free(cr);
				cr = tail;
			}else{
				temp = cr -> next;
				cr = cr -> prev;
				free(cr -> next);
				temp -> prev = cr;
				cr -> next = temp;
			}
		}
		if(cr -> next == NULL){
			break;
		}else{
			cr = cr -> next;
		}
	}

	cr = head;
	int count = 0;
	tail = NULL;
	while(cr != NULL){
		cr -> sn = count;
		count++;
		tail = cr;
		cr = cr -> next;
}









