#ifndef ariq_H
#define ariq_H
#include "global.h"

/* Variabel untuk menunjuk sebuah node dalam queue dan struktur queue */
typedef struct QueueNode *addressQueueNode;
typedef struct Queue *addressQueue;

// Struktur data noda yeng ada pada queue
typedef struct QueueNode 
{
    addressTree data;
    addressQueueNode next;
} QueueNode;

// Struktur queue
typedef struct Queue 
{
    addressQueueNode front, rear;
} Queue;

// Fungsi untuk membuat dan menginisialisasi node baru dalam pohon
addressTree buatNodeTree(infotype data);
/* 
   Tujuan: Membuat dan menginisialisasi node baru dalam pohon.
   I.S   : -
   F.S   : Mengembalikan alamat dari node yang baru saja dibuat dengan nilai data yang telah ditentukan, pointer left dan right diatur ke NULL, dan isJawaban yang diatur ke false.
*/

// Fungsi untuk membuat dan menginisialisasi node baru dalam antrian
addressQueueNode buatNodeQueue(addressTree nodeTree);
/* 
   Tujuan: Membuat dan menginisialisasi node baru dalam antrian.
   I.S   : -
   F.S   : Mengembalikan alamat dari node yang baru saja dibuat dengan data berupa alamat dari node tree yang diberikan, serta pointer next diatur ke NULL.
*/

// Fungsi untuk membuat antrian baru
addressQueue buatQueue();
/* 
   Tujuan: Membuat antrian baru.
   I.S   : -
   F.S   : Mengembalikan alamat dari antrian yang baru saja dibuat dengan pointer front dan rear diatur ke NULL.
*/

// Fungsi untuk memeriksa apakah antrian kosong
bool isEmpty(addressQueue queue);
/* 
   Tujuan: Memeriksa apakah antrian kosong.
   I.S   : Antrian telah dibuat.
   F.S   : Mengembalikan nilai true jika antrian kosong, dan false jika tidak kosong.
*/

// Fungsi untuk menambahkan node baru ke dalam antrian
void Enqueue(addressQueue queue, addressTree nodeTree);
/* 
   Tujuan: Menambahkan node baru ke dalam antrian.
   I.S   : Antrian telah dibuat.
   F.S   : Node baru dengan data berupa alamat dari node tree yang diberikan ditambahkan ke dalam antrian.
*/

// Fungsi untuk menghapus dan mengembalikan node dari depan antrian
addressTree Dequeue(addressQueue queue);
/* 
   Tujuan: Menghapus dan mengembalikan node dari depan antrian.
   I.S   : Antrian telah dibuat dan tidak kosong.
   F.S   : Mengembalikan alamat dari node yang dihapus dari depan antrian.
*/

// Fungsi untuk memasukkan node baru ke dalam pohon
addressTree insertNodeTree(addressTree rootTree, infotype data);
/* 
   Tujuan: Memasukkan node baru ke dalam pohon.
   I.S   : Pohon mungkin kosong atau tidak kosong.
   F.S   : Jika pohon kosong, maka node baru akan menjadi root. Jika pohon tidak kosong, maka node baru akan ditambahkan sebagai anak kiri atau kanan dari node yang memiliki anak kosong pertama.
   NOTE	 : Algoritma ini diambil dari website 'www.geeksforgeeks.org' yang kemudian diubah sesuai kebutuhan
*/

// Fungsi untuk menghitung kedalaman maksimum dari pohon
int maxDepth(addressTree rootTree);
/* 
   Tujuan: Menghitung kedalaman maksimum dari pohon.
   I.S   : Pohon mungkin kosong atau tidak kosong.
   F.S   : Mengembalikan nilai integer yang menyatakan kedalaman maksimum dari pohon.
   NOTE	 : Algoritma ini sepenuhnya diambil dari website 'www.geeksforgeeks.org'
*/

// Fungsi untuk mengkategorikan apakah suatu node merupakan jawaban atau bukan
void kategoriJawaban(addressTree rootTree);
/* 
   Tujuan: Mengkategorikan apakah suatu node merupakan jawaban atau bukan.
   I.S   : Pohon mungkin kosong atau tidak kosong.
   F.S   : Setiap node dalam pohon akan ditandai apakah merupakan jawaban atau bukan, berdasarkan keberadaan tanda tanya (?) dalam informasi node tersebut.
*/

// Fungsi untuk mencetak informasi dari parent node yang belum memiliki anak
void printParent(addressTree rootTree, int *adaPertanyaan);
/* 
   Tujuan: Mencetak informasi dari parent node yang belum memiliki anak.
   I.S   : Pohon mungkin kosong atau tidak kosong.
   F.S   : Jika ada parent node yang belum memiliki anak, informasi dari parent node tersebut dicetak dan mengatur adaPertanyaan r ke 0.
*/

// Fungsi untuk memeriksa kompleksitas topik berdasarkan 32 node pertama dalam pohon.
bool periksaKompleksitasTopik(addressTree root);
/* 
   Tujuan: Memastikan bahwa dalam 32 node pertama dari pohon, tidak ada jawaban yang ditemukan.
   I.S   : Pohon tidak kosong.
   F.S   : Mengembalikan nilai true jika semua node dari root sampai node ke-32 adalah pertanyaan, dan false jika terdapat jawaban di antara 32 node pertama.
*/

// Fungsi untuk membangun pohon berdasarkan input pengguna
void buatTree(addressList P);
/* 
   Tujuan: Membangun pohon berdasarkan input pengguna.
   I.S   : Pohon mungkin kosong atau tidak kosong.
   F.S   : Pohon akan dibangun berdasarkan input pengguna dengan kondisi tertentu, seperti minimal kedalaman pohon yang dimiliki adalah 6.
*/

// Fungsi untuk menyimpan struktur pohon ke dalam file
void simpanTree(addressList P);
/* 
   Tujuan: Menyimpan struktur pohon ke dalam file.
   I.S   : Pohon telah dibuat dan tidak kosong.
   F.S   : Struktur pohon akan disimpan ke dalam file sesuai dengan format yang ditentukan.
*/

// Fungsi untuk membaca struktur pohon dari file
void bacaFileTree(addressList P);
/* 
   Tujuan: Membaca struktur pohon dari file.
   I.S   : File mungkin kosong atau berisi data pohon.
   F.S   : Struktur pohon akan dibaca dari file dan dimasukkan ke dalam pohon.
*/

// Fungsi untuk melakukan verifikasi jawaban yang telah dibuat
void verifikasiJawaban(addressTree rootTree);
/* 
   Tujuan: Melakukan verifikasi jawaban yang telah dibuat.
   I.S   : Pohon mungkin kosong atau tidak kosong.
   F.S   : Pengguna akan diminta untuk memverifikasi jawaban yang telah dibuat dalam pohon, dengan opsi untuk mengubah jawaban atau menambahkan pertanyaan baru jika jawaban tidak sesuai.
*/

#endif
