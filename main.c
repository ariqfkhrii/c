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
	system("chcp 65001");
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
                printAsciiArt();
                TampilkanTopik(List, first);
                printf("\n\t\t\t\t\t\t\t\t\t\t\tketik 0 untuk kembali");
                printf("\n\t\t\t\t\t\t\t\t\t\t\tMasukkan topik yang anda inginkan: ");
                scanf("%d", &pilih);
                if (pilih == 0)
                {
                	break;
				}
                List = CariNodebyPilihan(pilih, first);
                if (List == NULL)
                {
                	printf("\n\t\t\t\t\t\t\t\t\t\t\t");
                	system("pause");
                	break;
				}
                printf("\t\t\t\t\t\t\t\t\t\t\tLihat list jawaban : (Y/N)");
                scanf(" %c", &jawaban);
                if (jawaban == 'Y' || jawaban == 'y') {
                	printf("\n\n\t\t\t\t\t\t\t\t\t\t\t----------------Daftar List---------------\n");
                    lihatjawaban(List->root);
                    printf("\n\t\t\t\t\t\t\t\t\t\t\tPikirkan satu jawaban yang ada!\n");
                	printf("\t\t\t\t\t\t\t\t\t\t\tSaya akan mencoba untuk menebaknya! \n");
                }
                printf("\t\t\t\t\t\t\t\t\t\t\tPlay Now? (Y/N): ");
                scanf(" %c", &jawaban);
                    if (jawaban == 'Y' || jawaban == 'y') {
                    	system("cls");
                    	printAsciiBanner();
                        playGame(List->root);
                    }
                printf("\n\t\t\t\t\t\t\t\t\t\t\t");
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
                            printAsciiArt();
                            TampilkanTopik(List, first);
                            printf("\n\t\t\t\t\t\t\t\t\t\t\t");
                            system("pause");
                            break;
                        case 1:
                            // Buat Topik
                            printAsciiArt();
                            TampilkanTopik(List, first);
                            BuatTopik(&List, &first);
                            simpantopik(first);
                            printf("\n\t\t\t\t\t\t\t\t\t\t\t");
                            system("pause");
                            break;
                        case 2:
						    // Hapus Topik
						    system("cls");
						    printAsciiArt();
                            TampilkanTopik(List,first);
                            printf("\n\t\t\t\t\t\t\t\t\t\t\tketik 0 untuk kembali");
                            printf("\n\t\t\t\t\t\t\t\t\t\t\tMasukkan topik yang anda inginkan: ");
                            scanf("%d", &pilih);
			                if (pilih == 0)
			                {
			                	break;
							}
                            List = CariNodebyPilihan(pilih, first);
			                if (List == NULL)
			                {
			                	printf("\n\t\t\t\t\t\t\t\t\t\t\t");
			                	system("pause");
			                	break;
							}
                            deleteTree(&(List->root));
                            deleteFile(List);
                            hapusTopik(List, &first);
                            simpantopik(first);
                            printf("\n\t\t\t\t\t\t\t\t\t\t\t");
						    system("pause");
                            break;
                        case 3:
                            // buat tree
                            system("cls");
                            printAsciiArt();
                            TampilkanTopik(List,first);
                            printf("\n\t\t\t\t\t\t\t\t\t\t\tketik 0 untuk kembali");
                            printf("\n\t\t\t\t\t\t\t\t\t\t\tMasukkan topik yang anda inginkan: ");
                            scanf("%d", &pilih);
			                if (pilih == 0)
			                {
			                	break;
							}
                            List = CariNodebyPilihan(pilih, first);
			                if (List == NULL)
			                {
			                	printf("\n\t\t\t\t\t\t\t\t\t\t\t");
			                	system("pause");
			                	break;
							}
                            if (List->root != NULL){
                                printf("\t\t\t\t\t\t\t\t\t\t\tMohon maaf Tree sudah terisi!\n");
                                printf("\n\t\t\t\t\t\t\t\t\t\t\t");
                                system("pause");
                                break;
                            }
                            buatTree(List);
                            simpanTree(List);
                            printf("\n\t\t\t\t\t\t\t\t\t\t\t");
                            system("pause");
                            break;
                        case 4:
                            // menghapus_pertanyaan_jawaban();
                            system("cls");
                            printAsciiArt();
                            TampilkanTopik(List,first);
                            printf("\n\t\t\t\t\t\t\t\t\t\t\tketik 0 untuk kembali");
                            printf("\n\t\t\t\t\t\t\t\t\t\t\tMasukkan topik yang anda inginkan: ");
                            scanf("%d", &pilih);
			                if (pilih == 0)
			                {
			                	break;
							}
                            List = CariNodebyPilihan(pilih, first);
			                if (List == NULL)
			                {
			                	printf("\n\t\t\t\t\t\t\t\t\t\t\t");
			                	system("pause");
			                	break;
							}
                            deleteTree(&(List->root));
                            deleteFile(List);
                            printf("\n\t\t\t\t\t\t\t\t\t\t\t");
                            system("pause");
                            break;
                        case 5:
                            // buat node 
                            system("cls");
                            printAsciiArt();
                            TampilkanTopik(List,first);
                            printf("\n\t\t\t\t\t\t\t\t\t\t\tketik 0 untuk kembali");
                            printf("\n\t\t\t\t\t\t\t\t\t\t\tMasukkan topik yang anda inginkan: ");
                            scanf("%d", &pilih);
			                if (pilih == 0)
			                {
			                	break;
							}
                            List = CariNodebyPilihan(pilih, first);
			                if (List == NULL)
			                {
			                	printf("\n\t\t\t\t\t\t\t\t\t\t\t");
			                	system("pause");
			                	break;
							}
                            verifikasiJawaban(List->root);
                            buatTree(List);
                            kategoriJawaban(List->root);
                            simpanTree(List);
                            printf("\n\t\t\t\t\t\t\t\t\t\t\t");
                            system("pause");
                            break;
                        case 6:
                            // edit tree
                            system("cls");
                            printAsciiArt();
                            TampilkanTopik(List,first);
                            printf("\n\t\t\t\t\t\t\t\t\t\t\tketik 0 untuk kembali");
                            printf("\n\t\t\t\t\t\t\t\t\t\t\tMasukkan topik yang anda inginkan: ");
                            scanf("%d", &pilih);
			                if (pilih == 0)
			                {
			                	break;
							}
                            List = CariNodebyPilihan(pilih, first);
			                if (List == NULL)
			                {
			                	printf("\n\t\t\t\t\t\t\t\t\t\t\t");
			                	system("pause");
			                	break;
							}
                            editTree(List);
                            simpanTree(List);
                            printf("\n\t\t\t\t\t\t\t\t\t\t\t");
                            system("pause");
                            break;
                        case 7:
                            // print tree
                            system("cls");
                            printAsciiArt();
                            TampilkanTopik(List,first);
                            printf("\n\t\t\t\t\t\t\t\t\t\t\tketik 0 untuk kembali");
                            printf("\n\t\t\t\t\t\t\t\t\t\t\tMasukkan topik yang anda inginkan: ");
                            scanf("%d", &pilih);
			                if (pilih == 0)
			                {
			                	break;
							}
                            List = CariNodebyPilihan(pilih, first);
			                if (List == NULL)
			                {
			                	printf("\n\t\t\t\t\t\t\t\t\t\t\t");
			                	system("pause");
			                	break;
							}
                            printTree(List->root);
                            printTreeToFile(List->root, "printTree.txt");
                            printf("\n\t\t\t\t\t\t\t\t\t\t\t");
                            system("pause");
                            break;
                        case 8:
                            kembali = true;
                            break;
                        default:
                            break;
                    }
                }
                break;
            }
            case 2:
//              cara main
				system("cls");
                printAsciiArt();
                caramain();
                printf("\n\t\t\t\t\t\t\t\t\t\t\t");
                system("pause");
                break;
            case 3:
            	//exit
            	system("cls");
                printAsciiArt();
                printf("\n\n");
                printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\tTerimakasih");
                return 0;
            default:
                break;
        }
    }
    return 0;
}
