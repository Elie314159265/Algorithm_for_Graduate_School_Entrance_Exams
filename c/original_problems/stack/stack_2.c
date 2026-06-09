/*
[スタック・ポインタ操作 オリジナル問題 created by NotebookLM]
問題 逆ポーランド記法に基づく実数の演算を行う計算機プログラムをさらに拡張する。スタックは構造体 node をポインタで連結したリストであり、外部変数 stack が最上部を指す。以下の問いに答えよ。（※前回作成した push, pop, stack_depth 等の基本関数は使用可能とする）

問1 関数 count_positive は、スタックに積まれている数値のうち、正の数（0.0より大きい数値）がいくつあるかを数えて返す関数である。空欄 A を埋めて関数を完成せよ。

問2 関数 insert_second は、引数に与えられた実数をスタックの最上部ではなく、「上から2番目の位置」に挿入する関数である。空欄 B を埋めて関数を完成せよ。（すでにメモリ獲得と、スタックが空だった場合の処理は記述されているものとする）

問3 関数 delete_second は、スタックの上から2番目の要素のみを削除（メモリ解放）する関数である（スタックは1段浅くなり、最上部と3番目が繋がる）。関数 pop や push を用いず、ポインタ操作と free 関数のみで空欄 C を埋めよ。ただし、スタックに2つ以上の数値が積まれていない場合は何も行わない。

問4 関数 average_top_two は、スタックの最上部と上から2番目の数値を取り出して平均値を計算し、その結果を新たにスタックに積む関数である（スタックは1段浅くなる）。関数 pop と push を用いて空欄 D を埋めよ。ただし、スタックに2つ以上の要素がない場合は何も行わない。

問5 関数 rotate_three は、スタックの最上部から3つの要素を巡回（ローテート）させる関数である。具体的には、1番目を2番目に、2番目を3番目に、3番目を1番目（最上部）に移動させる。関数 pop や push を用いず、ポインタ操作のみで空欄 E を埋めよ。ただし、スタックに3つ以上の要素がない場合は何も行わない。

*/



#include <stdlib.h>
#include <stdio.h>

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



/*問１．正の数の個数を返す*/
int count_positive(void){
	int count = 0;
	struct node *nodep = stack;
	while(nodep != NULL){
		if(nodep -> value > 0.0){
			count++;
		}
		nodep = nodep -> next;
	}
	return count;
}


/*問２．上から2番目の位置に数値を挿入する*/
void insert_second(double insert_value){
	struct node *nodep = (struct node*)malloc(sizeof(struct node));
	nodep -> value = insert_value;

	if(stack == NULL){
		nodep -> next =NULL;
		stack = nodep;
	}else{
		nodep -> next = stack -> next;
		stack -> next = nodep;
	}
}

/*問３．上から２番目の要素を削除(free)する*/
void delete_second(void){
	if(stack_depth()>=2){
		struct node *nodep = stack -> next;
		stack -> next = nodep -> next;
		free(nodep);
	}
}

/*問４．上から2つの平均値を計算して積む*/
void average_top_two(void){
	if(stack_depth() >= 2){
		double value1 = pop();
		double value2 = pop();
		push((value1 + value2)/2.0);
	}
}

/*問５．最上部から3つの要素を巡回させる(3番目を最上部に持ってくる)*/
void rotate_three(void){
	if(stack_depth() >= 3){
		struct node *nodep1 = stack -> next;
		struct node *nodep2 = stack -> next -> next;
		nodep1 -> next = nodep2 -> next;
		nodep2 -> next = stack;
		stack = nodep2;
	}
}

		


