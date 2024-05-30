#include "global.h"
#include "naufal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <windows.h> 
char jawaban;

void playGame(addressTree Node) {
    if (Node == NULL) {
        printCenteredText("Pohon tidak tersedia. Silakan buat pohon terlebih dahulu.\n", 24);
        return;
    }
    
    if (Node->left != NULL) {
        int highlight = 0;
        int choice = -1;
        int c;

        char *choices[] = { "Ya", "Tidak" };
        int n_choices = sizeof(choices) / sizeof(char*);
        
        while(1) {
            print_menuPlay(highlight, choices, n_choices);
			printCenteredText(Node->info, 24);
            c = _getch();
            if (c == 0 || c == 224) {
                switch (_getch()) {
                    case 72: 
                    case 75:
                        highlight = (highlight == 0) ? n_choices - 1 : highlight - 1;
                        break;
                    case 80: 
                    case 77:
                        highlight = (highlight == n_choices - 1) ? 0 : highlight + 1;
                        break;
                    default:
                        break;
                }
            } else if (c == 13) { 
                choice = highlight;
                break;
            }
        }

        if (choice == 0) { 
            playGame(Node->left);
        } else if (choice == 1) { 
            playGame(Node->right);
        }
    } else {
    	system("cls");
    	
    	printAsciiBanner();
    	if (Node->isJawaban == false && Node->left == NULL && Node->right == NULL){
            printCenteredText("Mohon maaf pertanyan belum ada jawaban", 24);
            return;
		}
    	printCenteredText("Apakah yang anda pikirkan itu ", 24);
        printCenteredText(Node->info, 25);
        _getch();
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
		printf("\t\t\t\t\t\t\t\t\t\t\tIndex tidak ditemukan!");
	}
	
	return Trav;
}

void lihatjawaban(addressTree rootTree){
	if (rootTree == NULL){
		return;
	}
	if (rootTree->isJawaban == true){
		printf("\t\t\t\t\t\t\t\t\t\t\t%s \n", rootTree->info);
	}else{
		lihatjawaban(rootTree->left);
		lihatjawaban(rootTree->right);
	}
}

void caramain() {
    printf("\n\t\t\t\t\t\t\t\t\t\t\t------Cara Main Mind-Master-------\n");
    printf("\n\t\t\t\t\t\t\t\t\t\t1. Pilih topik yang Anda inginkan.\n");
    printf("\t\t\t\t\t\t\t\t\t\t2. Pikirkan sebuah jawaban dari daftar yang muncul di layar.\n");
    printf("\t\t\t\t\t\t\t\t\t\t3. Mulailah permainan.\n");
    printf("\t\t\t\t\t\t\t\t\t\t4. Program akan menanyakan beberapa pertanyaan yang harus Anda jawab.\n");
    printf("\t\t\t\t\t\t\t\t\t\t5. Jawab pertanyaan dengan memilih 'Y' jika jawabannya benar, atau 'N' jika salah.\n");
    printf("\t\t\t\t\t\t\t\t\t\t6. Program akan menganalisis jawaban Anda untuk menebak apa yang Anda pikirkan.\n");
    printf("\t\t\t\t\t\t\t\t\t\t7. Jika program berhasil menebak dengan benar, permainan selesai dan kata berhasil ditebak!\n");
    
	printf("\n\t\t\t\t\t\t\t\t\t\t\t------Cara Menambahkan Topik-------\n");
    printf("\n\t\t\t\t\t\t\t\t\t\t1. Masukkan topik baru yang ingin Anda tambahkan.");
    printf("\n\t\t\t\t\t\t\t\t\t\t2. Topik yang sudah ada tidak bisa ditambahkan lagi.\n");
    
    printf("\n\t\t\t\t\t\t\t\t\t\t\t------Cara Menambahkan Pertanyaan dan Jawaban-------\n");
    printf("\n\t\t\t\t\t\t\t\t\t\t1. Pilih topik yang ingin Anda tambahkan pertanyaan dan jawabannya.\n");
    printf("\t\t\t\t\t\t\t\t\t\t2. Buat pertanyaan dan jawaban untuk topik tersebut.\n");
    printf("\t\t\t\t\t\t\t\t\t\t3. Akhiri setiap pertanyaan dengan tanda tanya.\n");
    printf("\t\t\t\t\t\t\t\t\t\t4. Jangan akhiri jawaban dengan tanda tanya.\n");
}


