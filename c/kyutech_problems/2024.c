#include <stdio.h>
#include <stdlib.h>

struct list {
	int val;
	struct list *next;
};

struct list *head;

int maxdata(void){
	struct list *p;
	int max = 0;
	for (p = head; p != NULL; p = p -> next){
		if(p -> val > max){
			max = p -> val;
		}
	}

	return max;
}

void append(struct list *p, int n){
	struct list *new;
	new = (struct list*)malloc(sizeof(struct list));
	new -> val = n;
	new -> next = p -> next;
	p -> next = new;
}

void delete(struct list *p){
	struct list *q;
	if(head == p){
		head = p -> next;
		free(p);
	}else{
		q = head;
		while(q -> next != p){
			q = q -> next;
		}
		q -> next = p -> next;
		free(p);
		// pはグローバル変数ならダングリングポインタを防ぐために
		// p = NULL;
	}
}

/*問４ O(n)である関数は(b)delete関数、(c)insert関数
  理由は不要とのことだが理解力確認のため記述しておく。(a),(d)はノードのポインタp
  が与えられるとその直後のp -> next を参照すればよいのでO(1)だが、(b),(c)は
  ノードのポインタpが与えられると、その直前のノードのポインタを探す必要がある。
  今回は単方向リストよりheadから順番に辿る必要があり、この違いによって実行時間
  に違いが出ている。*/

/*問５ list2はいわゆる双方向リストであり、あるノードのポインタpから次のノードの
  ポインタp -> nextだけでなく前のノードのポインタp -> prevを辿ることができる。
*/
// struct list2 {
//     int val;
//     struct list2 *next;
//     struct list2 *prev;
