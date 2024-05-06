#ifndef ariq_H
#define ariq_H

#include "global.h"

addressTree buatNodeTree (infotype data);
/* Tujuan: Membuat dan menginisialisasi sebuah node baru dalam pohon.
 * I.S.   : Data yang ingin dimasukkan ke dalam node telah tersedia.
 * F.S.   : Sebuah node baru telah dibuat dengan data yang telah disediakan. */

addressTree insertNodeTree (addressTree rootTree, infotype data);
/* Tujuan: Memasukkan node baru ke dalam pohon.
 * I.S.   : Pohon dan data yang ingin dimasukkan telah tersedia.
 * F.S.   : Node baru telah dimasukkan ke dalam pohon menggunakan insertion secara level order.
 * NOTE	  : Algoritma ini diambil dari website 'www.geeksforgeeks.org' kemudian dimodifikasi sesuai kebutuhan */

int maxDepth (addressTree rootTree);
/* Tujuan: Menghitung kedalaman maksimum dari pohon.
 * I.S.   : Pohon mungkin kosong atau tidak.
 * F.S.   : Kedalaman maksimum dari pohon telah dihitung dan dikembalikan. 
 * NOTE	  : Algoritma ini diambil dari website 'www.geeksforgeeks.org' kemudian dimodifikasi sesuai kebutuhan */

void kategoriJawaban (addressTree rootTree);
/* Tujuan: Menandai node-node yang berisi jawaban dalam pohon.
 * I.S.   : Pohon telah terbentuk.
 * F.S.   : Node-node yang merupakan jawaban telah ditandai. */

void printParent (addressTree rootTree, int *adaPertanyaan);
/* Tujuan: Mencetak parent node terakhir yang belum memiliki child.
 * I.S.   : Pohon telah terbentuk.
 * F.S.   : Parent node terakhir yang belum memiliki child telah dicetak. */

void buatTree (addressList P);
/* Tujuan: Membuat pohon dengan meminta input pengguna secara iteratif.
 * I.S.   : Pohon kosong atau sudah terbentuk sebagian.
 * F.S.   : Pohon telah terbentuk sesuai dengan input pengguna. */

void simpanTree (addressList P);
/* Tujuan: Menyimpan struktur pohon ke dalam file eksternal.
 * I.S.   : Pohon terbentuk dan ada data yang ingin disimpan.
 * F.S.   : Struktur pohon telah disimpan dalam file eksternal. */

void bacaFileTree (addressList P);
/* Tujuan: Membaca struktur pohon dari file eksternal.
 * I.S.   : File eksternal yang berisi struktur pohon sudah ada.
 * F.S.   : Struktur pohon telah dibaca dari file eksternal. */

void traversalInOrder (addressTree rootTree);
/* Tujuan: Melakukan traversal in-order pada pohon.
 * I.S.   : Pohon terbentuk.
 * F.S.   : Node-node dalam pohon telah dicetak secara in-order. */

void verifikasiJawaban (addressTree rootTree);
/* Tujuan: Memeriksa dan mengonfirmasi jawaban yang dimasukkan oleh pengguna.
 * I.S.   : Pohon terbentuk dan ada jawaban yang perlu diverifikasi.
 * F.S.   : Jawaban telah diverifikasi dan disimpan jika sesuai atau diminta pengisian ulang jika tidak sesuai. */

#endif
