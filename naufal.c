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

addressList CariNodebyPilihan(int pilih, addressList first){
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

void editTree(addressList P) {
    char nodeToEdit[100];
    infotype newNodeData;
    addressTree temp;
    addressTree queue[100];
    int front = -1, rear = -1;

    if (P == NULL || P->root == NULL) {
        printf("Pohon kosong. Tidak ada yang bisa diubah.\n");
        return;
    }

    printf("Masukkan data node yang ingin diedit: ");
    fflush(stdin);
    if (fgets(nodeToEdit, sizeof(nodeToEdit), stdin) == NULL) {
        printf("Input tidak valid. Silahkan coba lagi.\n");
        return;
    }
    nodeToEdit[strcspn(nodeToEdit, "\n")] = '\0';

    queue[++rear] = P->root;

    while (front < rear) {
        temp = queue[++front];

        if (temp != NULL) {
            if (strcmp(temp->info, nodeToEdit) == 0) {
                printf("Node ditemukan.\n");
                
                while (1) {
                    printf("Masukkan data baru: ");
                    fflush(stdin);
                    if (fgets(newNodeData, sizeof(newNodeData), stdin) == NULL) {
                        printf("Input tidak valid. Silahkan coba lagi.\n");
                        continue;
                    }
                    newNodeData[strcspn(newNodeData, "\n")] = '\0';

                    if (temp->isJawaban) {
                        if (strchr(newNodeData, '?') != NULL) {
                            printf("Node yang ingin diperbarui adalah jawaban, tidak boleh diisi dengan pertanyaan.\n");
                        } else {
                            break;
                        }
                    } else {
                        if (strchr(newNodeData, '?') == NULL) {
                            printf("Node yang ingin diperbarui adalah pertanyaan, harus diisi dengan pertanyaan.\n");
                        } else {
                            break;
                        }
                    }
                }

                strcpy(temp->info, newNodeData);
                simpanTree(P);
                printf("Node berhasil diubah.\n");
                return;
            }

            if (temp->left != NULL) {
                queue[++rear] = temp->left;
            }
            if (temp->right != NULL) {
                queue[++rear] = temp->right;
            }
        }
    }

    printf("Node tidak ditemukan dalam pohon.\n");
}

void print_menu(int highlight, char *choices[], int n_choices) {
    system("cls"); // Bersihkan layar (untuk Windows)
    for(int i = 0; i < n_choices; ++i) {
        if(highlight == i) {
            printf("-> %s\n", choices[i]); // Highlight pilihan
        } else {
            printf("   %s\n", choices[i]);
        }
    }
}

int menu_utama() {
    int highlight = 0;
    int choice = -1;
    int c;
    
    char *choices[] = { 
        "Mulai Bermain",
        "Pengaturan",
        "Cara Main",
        "Keluar",
    };
    int n_choices = sizeof(choices) / sizeof(char*);

    print_menu(highlight, choices, n_choices);
    while(1) {
        c = _getch(); // Mengambil input
        if(c == 0 || c == 224) {
            // Arrow keys are two-byte sequences in Windows: 0 atau 224 diikuti oleh kode
            switch(_getch()) {
                case 72: // Arrow up
                    if(highlight == 0)
                        highlight = n_choices - 1;
                    else
                        --highlight;
                    break;
                case 80: // Arrow down
                    if(highlight == n_choices - 1)
                        highlight = 0;
                    else 
                        ++highlight;
                    break;
                default:
                    break;
            }
            print_menu(highlight, choices, n_choices);
        } else if(c == 13) { // Enter key
            choice = highlight;
            // Bersihkan baris tambahan di bawah menu
            system("cls");
            return choice;
        }
    }
}

int menu_pengaturan() {
    int highlight = 0;
    int choice = -1;
    int c;
    
    char *choices[] = { 
        "Tampilkan Topik",
        "Tambah Topik",
        "Hapus Topik",
        "Membuat Pertanyaan dan Jawaban",
        "Menghapus Pertanyaan dan Jawaban",
        "Menambah Pertanyaan dan Jawaban",
        "Mengubah Pertanyaan dan Jawaban",
        "Lihat Pertanyaan dan Jawaban",
        "Kembali ke Menu Utama",
    };
    int n_choices = sizeof(choices) / sizeof(char*);

    print_menu(highlight, choices, n_choices);
    while(1) {
        c = _getch(); // Mengambil input
        if(c == 0 || c == 224) {
            // Arrow keys are two-byte sequences in Windows: 0 atau 224 diikuti oleh kode
            switch(_getch()) {
                case 72: // Arrow up
                    if(highlight == 0)
                        highlight = n_choices - 1;
                    else
                        --highlight;
                    break;
                case 80: // Arrow down
                    if(highlight == n_choices - 1)
                        highlight = 0;
                    else 
                        ++highlight;
                    break;
                default:
                    break;
            }
            print_menu(highlight, choices, n_choices);
        } else if(c == 13) { // Enter key
            choice = highlight;
            // Bersihkan baris tambahan di bawah menu
            system("cls");
            return choice;
        }
    }
}

void keluar() {
    system("cls");
    printf("Keluar dari program...\n");
    // Logika untuk keluar
    printf("Terima kasih telah bermain!\n");
}