#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"

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
        printf("Error: Gagal membuka file untuk ditulis.\n");
        return;
    }

    addressList current = P;
    while (current != NULL) {
        fprintf(file, "%s\n", current->topik); // Menyimpan topik ke dalam file
        current = current->next;
    }

    fclose(file);
    printf("Data berhasil disimpan ke dalam file topik.txt.\n");
}

void BuatTopik(addressList *P, addressList *first) {
    char judultopik[50];
    printf("Masukkan judul topik baru: ");
    fgets(judultopik, sizeof(judultopik), stdin);
    judultopik[strcspn(judultopik, "\n")] = '\0'; // Remove newline character

    addressList newNode = (addressList)malloc(sizeof(listTopik));
    if (newNode == NULL) {
        printf("Error: Alokasi memori gagal.\n");
        return;
    }

    if (search(*P, judultopik) != NULL) {
        printf("Error: Topik '%s' sudah ada. Silakan masukkan nama topik yang berbeda.\n", judultopik);
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

    printf("Topik baru '%s' telah berhasil dibuat.\n", judultopik);
    simpantopik(*P);
}

void bacadarifile(addressList *P, addressList *first) {
    FILE *file = fopen("topik.txt", "r");
    if (file == NULL) {
        printf("Error: Gagal membuka file untuk dibaca.\n");
        return;
    }

    char judultopik[50];
    while (fgets(judultopik, sizeof(judultopik), file) != NULL) {
        judultopik[strcspn(judultopik, "\n")] = '\0';
        addressList newNode = (addressList)malloc(sizeof(listTopik));
        if (newNode == NULL) {
            printf("Error: Alokasi memori gagal.\n");
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
void TampilkanTopik(addressList P) {
    printf("Daftar Topik:\n");
    addressList temp = P;
    int i = 1;
    while (temp != NULL) {
        printf("%d. %s\n", i, temp->topik);
        temp = temp->next;
        i++;
    }
}

void hapusTopik(addressList *P, addressList *first) {
    char judultopik[50];
    printf("Masukkan judul topik yang ingin dihapus: ");
    fgets(judultopik, sizeof(judultopik), stdin);
    judultopik[strcspn(judultopik, "\n")] = '\0'; // Remove newline character

    if (*P == NULL) {
        printf("Error: Tidak ada topik yang tersedia.\n");
        return;
    }

    addressList current = *P;
    addressList previous = NULL;

    while (current != NULL && strcmp(current->topik, judultopik) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Error: Topik '%s' tidak ditemukan.\n", judultopik);
        return;
    }

    if (previous == NULL) {
        *P = current->next;
        *first = *P;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("Topik '%s' telah berhasil dihapus.\n", judultopik);

    // Update the file after deletion
    simpantopik(*first);
}
