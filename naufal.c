#include "global.h"
#include "naufal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void playGame(addressTree Node) {
    if (Node == NULL) {
        printf("Pohon tidak tersedia. Silakan buat pohon terlebih dahulu.\n");
        return;
    }

    printf("%s\n", Node->info);

    char jawaban[2];
    if (Node->left != NULL) {
        printf("Jawab (y/n): ");
        scanf("%s", jawaban);
        printf("\n");
        if (jawaban[0] == 'y' || jawaban[0] == 'Y') {
            playGame(Node->left);
        } else if (jawaban[0] == 'n' || jawaban[0] == 'N') {
            playGame(Node->right);
        } else {
            printf("Input tidak valid.\n");
        }
    }
}

void menu() {
	char jawaban;
	addressList P, Q;
    addressTree rootTree;

    addressTree root = NULL;

    // Buat dua link list
    P = (addressList)malloc(sizeof(listTopik));	
    strcpy(P->topik, "Hewan");
    P->next = NULL;
    P->root = NULL;

    Q = (addressList)malloc(sizeof(listTopik)); 
    strcpy(Q->topik, "Buah");
    Q->next = NULL;
    Q->root = NULL;
	
	int pilihopsi = 0;
	char opsi[5][20] = {"Play Now", "Cara Main", "Setting", "Exit"}; 
	int totalOpsi = 5; 
	char key;
    
    do {
        system("cls");
        printf("Mind Master \n");
        for (i = 0; i < totalOpsi; i++) {
            if (i == pilihopsi) {
                printf("-> ");
            } else {
                printf("   ");
            }
            printf("%s\n", opsi[i]);
        }

        key = getch();

        switch(key) {
            case 72:
                pilihopsi = (pilihopsi - 1 + totalOpsi) % totalOpsi;
                break;
            case 80: 
                pilihopsi = (pilihopsi + 1) % totalOpsi;
                break;
        }
    } while(key != 13);
    switch(pilihopsi) {
        case 0:
        	system("cls");
        	printf("Selamat datang di permainan tebak-tebakan!\n");
		    printf("Jawablah pertanyaan berikut dengan 'y' untuk ya dan 'n' untuk tidak.\n\n");
        	
		    printf("Topik: %s\n", P->topik);
		    bacaFileTree(P);
		    
		    lihatjawaban(P->root);
		    printf("Apa yang anda pikirkan? \n");
		    printf("Play Now? (Y/N) : ");
		    scanf("%c", &jawaban);
		    if (jawaban == 'Y' || jawaban == 'y'){
		    	system("cls");
		    	playGame(P->root);
			}else{
				exit(1);
			}
		
            break;
        case 1:
            printf("Opsi 2");
            break;
        case 2:
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
            printf("opsi 3");
            break;
        case 3:
        	printf("Terimakasih");
        	exit(1);
            break;
    }
}

void lihatjawaban(addressTree rootTree){
	if (rootTree == NULL){
		return;
	}
	if (rootTree->left == NULL && rootTree->right == NULL){
		printf("%s \n", rootTree->info);
	}else{
		lihatjawaban(rootTree->left);
		lihatjawaban(rootTree->right);
	}
}