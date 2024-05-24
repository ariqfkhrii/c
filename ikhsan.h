#ifndef ikhsan_H
#define ikhsan_H
#include "global.h"


void printAsciiArt();

void printTreeHelper(addressTree node, int space, char* prefix);
/* Tujuan: Membantu fungsi printTree untuk mencetak pohon dengan tanda '-' untuk subtree kiri dan '+' untuk subtree kanan.
 * I.S.   : Node saat ini dan jumlah spasi untuk indentation sudah tersedia.
 * F.S.   : Pohon telah dicetak dengan format yang lebih mudah dibaca, dengan tanda '-' untuk subtree kiri dan '+' untuk subtree kanan. */


void printTree(addressTree rootTree);
/* Tujuan: Mencetak seluruh pohon dari akar (root) dengan format yang lebih mudah dibaca.
 * I.S.   : Root pohon tersedia.
 * F.S.   : Pohon telah dicetak dengan format yang lebih mudah dibaca, dimulai dari root. */


void pilihTopikDanCetakTree(addressList head);
/* Tujuan: Memilih topik dari linked list yang tersedia dan mencetak pohon yang sesuai dengan topik yang dipilih.
 * I.S.   : Linked list dengan topik-topik yang tersedia sudah ada.
 * F.S.   : Topik telah dipilih oleh pengguna dan pohon yang sesuai dengan topik tersebut telah dicetak. */


void deleteTree(addressTree *rootTree);


#endif

