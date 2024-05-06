#include "global.h"
#include "naufal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
