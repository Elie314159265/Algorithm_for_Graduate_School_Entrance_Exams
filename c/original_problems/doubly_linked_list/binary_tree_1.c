#include <stdio.h>
#include <stdlib.h>

#define MAX(x,y) (((x) > (y)) ? (x) : (y))


struct node {
	int val;
	struct node *left;
	struct node *right;
};

struct node *root = NULL;

// 値keyを受け取ってそれと一致するノードのポインタを返す関数
struct node *search(struct node *root, int key){
	if(root == NULL || root -> val == key){
		return root;
	}

	if(key < root -> val){
		return search(root -> left, key);
	}else{
		return search(root -> right, key);
	}
}

struct node *find_min(struct node *p){
	if(p == NULL){
		return NULL;
	}
	while(p -> left != NULL){
		p = p -> left;
	}
	return p;
}

struct node *insert(struct node *p, int value){
	if(p == NULL){
		struct node *new_node = (struct node *)malloc(sizeof(struct node));
		new_node -> val = value;
		new_node -> left = NULL;
		new_node -> right = NULL;
		return new_node;
	}
	if(value < p -> val){
		p -> left =  insert(p -> left, value);
	}
	else if(value > p -> val){
		p -> right = insert(p -> right, value);
	}
	return p;
}


// 指定した値のノードを削除する関数
struct node *delete_node(struct node *p, int value){
	if(p == NULL) return NULL;

	if(value < p -> val){
		p -> left = delete_node(p -> left, value);
	}else if(value > p -> val){
		p -> right = delete_node(p -> right, value);
	}else{
		// 削除対象ノードpを発見した場合
		if(p -> left == NULL){
			struct node *temp = p -> right;
			free(p);
			return temp;
		}else if(p -> right == NULL){
			struct node *temp = p -> left;
			free(p);
			return temp;
		}else{
			struct node *temp = find_min(p -> right);
			p -> val = temp -> val;
			p-> right = delete_node(p-> right, temp-> val);
		}
	}
	return p;
}


int tree_depth(struct node *p){
	if(p == NULL){
		return 0;
	}
	return 1 + MAX(tree_depth(p -> left), tree_depth(p -> right));
}

void print_inorder(struct node *p){
	if(p == NULL) return;
	print_inorder(p -> left);
	printf("[%d]", p -> val);
	print_inorder(p -> right);
}

void free_tree(struct node *p){
	if(p == NULL) return;
	free_tree(p -> left);
	free_tree(p -> right);
	free(p);

}


/* === テスト用メイン関数 === */
int main(void) {
    struct node *root = NULL;

    printf("=== 二分探索木 (BST) の総合テスト ===\n\n");

    /* 1. データの挿入 */
    printf("1. データを木に挿入します: 8, 3, 10, 1, 6, 14, 4, 7\n");
    root = insert(root, 8);
    root = insert(root, 3);
    root = insert(root, 10);
    root = insert(root, 1);
    root = insert(root, 6);
    root = insert(root, 14);
    root = insert(root, 4);
    root = insert(root, 7);

    /* 2. 通りがけ順出力 */
    printf("現在の木 (通りがけ順 / 期待値: 昇順に整列): ");
    print_inorder(root);
    printf("\n\n");

    /* 3. 深さの測定 */
    printf("2. 木の最大深さの測定 (期待値: 4): %d\n\n", tree_depth(root));

    /* 4. 探索テスト */
    printf("3. データの探索テスト\n");
    int target1 = 6;
    struct node *found = search(root, target1);
    if (found != NULL) {
        printf("  値 %d を発見しました！ (ノードのアドレス: %p)\n", target1, (void*)found);
    } else {
        printf("  値 %d は見つかりませんでした。\n", target1);
    }

    int target2 = 5; /* 存在しない値 */
    found = search(root, target2);
    if (found != NULL) {
        printf("  値 %d を発見しました！\n", target2);
    } else {
        printf("  値 %d は見つかりませんでした。(正常動作)\n", target2);
    }
    printf("\n");

    /* 5. 削除テスト */
    printf("4. データの削除テスト\n");

    /* ケース1: 葉ノード (子が0個) の削除 */
    printf("  [ケース1] 葉ノード '1' を削除します...\n");
    root = delete_node(root, 1);
    printf("  削除後の木: ");
    print_inorder(root);
    printf("\n");

    /* ケース2: 子が1個のノードの削除 */
    printf("  [ケース2] 子が1個のノード '14' を削除します...\n");
    root = delete_node(root, 14);
    printf("  削除後の木: ");
    print_inorder(root);
    printf("\n");

    /* ケース3: 子が2個のノードの削除 */
    printf("  [ケース3] 子が2個のノード '3' を削除します (右部分木の最小値 '4' が昇格するはず)...\n");
    root = delete_node(root, 3);
    printf("  削除後の木: ");
    print_inorder(root);
    printf("\n\n");

    /* 削除後の深さ再測定 */
    printf("現在の木の最大深さ (期待値: 3): %d\n\n", tree_depth(root));

    /* 6. メモリ解放 */
    printf("5. メモリを解放して終了します...\n");
    free_tree(root);
    root = NULL;
    printf("終了しました。\n");

    return 0;
}


