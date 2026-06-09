/*
[スタック・ポインタ操作 オリジナル問題 created by NotebookLM]

問題 逆ポーランド記法に基づく実数の演算を行う計算機プログラムを拡張する。演算に使用するスタックは、構造体 node をポインタで連結したリストとして表現され、外部変数 stack が最上部を指す仕様である。以下の問いに答えよ。

問1 関数 sum_stack は、スタックに積まれているすべての数値の合計を計算して返す関数である。空欄 A を埋めて関数 sum_stack を完成せよ。ただし、スタックが空の場合は、合計を 0.0 とすること。

問2 関数 duplicate は、スタックの最上部にある数値を複製し、新たにスタックの最上部に積む（スタックが1段深くなる）関数である。空欄 B を埋めて関数 duplicate を完成せよ。ただし、スタックが空の場合は何も行わないものとする。

問3 関数 clear_stack は、スタックに積まれているすべての要素を取り出し、割り当てられたメモリを解放してスタックを空にする関数である。関数 pop を利用して空欄 C を埋め、関数 clear_stack を完成せよ。

問4 関数 divide は、スタックの上から2番目の数値を最上部の数値で除算し（スタックは2段浅くなる）、その結果をスタックに積む関数である。空欄 D を埋めて関数 divide を完成せよ。ただし、スタックに二つ以上の数値が積まれていない場合や、最上部の数値が 0.0（ゼロ除算）の場合は、何も行わないものとする。

問5 関数 move_top_to_third は、スタックの最上部にある要素を、上から3番目の位置に移動させる関数である（スタックの要素数は変わらない）。関数 pop と push を呼び出して実現することも可能であるが、ここでは node のポインタ操作のみで行う方法で、空欄 E を埋めて関数を完成せよ。ただし、スタックに三つ以上の数値が積まれていない場合は、何も行わないものとする。

*/



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

int stack_depth(void)
{
	struct node *nodep = stack;
	int depth = 0;
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
		struct node *nodep = stack -> next;
		double top_value = stack -> value;
		free(stack);
		stack = nodep;
		return top_value;
	}
	return 0.0;
}


/*問１．スタックの要素の合計を返す*/
double sum_stack(void){
	struct node *nodep = stack;
	double total = 0.0;
	while(nodep != NULL){
		total += nodep -> value;
		nodep = nodep -> next;
	}
	return total;
}

/*問２．スタックの最上部の値を複製する*/
void duplicate(void){
	if(stack_depth() > 0){
		struct node *nodep = (struct node*)malloc(sizeof(struct node));
		// nodep = stackとするとmallocで確保したメモリ領域を捨てて既存の先頭ノードのアドレスで上書きしてしまい、メモリリークが発生する。ノードそのものではなく「ノードの持つ値」をコピーが正しい。
		nodep -> value = stack -> value;
		nodep -> next = stack;
		stack = nodep;
	}
}

/*問３．スタックを完全に空にする*/
void clear_stack(void){
	while(stack != NULL){
		pop(); // pop関数の引数は無し
	}

}

/*問４．上から2番目の数値を最上部の数値で除算し、結果を積む*/
void divide(void){
	if(stack_depth() >= 2 && stack -> value != 0.0){
		double value1 = pop(); // popで安全に値を取り出す。使わない場合はfreeでノードを開放する必要がある
		double value2 = pop();
		push(value2 / value1);
	}
}

/*問５．最上部の要素をポインタ操作で上から3番目に移動させる*/
void move_top_to_third(void){
	if(stack_depth()>=3){
		struct node *nodep1 = stack-> next;
		struct node *nodep2 = stack;
		nodep2 -> next = nodep1 -> next -> next;
		nodep1 -> next -> next = nodep2;
		stack = nodep1;
	}
}
		

		
		
		

int main(void) {
    printf("=== 初期データのセット ===\n");
    push(4.0);
    push(8.0);
    push(2.0);
    /* 現在のスタック: 最上部から順に 2.0 -> 8.0 -> 4.0 */
    printf("現在のスタック: ");
    print_stack(); 

    printf("\n=== 問1: sum_stack のテスト ===\n");
    printf("合計値: %5.2f\n", sum_stack()); /* 期待される出力: 14.00 */

    printf("\n=== 問2: duplicate のテスト ===\n");
    duplicate(); /* 最上部の 2.0 を複製 */
    printf("複製後のスタック: ");
    print_stack(); /* 期待される出力: | 2.00| | 2.00| | 8.00| | 4.00| */

    printf("\n=== 問4: divide のテスト ===\n");
    /* 上から2番目(2.0) を 最上部(2.0) で除算し、結果(1.0) を積む */
    divide(); 
    printf("除算後のスタック: ");
    print_stack(); /* 期待される出力: | 1.00| | 8.00| | 4.00| */

    printf("\n=== 問5: move_top_to_third のテスト ===\n");
    /* 最上部の 1.0 を、上から3番目に移動させる */
    move_top_to_third();
    printf("移動後のスタック: ");
    print_stack(); /* 期待される出力: | 8.00| | 4.00| | 1.00| */

    printf("\n=== 問3: clear_stack のテスト ===\n");
    clear_stack(); /* スタックをすべて空にする */
    printf("クリア後のスタック: ");
    print_stack(); /* 期待される出力: (何も出力されず改行のみ) */
    printf("現在の深さ: %d\n", stack_depth()); /* 期待される出力: 0 */

    return 0;
}
