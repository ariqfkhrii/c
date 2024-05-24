#ifndef naufal_H
#define naufal_H
#include "global.h"

void playGame(addressTree Node);
void lihatjawaban(addressTree rootTree);
void caramain();
void print_menu(int highlight, char *choices[], int n_choices);
void editTree(addressList P);
int menu_utama();
int menu_pengaturan();
void keluar();

#endif