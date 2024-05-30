#ifndef naufal_H
#define naufal_H
#include "global.h"

// Fungsi playgame
void playGame(addressTree Node);

// Fungsi carinode
addressList CariNodebyPilihan(int pilih, addressList first);

// Fungsi lihat jawaban
void lihatjawaban(addressTree rootTree);

// Fungsi caramain
void caramain();

// Fungsi edittree
void editTree(addressList P);

// Fungsi printmenuplay
void print_menuPlay(int highlight, char *choices[], int n_choices);

// Fungsi print menu utama
int menu_utama();

// Fungsi print menu pengaturan
int menu_pengaturan();

// Fungsi mengatur posisi kursor
void gotoxy(int x, int y);

// Fungsi ukuran layar konsol
void getConsoleSize(int *columns, int *rows);

// Fungsi menampilkan teks di tengah layar
void printCentered(const char *text, int y);

// Fungsi mengatur warna teks
void setTextColor(int textColor, int bgColor);

// Fungsi print menu utama
void print_menu(int highlight, char *choices[], int n_choices);

// Fungsi mencetak teks di tengah layar
void printCenteredText(const char *text, int y);

#endif