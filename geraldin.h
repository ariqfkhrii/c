#ifndef GERALDIN_H
#define GERALDIN_H
#include "global.h"

addressList search(addressList topik, char *judul);
void simpantopik(addressList P);
void BuatTopik(addressList *P, addressList *first);
void bacadarifile(addressList *P, addressList *first);
void TampilkanTopik(addressList P, addressList first);
void hapusTopik(addressList nodeToDelete, addressList *first);


#endif