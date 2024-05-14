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


void BuatTopik(addressList *P) {
    char judultopik[50];
    do {
        printf("Masukkan nama topik baru: ");
        fflush(stdin);
        fgets(judultopik, sizeof(judultopik), stdin);
        judultopik[strcspn(judultopik, "\n")] = '\0'; // Menghilangkan newline dari input
        
        // Memeriksa apakah topik sudah ada
        if (search(*P, judultopik) != NULL) {
            printf("Error: Topik '%s' sudah ada. Silakan masukkan nama topik yang berbeda.\n", judultopik);
        } else {
            break;
        }
    } while (1);

    // Membuat node baru untuk topik
    addressList newNode = (addressList)malloc(sizeof(listTopik));
    if (newNode == NULL) {
        printf("Error: Alokasi memori gagal.\n");
        return;
    }
    strcpy(newNode->topik, judultopik);
    newNode->next = NULL;
    newNode->root = NULL;

    // Menambahkan node ke dalam list
    if (*P == NULL) {
        *P = newNode; 
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

void simpantopik(addressList P) {
    FILE *file = fopen("topik.txt", "w");  // Buka file untuk ditulis (overwrite)
    if (file == NULL) {
        printf("Error: Gagal membuka file untuk ditulis.\n");
        return;
    }
    // Simpan topik ke dalam file hanya jika belum ada
    addressList current = P;
    while (current != NULL) {
        if (search(P, current->topik) == current) {
            fprintf(file, "%s\n", current->topik);  // Menyimpan topik ke dalam file
        }
        current = current->next;
    }

    fclose(file);
    printf("Data berhasil disimpan ke dalam file topik.txt.\n");
}



void bacadarifile(addressList *P) {
    FILE *file = fopen("topik.txt", "r");
    if (file == NULL) {
        printf("Error: Gagal membuka file untuk dibaca.\n");
        return;
    }

    char judultopik[50];
    while (fgets(judultopik, sizeof(judultopik), file) != NULL) {
        judultopik[strcspn(judultopik, "\n")] = '\0'; // Menghilangkan newline dari input
        addressList newNode = (addressList)malloc(sizeof(listTopik));
        if (newNode == NULL) {
            printf("Error: Alokasi memori gagal.\n");
            fclose(file);
            return;
        }
        strcpy(newNode->topik, judultopik);
        newNode->next = NULL;
        newNode->root = NULL;

        // Menambahkan node ke dalam list
        if (*P == NULL) {
            *P = newNode; 
        } else {
            addressList temp = *P;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    fclose(file);
    printf("Data berhasil dibaca dari file topik.txt.\n");
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


