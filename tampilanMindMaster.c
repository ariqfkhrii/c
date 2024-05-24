#include <stdio.h>
#include <conio.h> // Untuk menggunakan _getch()

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