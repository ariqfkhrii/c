#ifndef global_H
#define global_H
#include <stdbool.h>

/* Variabel untuk diisi sebuah pertanyaan maupun jawaban untuk tree */
typedef char infotype[100];

/* Variabel untuk menunjuk sebuah struktur tree maupun list */
typedef struct listNode *addressList;
typedef struct treeNode *addressTree;

/* Struktur data linked list */
typedef struct listNode {
	char topik[50];
	addressList next;
	addressTree root;
} listTopik;

/* Struktur data tree */
typedef struct treeNode {
	infotype info;
	addressTree left;
	addressTree right;
	bool isJawaban;
} Tree;

/* Variabel untuk iterasi */
int i, j;

#endif