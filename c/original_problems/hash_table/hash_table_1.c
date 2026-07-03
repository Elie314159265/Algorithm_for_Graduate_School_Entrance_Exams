#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 5

typedef struct HashNode{
	char key;
	int value;
	struct HashNode *next;
} HashNode;

// ハッシュテーブル本体
HashNode *hash_table[TABLE_SIZE] = {NULL};

unsigned int hash(const char *key){
	unsigned int hash_val = 0;
	while(*key){
		hash_val = (hash_val * 31) + *key++;
	}
	// 0,1,2,3,4のうちどれかを返す。
	return hash_val % TABLE_SIZE;
}

void insert(const char *key, int value){
	// ハッシュ値を計算。0~4の整数。
	unsigned int idx = hash(key);
	while

