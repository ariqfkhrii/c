#ifndef global_H
#define global_H
#include <stdbool.h>
#include <stdio.h>

typedef char infotype[100];
typedef struct listNode *addressList;
typedef struct treeNode *addressTree;
typedef struct listNode {
	char topik[50];
	addressList next;
	addressTree root;
} listTopik;

typedef struct treeNode {
	infotype info;
	addressTree left;
	addressTree right;
} Tree;

#endif