void editTree(addressList P) {
    char nodeToEdit[100];
    infotype newNodeData;
    addressTree temp;
    addressTree queue[100];
    int front = -1, rear = -1;

    if (P == NULL || P->root == NULL) {
        printf("\n\t\t\t\t\t\t\t\t\t\t\tPohon kosong. Tidak ada yang bisa diubah.\n");
        return;
    }

    printf("\n\t\t\t\t\t\t\t\t\t\t\tMasukkan data node yang ingin diedit: ");
    fflush(stdin);
    if (fgets(nodeToEdit, sizeof(nodeToEdit), stdin) == NULL) {
        printf("\n\t\t\t\t\t\t\t\t\t\t\tInput tidak valid. Silahkan coba lagi.\n");
        return;
    }
    nodeToEdit[strcspn(nodeToEdit, "\n")] = '\0';

    queue[++rear] = P->root;

    while (front < rear) {
        temp = queue[++front];

        if (temp != NULL) {
            if (strcmp(temp->info, nodeToEdit) == 0) {
                printf("\n\t\t\t\t\t\t\t\t\t\t\tNode ditemukan.\n");
                
                while (1) {
                    printf("\t\t\t\t\t\t\t\t\t\t\tMasukkan data baru: ");
                    fflush(stdin);
                    if (fgets(newNodeData, sizeof(newNodeData), stdin) == NULL) {
                        printf("\t\t\t\t\t\t\t\t\t\t\tInput tidak valid. Silahkan coba lagi.\n");
                        continue;
                    }
                    newNodeData[strcspn(newNodeData, "\n")] = '\0';

                    if (temp->isJawaban) {
                        if (strchr(newNodeData, '?') != NULL) {
                            printf("\n\t\t\t\t\t\t\t\t\t\t\tNode yang ingin diperbarui adalah jawaban, tidak boleh diisi dengan pertanyaan.\n");
                        } else {
                            break;
                        }
                    } else {
                        if (strchr(newNodeData, '?') == NULL) {
                            printf("\n\t\t\t\t\t\t\t\t\t\t\tNode yang ingin diperbarui adalah pertanyaan, harus diisi dengan pertanyaan.\n");
                        } else {
                            break;
                        }
                    }
                }

                strcpy(temp->info, newNodeData);
                simpanTree(P);
                printf("\t\t\t\t\t\t\t\t\t\t\tNode berhasil diubah.\n");
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

    printf("\n\t\t\t\t\t\t\t\t\t\t\tNode tidak ditemukan dalam pohon.\n");
}

void print_menuPlay(int highlight, char *choices[], int n_choices) {
	system("cls");
	printAsciiBanner();
	int columns, rows;
    getConsoleSize(&columns, &rows);

    for(int i = 0; i < n_choices; ++i) {
        int x = (columns - strlen(choices[i])) / 2;
        int y = (rows / 2 - n_choices / 2) + i;
        gotoxy(x, y);
        
        if (highlight == i) {
            printf(" -> %s", choices[i]); 
        } else {
            printf("   %s   ", choices[i]);
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
        c = _getch(); 
        if(c == 0 || c == 224) {
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
        } else if(c == 13) {
            choice = highlight;
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
        c = _getch(); 
        if(c == 0 || c == 224) {
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
        } else if(c == 13) {
            choice = highlight;
            system("cls");
            return choice;
        }
    }
}
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Fungsi untuk mendapatkan ukuran layar konsol
void getConsoleSize(int *columns, int *rows) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

// Fungsi untuk menampilkan teks di tengah layar
void printCentered(const char *text, int y) {
    int columns, rows;
    getConsoleSize(&columns, &rows);
    int len = strlen(text);
    int x = (columns - len) / 3;
    if (x < 0) x = 65;
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("%s", text);
}
void setTextColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}
void print_menu(int highlight, char *choices[], int n_choices) {
	system ("cls");
	printAsciiArt();

    int columns, rows;
    getConsoleSize(&columns, &rows);

    // Lebar dan tinggi kotak menu
    int box_width = 18;
    int box_height = n_choices + 4;

    // Hitung posisi x dan y untuk meletakkan kotak menu di tengah layar
    printf("\n\n");
    int x = (columns - box_width) / 2;
    int y = (rows - box_height) / 2;

    // Gambar bingkai atas
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("%c", 218); 
    for (int i = 0; i < box_width - 2; i++) printf("%c", 196); 
    printf("%c", 191); 
    
    // Gambar sisi samping dan isi menu
    for (int i = 1; i < box_height - 1; i++) {
        coord.Y = y + i;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        printf("%c", 179); 

        // Isi menu di baris yang sesuai
        if (i >= 2 && i < 2 + n_choices) {
            int choice_index = i - 2;
            if (highlight == choice_index) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                printf(" %-*s ", box_width - 3, choices[choice_index]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            } else {
                printf(" %-*s ", box_width - 3, choices[choice_index]);
            }
        } else {
            printf("%-*s", box_width - 2, "");
        }

        printf("%c", 179);
    }

    // Gambar bingkai bawah
    coord.Y = y + box_height - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("%c", 192); 
    for (int i = 0; i < box_width - 2; i++) printf("%c", 196);
    printf("%c", 217);
}
void printCenteredText(const char *text, int y) {
    int columns, rows;
    getConsoleSize(&columns, &rows);
    int x = (columns - strlen(text)) / 2;
    gotoxy(x, y);
    printf("%s", text);
}


void keluar() {
    system("cls");
    printf("\n\t\t\t\t\t\t\t\t\t\tKeluar dari program...\n");
    printf("\n\t\t\t\t\t\t\t\t\t\tTerima kasih telah bermain!\n");
}