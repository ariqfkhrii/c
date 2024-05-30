#ifndef ikhsan_H
#define ikhsan_H
#include "global.h"


void printAsciiArt();
void printAsciiBanner()

void printTreeHelper(FILE *file, addressTree node, int space, char* prefix);
void printTreeHelperCLI(addressTree node, int level, int isLast, int *path);
/* Tujuan: Membantu fungsi printTree untuk mencetak pohon dengan tanda '-' untuk subtree kiri dan '+' untuk subtree kanan.
 * I.S.   : Node saat ini dan jumlah spasi untuk indentation sudah tersedia.
 * F.S.   : Pohon telah dicetak dengan format yang lebih mudah dibaca, dengan tanda '-' untuk subtree kiri dan '+' untuk subtree kanan. */


void printTree(addressTree rootTree);
void printTreeToFile(addressTree rootTree, const char* fileName);
/* Tujuan: Mencetak seluruh pohon dari akar (root) dengan format yang lebih mudah dibaca.
 * I.S.   : Root pohon tersedia.
 * F.S.   : Pohon telah dicetak dengan format yang lebih mudah dibaca, dimulai dari root. */

void deleteTree(addressTree *rootTree);
void deleteFile(addressList P);


#endif

