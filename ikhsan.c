#include "global.h"
#include "ariq.h"
#include "ikhsan.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printTreeHelper(addressTree node, int space, char* prefix) {
    int COUNT = 25; // Space between levels
    if (node == NULL) {
        return;
    }

    space += COUNT;

    printTreeHelper(node->right, space, "+");

    printf("\n");
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }

    if (space == COUNT) {
        printf("[Root] ");
    }

    printf("%s%s\n", prefix, node->info);

    // Menampilkan subtree kiri dengan tanda "-"
    if (node->left != NULL) {
        printTreeHelper(node->left, space, "-");
    }
}

void printTree(addressTree rootTree) {
    printTreeHelper(rootTree, 0, "");
}



void pilihTopikDanCetakTree(addressList head) {
    while (1) {
        addressList current = head;
        int count = 0;
        int choice = -1;

        // Menampilkan daftar topik
        printf("\nDaftar Topik:\n");
        while (current != NULL) {
            printf("%d. %s\n", ++count, current->topik);
            current = current->next;
        }

        // Meminta pengguna memilih topik
        printf("Pilih topik yang ingin dicetak tree-nya (masukkan nomor, 0 untuk keluar): ");
        scanf("%d", &choice);

        // Keluar dari loop jika pengguna memilih 0
        if (choice == 0) {
            break;
        }

        // Validasi pilihan
        if (choice < 1 || choice > count) {
            printf("Pilihan tidak valid.\n");
            continue;
        }

        // Reset current ke head dan iterasi untuk menemukan topik yang dipilih
        current = head;
        count = 1;
        while (current != NULL && count < choice) {
            current = current->next;
            count++;
        }

        // Cetak tree dari topik yang dipilih
        if (current != NULL) {
            printf("Tree untuk topik: %s\n", current->topik);
            printf("'+' untuk subtree kanan\n '-' untuk subtree kiri\n\n\n");
            printTree(current->root);
        } else {
            printf("Topik tidak ditemukan.\n");
        }
    }
}


void deleteTree(addressTree *rootTree) {
    if (*rootTree != NULL) {
        // Hapus anak kiri
        deleteTree(&((*rootTree)->left));
        // Hapus anak kanan
        deleteTree(&((*rootTree)->right));
        // Hapus node saat ini
        free(*rootTree);
        // Atur referensi ke node saat ini menjadi NULL
        *rootTree = NULL;
    }
}


void printAsciiArt() {
    const char *asciiArt[] = {
        "          ____                                      ",
        "        ,'  , `.                                    ",
        "     ,-+-,.' _ |   ,--,                       ,---, ",
        "  ,-+-. ;   , || ,--.'|          ,---,      ,---.'| ",
        " ,--.'|'   |  ;| |  |,       ,-+-. /  |     |   | : ",
        "|   |  ,', |  ': `--'_      ,--.'|'   |     |   | | ",
        "|   | /  | |  || ,' ,'|    |   |  ,\"' |   ,--.__| | ",
        "'   | :  | :  |, '  | |    |   | /  | |  /   ,'   | ",
        ";   . |  ; |--'  |  | :    |   | |  | | .   '  /  | ",
        "|   : |  | ,     '  : |__  |   | |  |/  '   ; |:  | ",
        "|   : '  |/      |  | '.'| |   | |--'   |   | '/  ' ",
        ";   | |`-'       ;  :    ; |   |/       |   :    :| ",
        "|   ;/           |  ,   /  '---'         \\   \\  /   ",
        "'---'             ---`-'                  `----'    ",
        "                                                    ",
        "                                                                                  ",
        "          ____                                                               ",
        "        ,'  , `.                                ___                           ",
        "     ,-+-,.' _ |                              ,--.'|_                         ",
        "  ,-+-. ;   , ||                              |  | :,'               __  ,-.  ",
        " ,--.'|'   |  ;|                 .--.--.      :  : ' :             ,' ,'/ /|  ",
        "|   |  ,', |  ':    ,--.--.     /  /    '   .;__,'  /      ,---.   '  | |' |  ",
        "|   | /  | |  ||   /       \\   |  :  /`./   |  |   |      /     \\  |  |   ,'  ",
        "'   | :  | :  |,  .--.  .-. |  |  :  ;_     :__,'| :     /    /  | '  :  /    ",
        ";   . |  ; |--'    \\__\\/ : . .   \\  \\    `.    '  : |__  .    ' / | |  | '     ",
        "|   : |  | ,       ,\" .--.; |    `----.   \\   |  | '.'| '   ;   /| ;  : |     ",
        "|   : '  |/       /  /  ,.  |   /  /`--'  /   ;  :    ; '   |  / | |  , ;     ",
        ";   | |`-'       ;  :   .'   \\ '--'.     /    |  ,   /  |   :    |  ---'     ",
        "|   ;/           |  ,     .-./   `--'---'      ---`-'    \\   \\  /             ",
        "'---'             `--`---'                                `----'             ",
        "=========================================================================================",
        NULL
    };

    for (int i = 0; asciiArt[i] != NULL; i++) {
        fputs(asciiArt[i], stdout);
        fputs("\n", stdout);
    }
}