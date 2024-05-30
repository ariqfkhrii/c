#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "ikhsan.h"
addressList search(addressList topik, char *judul) {
    addressList current = topik;
    while (current != NULL) {
        if (strcmp(current->topik, judul) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void simpantopik(addressList P) {
    FILE *file = fopen("topik.txt", "w"); // Buka file untuk ditulis (overwrite)
    if (file == NULL) {
        printf("\t\t\t\t\t\t\t\t\t\t\tError: Gagal membuka file untuk ditulis.\n");
        return;
    }

    addressList current = P;
    while (current != NULL) {
        fprintf(file, "%s\n", current->topik); // Menyimpan topik ke dalam file
        current = current->next;
    }

    fclose(file);
    printf("\t\t\t\t\t\t\t\t\t\t\tData berhasil disimpan ke dalam file topik.txt.\n");
}

void BuatTopik(addressList *P, addressList *first) {
    char judultopik[50];
    *P = *first;
    printf("\n\n\t\t\t\t\t\t\t\t\t\t\t----------------Buat Topik---------------\n");
    printf("\n\t\t\t\t\t\t\t\t\t\t\tMasukkan judul topik baru: ");
    fflush(stdin);
    fgets(judultopik, sizeof(judultopik), stdin);
    judultopik[strcspn(judultopik, "\n")] = '\0'; // Remove newline character

    addressList newNode = (addressList)malloc(sizeof(listTopik));
    if (newNode == NULL) {
        printf("\t\t\t\t\t\t\t\t\t\t\tError: Alokasi memori gagal.\n");
        return;
    }

    if (search(*P, judultopik) != NULL) {
        printf("\t\t\t\t\t\t\t\t\t\t\tError: Topik '%s' sudah ada. Silakan masukkan nama topik yang berbeda.\n", judultopik);
        free(newNode);
        return;
    }

    strcpy(newNode->topik, judultopik);
    newNode->next = NULL;
    newNode->root = NULL;

    if (*P == NULL) {
        *P = newNode;
        *first = *P;
    } else {
        addressList temp = *P;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    printf("\n\t\t\t\t\t\t\t\t\t\t\tTopik baru '%s' telah berhasil dibuat.\n", judultopik);
}

void bacadarifile(addressList *P, addressList *first) {
    FILE *file = fopen("topik.txt", "r");
    if (file == NULL) {
        printf("\t\t\t\t\t\t\t\t\t\t\tError: Gagal membuka file untuk dibaca.\n");
        return;
    }

    char judultopik[50];
    while (fgets(judultopik, sizeof(judultopik), file) != NULL) {
        judultopik[strcspn(judultopik, "\n")] = '\0';
        addressList newNode = (addressList)malloc(sizeof(listTopik));
        if (newNode == NULL) {
            printf("\t\t\t\t\t\t\t\t\t\t\tError: Alokasi memori gagal.\n");
            fclose(file);
            return;
        }
        strcpy(newNode->topik, judultopik);
        newNode->next = NULL;
        newNode->root = NULL;

        if (*P == NULL) {
            *P = newNode;
            *first = *P;
        } else {
            addressList temp = *P;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    fclose(file);
}

// Fungsi untuk menampilkan daftar topik
void TampilkanTopik(addressList P, addressList first) {
    printf("\n\n\t\t\t\t\t\t\t\t\t\t\t----------------Daftar Topik---------------\n");
    if (first == NULL) {
        printf("\t\t\t\t\t\t\t\t\t\t\tDaftar topik kosong.\n");
        return;
    }
    
    addressList temp = first;
    int nomor = 1;
    while (temp != NULL) {
        printf("\t\t\t\t\t\t\t\t\t\t\t\t%d. %s\n", nomor, temp->topik);
        temp = temp->next;
        nomor++;
    }
}



void hapusTopik(addressList nodeToDelete, addressList *first) {
    if (nodeToDelete == NULL) {
        printf("Topik yang akan dihapus tidak ada.\n");
        return;
    }

    // Jika node yang akan dihapus adalah node pertama
    if (*first == nodeToDelete) {
        *first = nodeToDelete->next;
    } else {
        // Cari node sebelumnya
        addressList prev = *first;
        while (prev != NULL && prev->next != nodeToDelete) {
            prev = prev->next;
        }

        // Jika node sebelumnya ditemukan, ubah pointer next-nya
        if (prev != NULL) {
            prev->next = nodeToDelete->next;
        } else {
            printf("\t\t\t\t\t\t\t\t\t\t\t\tTopik sebelumnya tidak ditemukan. Penghapusan gagal.\n");
            return;
        }
    }

    // Bebaskan memori dari node yang dihapus
    free(nodeToDelete);
    printf("\t\t\t\t\t\t\t\t\t\t\t\tTopik berhasil dihapus.\n");
}




