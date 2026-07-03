#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
	int data;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;


// low以上high以下のノードの値の合計値を計算する
int sum_range(TreeNode *node, int low, int high){
	if(node == NULL){
		return 0;
	}

	int sum = 0;

	if(node -> data >= low && node -> data <= high){
		sum += node -> data;
	}
	if(node -> data > low){
		sum += sum_range(node -> left, low, high);
	}
	if(node -> data < high){
		sum += sum_range(node -> right, low, high);
	}
	return sum;
}

// 指定された2つの値の最も近い共通の先祖となるノードのポインタを返す。
TreeNode *lowest_common_ancestor(TreeNode *root, int n1, int n2){
	if(root == NULL){
		return NULL;
	}

	if(n1 < root -> data && n2 < root -> data){
		return lowest_common_ancestor(root -> left, n1, n2);
	}

	if(n1 > root -> data && n2 > root -> data){
		return lowest_common_ancestor(root -> right, n1, n2);
	}
	return root;
}



