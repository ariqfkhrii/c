// main.c
#include "global.h"
#include "ariq.h"
#include "geraldin.h"
#include "ikhsan.h"
#include "naufal.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main() 
{
    addressList List = NULL, first = NULL, trav = NULL;
    addressTree rootTree;
    int pilihan, pilihanPengaturan;
    bool kembali;
    int pilih;
    char jawaban;

    bacadarifile(&List, &first);
    trav = first;
    while (trav != NULL)
    {
        bacaFileTree(trav);
        trav = trav->next;
    }   
    
    while(1) 
    {
        pilihan = menu_utama();
        switch(pilihan) {
            case 0:
                system("cls");
                TampilkanTopik(List);
                scanCentered("Masukkan topik yang anda inginkan: ", "%d", &pilih, 12);
                List = CariNodebyPilihan(pilih, first);
                scanCentered("Lihat Jawaban? (Y/N)", " %c", &jawaban, 14);
                if (jawaban == 'Y' || jawaban == 'y') { 
                    lihatjawaban(List->root);
                }
                printCentered("Pikirkan list jawaban yang ada! Saya akan mencoba untuk menebaknya!", 18);
                scanCentered("Play Now? (Y/N): ", " %c", &jawaban, 19);
                if (jawaban == 'Y' || jawaban == 'y') {
                	system("cls");
                    playGame(List->root);
                }
                system("pause");
                break;
            case 1: 
            {
                kembali = false;
                while(!kembali) {
                    pilihanPengaturan = menu_pengaturan();
                    switch(pilihanPengaturan) {
                        case 0:
                            // Lihat topik
                            TampilkanTopik(List);
                            system("pause");
                            break;
                        case 1:
                            // Buat Topik
                            BuatTopik(&List, &first);
                            system("pause");
                            break;
                        case 2:
                            // Hapus Topik
                            system("cls");
                            TampilkanTopik(List);
                            hapusTopik(&List, &first);
                            system("pause");
                            break;
                        case 3:
                            // buat tree
                            system("cls");
                            TampilkanTopik(List);
                            printCentered("Masukkan topik yang anda inginkan: ", 12);
                            gotoxy(0, 13); // Pindah ke baris berikutnya untuk input
                            scanf("%d", &pilih);
                            List = CariNodebyPilihan(pilih, first);
                            if (List->root != NULL){
                                printCentered("Mohon maaf Tree sudah terisi!", 15);
                                system("pause");
                                break;
                            }
                            buatTree(List);
                            simpanTree(List);
                            system("pause");
                            break;
                        case 4:
                            // menghapus_pertanyaan_jawaban();
                            system("pause");
                            break;
                        case 5:
                            // buat node 
                            system("cls");
                            TampilkanTopik(List);
                            printCentered("Masukkan topik yang anda inginkan: ", 12);
                            gotoxy(0, 13); // Pindah ke baris berikutnya untuk input
                            scanf("%d", &pilih);
                            List = CariNodebyPilihan(pilih, first);
                            verifikasiJawaban(List->root);
                            buatTree(List);
                            kategoriJawaban(List->root);
                            simpanTree(List);
                            system("pause");
                            break;
                        case 6:
                            // edit tree
                            system("cls");
                            TampilkanTopik(List);
                            printCentered("Masukkan topik yang anda inginkan: ", 12);
                            gotoxy(0, 13); // Pindah ke baris berikutnya untuk input
                            scanf("%d", &pilih);
                            List = CariNodebyPilihan(pilih, first);
                            editTree(List);
                            simpanTree(List);
                            system("pause");
                            break;
                        case 7:
                            // print tree
                            system("cls");
                            TampilkanTopik(List);
                            printCentered("Masukkan topik yang anda inginkan: ", 12);
                            gotoxy(0, 13); // Pindah ke baris berikutnya untuk input
                            scanf("%d", &pilih);
                            List = CariNodebyPilihan(pilih, first);
                            printTree(List->root);
                            system("pause");
                            break;
                        case 8:
                            kembali = true; // Kembali ke menu utama
                            break;
                        default:
                            break;
                    }
                }
                break;
            }
            case 2:
                // cara main
                caramain();
                system("pause");
                break;
            case 3:
                printCentered("Terimakasih", 12);
                return 0;
            default:
                break;
        }
    }
    return 0;
}
