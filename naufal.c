#include "global.h"
#include "naufal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

char jawaban;

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

addressList CariNodebyPilihan(int pilih){
	i = 1;
	addressList Trav;
	bool found = false;
	Trav = first;
	
	while (i < pilih && Trav != NULL){
		Trav = Trav->next;
		i++;
	}
	
	if (Trav == NULL){
		printf("Index tidak ditemukan!");
	} else {
		return Trav;
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

void caramain() {
	system("cls");
    printf("------Cara Main Mind-Master-------\n");
    printf("1. Pilih topik yang Anda inginkan.\n");
    printf("2. Pikirkan list jawaban yang ada pada layar.\n");
    printf("3. Mulailah game.\n");
    printf("4. Program akan menanyakan rentetan pertanyaan yang harus dijawab oleh Anda.\n");
    printf("5. Jawab pertanyaan dengan memilih 'Y' jika jawabannya benar, atau 'N' jika salah.\n");
    printf("6. Program akan menganalisis jawaban Anda untuk menebak apa yang Anda pikirkan.\n");
    printf("7. Jika program menebak dengan benar, permainan selesai dan kata berhasil ditebak!\n");
    printf("8. Jika program gagal menebak, Anda bisa menambahkan pertanyaan dan jawaban baru untuk diperbaiki kecerdasannya.\n");
}

void menuUser() {
    addressList List = NULL;
    addressTree rootTree;
    addressTree root = NULL;

    int pilihopsi = 0;
    char opsi[5][20] = {
        "Play Now", 
        "Cara Main", 
        "Setting", 
        "Exit"
    }; 
    int totalOpsi = 4;
    char key;

    MainMenuUser:
    while (1) {
        system("cls");
        printf("Mind Master \n");
        for (int i = 0; i < totalOpsi; i++) {
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
            case 13:
                switch(pilihopsi) {
                    case 0:
                        system("cls");
                        int pilih;
                        char jawaban;
                        bacadarifile(&List);
                        TampilkanTopik(List);
                        printf("Masukkan topik yang anda inginkan: ");
                        scanf("%d", &pilih);
                        List = CariNodebyPilihan(pilih);
                        lihatjawaban(List->root);
                        printf("Pikirkan list jawaban yang ada! Saya akan mencoba untuk menebaknya! \n");
                        printf("Play Now? (Y/N): ");
                        scanf(" %c", &jawaban);
                        if (jawaban == 'Y' || jawaban == 'y') {
                            system("cls");
                            playGame(List->root);
                        }
                        break;
                    case 1:
                        caramain();
                        printf("Kembali ke menu utama (Y/N)? ");
                        scanf(" %c", &key);
                        if (key == 'Y' || key == 'y') {
                            goto MainMenuUser;
                        }
                        break;
                    case 2:
                        menuAdmin();
                        printf("Kembali ke menu utama (Y/N)? ");
                        scanf(" %c", &key);
                        if (key == 'Y' || key == 'y') {
                            goto MainMenuUser;
                        }
                        break;
                    case 3:
                        printf("Terimakasih");
                        exit(0);
                        break;
                }
                break;
        }
    }
}

void menuAdmin() {
    addressList List = NULL;
    bacadarifile(&List);
    int pilihopsi = 0;
    char opsi[4][50] = {
        "Tambah Topik", 
        "Hapus Topik", 
        "Pilih Topik untuk CRUD Tree ", 
        "Kembali ke menu utama"
    }; 
    int totalOpsi = 4;
    char key;

    AdminMenu:
    while (1) {
        system("cls");
        printf("Menu Setting \n");
        for (int i = 0; i < totalOpsi; i++) {
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
            case 13:
                switch(pilihopsi) {
                    case 0:
                        system("cls");
                        BuatTopik(&List);
                        printf("Kembali ke menu utama (Y/N)? ");
                        scanf(" %c", &key);
                        if (key == 'Y' || key == 'y') {
                            goto AdminMenu;
                        }
                        break;
                    case 1:
                        system("cls");
                        printf("Hapus topik\n");
                        // Add logic to handle topic deletion
                        printf("Kembali ke menu utama (Y/N)? ");
                        scanf(" %c", &key);
                        if (key == 'Y' || key == 'y') {
                            goto AdminMenu;
                        }
                        break;
                    case 2:
                        system("cls");
                        int pilih;
                        bacadarifile(&List);
                        TampilkanTopik(List);
                        printf("Masukkan topik yang anda inginkan: ");
                        scanf("%d", &pilih);
                        List = CariNodebyPilihan(pilih);
                        handleTreeOptions(List);
                        printf("Kembali ke menu utama (Y/N)? ");
                        scanf(" %c", &key);
                        if (key == 'Y' || key == 'y') {
                            goto AdminMenu;
                        }
                        break;
                    case 3:
                        return;
                }
                break;
        }
    }
}

void handleTreeOptions(addressList List) {
    int pilihopsi = 0;
    char opsi[6][30] = {
        "Buat Tree", 
        "Hapus Tree", 
        "Tambah Node Tree", 
        "Edit Tree", 
        "Print Tree", 
        "Kembali ke menu utama"
    }; 
    int totalOpsi = 6;
    char key;

    while (1) {
        system("cls");
        printf("Menu Setting \n");
        for (int i = 0; i < totalOpsi; i++) {
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
            case 13:
                switch(pilihopsi) {
                    case 0:
                        system("cls");
                        buatTree(List);
                        break;
                    case 1:
                        system("cls");
                        printf("Hapus tree\n");
                        // Add logic to handle tree deletion
                        break;
                    case 2:
                        system("cls");
                        buatTree(List);
                        break;
                    case 3:
                        system("cls");
                        printf("Edit tree\n");
                        // Add logic to handle tree editing
                        break;
                    case 4:
                        system("cls");
                        printf("Print Tree\n");
                        printTree(List->root);
                        // Add logic to handle tree printing
                        break;
                    case 5:
                        return;
                }
                break;
        }
    }
}

//void editTree(addressTree rootTree){
//	if (rootTree == NULL){
//		printf("Maaf tree saat ini kosong, tidak dapat diedit!\n");
//		return;
//	}
//
//	
//}