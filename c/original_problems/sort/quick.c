#include <stdio.h>
#include <stdlib.h>

struct list {
    int val;
    struct list *next;
};

struct list *head = NULL;

/* === リストの内容を表示する関数 === */
void print_list(const char *msg) {
    struct list *p;
    printf("%s: ", msg);
    if (head == NULL) printf("(空)");
    for (p = head; p != NULL; p = p->next) {
        printf("[%d] ", p->val);
    }
    printf("\n");
}

/* === テスト用にリストの先頭にデータを追加する関数 === */
void push_list(int val) {
    struct list *new_node = (struct list *)malloc(sizeof(struct list));
    new_node->val = val;
    new_node->next = head;
    head = new_node;
}

/* === リストの全メモリを解放する関数 === */
void free_list(void) {
    struct list *p = head;
    while (p != NULL) {
        struct list *temp = p;
        p = p->next;
        free(temp);
    }
    head = NULL;
}

void partition(struct list *head, int pivot_val, struct list **less_head, struct list **greater_head){
	*less_head = NULL;
	*greater_head = NULL;

	struct list *curr = head;

	while(curr != NULL){
		struct list *next_node = curr -> next;
		if(curr -> val < pivot_val){
			curr -> next = *less_head;
			*less_head = curr;
		}else{
			curr -> next = *greater_head;
			*greater_head = curr;
		}
		curr = next_node;
	}
}

void quick_sort(struct list **head_ref){
	if (*head_ref == NULL || (*head_ref) -> next == NULL){
		return;
	}
	struct list *pivot_node = *head_ref;
	struct list *rest = pivot_node -> next;
	pivot_node -> next = NULL;
	struct list *less = NULL;
	struct list *greater = NULL;

	partition(rest, pivot_node -> val, &less, &greater);

	quick_sort(&less);
	quick_sort(&greater);

	if(less == NULL){
		*head_ref = pivot_node;
		pivot_node -> next = greater;
	}else{
		struct list *temp = less;
		*head_ref = less;
		while(temp -> next != NULL){
			temp = temp -> next;
		}
		temp -> next = pivot_node;
		pivot_node -> next = greater;
	}
}


int main(void) {
    printf("=== クイックソート(ポインタ操作)のテスト ===\n");

    /* データの追加 (LIFOなので、後に入れたものが先頭にくる) */
    push_list(10);
    push_list(4);
    push_list(7);
    push_list(2);
    push_list(6);
    push_list(9);
    push_list(1);
    push_list(5);
    push_list(8);
    push_list(3);

    print_list("ソート前");
    /* 期待値: [1] [2] [3] [4]  [5] [6] [7] [8]  */

    /* 大元のグローバル変数 head の「住所(&)」を渡してソート実行 */
    quick_sort(&head);

    print_list("ソート後");
    /* 期待値: [4] [6] [1] [8] [3] [5] [7] [2]   */

    free_list();

    return 0;
}
