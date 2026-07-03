/*
問題設定
アプリケーションが実行したタスク履歴を、双方向連結リストを用いて管理するシステムを構築する。
メモリを節約するために、履歴バッファに保存できる最大件数はMAX_CACHE=4とする。
この履歴システムは以下のルールに従って動作する。
1. 新しいタスクが実行されるか、既存タスクが再アクセスされると、そのタスクノードはリストの最前(head)に移動し、アクセス回数(access_count)が１加算される。
2. 既存タスクノードを最前に移動させる際に、ポインタの繋ぎ変えのみで移動を実現し、実行時間をリストの長さに比例させないO(1)で処理する。
3. 履歴バッファの件数が最大値４を超えた場合、最も古くアクセスされていない末尾(tail)のタスクノードを削除し、メモリを開放する。*/

#include <stdlib.h>
#include <stdio.h>

#define MAX_CACHE 4

typedef struct task_node{
	int task_id;
	int access_count;
	struct task_node *prev;
	struct task_node *next;
}TASK;


TASK *head = NULL;
TASK *tail = NULL;
int cache_size = 0;


/*履歴を先頭から順に再帰的に表示する関数*/
void show_history_rec(TASK *cr){
	if(cr == NULL){
		return;
	}
	printf("Task ID: %d, Access Count: %d\n", cr -> task_id, cr -> access_count);
	show_history_rec(cr -> next);
}


void move_to_head(TASK *node){
	if(node == head){
		return;
	}
	//ノードを現在の位置から切り離し、切り離したノードをリストの先頭に挿入する
	if(node == tail){
		tail = node -> prev;
		tail -> next = NULL;
		head -> prev = node;
		node -> next = head;
		head = node;
	}else{
		TASK *node_next = node -> next;
		node -> next = head;
		head -> prev = node;
		head = node;
		node = node -> prev;
		node -> next = node_next;
		node_next -> prev = node;
	}
}

void evict_tail(void){
	if(tail == NULL){
		return;
	}
	TASK *temp = tail;
	if(tail -> prev != NULL){
		tail = tail -> prev;
		tail -> next = NULL;
		free(temp);
		cache_size--;
	}else{
		head = NULL;
		tail = NULL;
	}
}

void access_task(int id){
	TASK *cr = head;

	while(cr != NULL){
		if(cr -> task_id == id){
			cr -> access_count++;
			move_to_head(cr);
			return;
		}
		cr = cr -> next;
	}
	if(cache_size >= MAX_CACHE){
		evict_tail();
	}

	TASK *new_node = (TASK *)malloc(sizeof(TASK));
	new_node -> task_id = id;
	new_node -> access_count = 1;
	new_node -> prev = NULL;
	new_node -> next = head;

	if(head == NULL){
		head = new_node;
		tail = new_node;
	}else{
		head -> prev = new_node;
		head = new_node;
	}
	cache_size++;
}

void remove_inactive_tasks(void){
	TASK *cr = head;
	TASK *temp;

	while(cr != NULL){
		if (cr -> access_count <= 1){
			cache_size--;
			if(cr == head){
				if(head == tail){
					tail = NULL;
					head = NULL;
					free(cr);
				}else{
					head = head -> next;
					head -> prev = NULL;
					free(cr);
					cr = head;
				}	
			}else if(cr == tail){
				if(tail == head){
					tail = NULL;
					head = NULL;
					free(cr);
				}else{
					tail = tail -> prev;
					tail -> next = NULL;
					free(cr);
					cr = tail;
				}
			}else{
				temp = cr -> prev;
				cr = cr -> next;
				free(cr -> prev);
				cr -> prev = temp;
				temp -> next = cr;
			}
		}else{
			cr = cr -> next;
		}
	}
}




