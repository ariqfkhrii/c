#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "ariq.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	// Deklarasi
	addressList P, Q;
	addressTree rootTree;
		
	// Buat dua link list
	P = (addressList) malloc (sizeof (listTopik));
	strcpy(P->topik, "Hewan");
	P->next = NULL;
	P->root = NULL;
	
	Q = (addressList) malloc (sizeof (listTopik));
	strcpy(Q->topik, "Buah");
	Q->next = NULL;
	Q->root = NULL;
	
	// Isi root yang ada di link list dengan pengisian tree
	printf("Topik: %s\n\n", P->topik);
	buatTree(P);
	simpanTree(P);
	printf("\nTraversal in-order: ");
	traversalInOrder(P->root);
	
	// Testing isi tree dari file	
	printf("\n\nTopik: %s\n", Q->topik);
	bacaFileTree(Q);
	
    // Cek apakah tree berhasil terisi dari file
	printf("\nTraversal in-order: ");
	traversalInOrder(Q->root);
	
	// Test tambah node tree
	verifikasiJawaban(Q->root);
	buatTree(Q);
	
	// Cek apakah node berhasil di tambah
	printf("\nTraversal in-order: ");
	traversalInOrder(Q->root);
	
	return 0;
}