#ifndef GERALDIN_H
#define GERALDIN_H
#include "global.h"

void BuatTopik(addressList *P);
void TampilkanTopik(addressList P);
void simpantopik(addressList P);
void bacadarifile(addressList *P);
addressList search(addressList topik, char *judul);

#endif