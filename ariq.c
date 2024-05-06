#include "global.h"
#include "ariq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

addressTree buatNodeTree (infotype data)
{
	// Deklarasi
	addressTree R;
	
	// Inisialisasi
	R = (addressTree) malloc (sizeof (Tree)); // Mengalokasikan memori sebesar ukuran dari struktur Tree
	
	// Algoritma
	if (R == NULL) // Kondisi ketika peng-alokasian memori gagal
	{
		system("cls");
		printf("Alokasi memori gagal.");
		printf("\n\nTekan apapun untuk keluar.");
		getchar();
		exit(1);
	}
	else // Kondisi ketika peng-alokasian memori berhasil
	{
		strcpy(R->info, data);
		R->left = NULL;
		R->right = NULL;
		R->isJawaban = false;
	}
	return R; // Mengembalikan alamat dari node Tree yang sudah dibuat
};

addressTree insertNodeTree(addressTree rootTree, infotype data)
{
	// Algoritma
    if (rootTree == NULL) // Kondisi jika akar dari tree tersebut belum ada
    {
        rootTree = buatNodeTree(data);
        return rootTree;
    }
    
	// Kondisi ketika akar dari tree sudah ada, maka akan melakukan insertion secara level order
	// Deklarasi dan Inisialisasi
    addressTree temp;
    addressTree queue[100];
    int front = -1, rear = -1;
    queue[++rear] = rootTree; // Root dari tree akan dimasukkan kedalam queue di indeks rear yaitu -1 kemudian rear akan di tingkatkan menjadi 0

    while (front != rear) // JIka tidak ada lagi node yang bisa di proses maka program akan berhenti
    {
        temp = queue[++front]; // temp akan berisi nilai front kemudian nilai front akan ditingkatkan sebanyak satu
        
        if (temp->isJawaban == true) // Jika node saat ini merupakan jawaban maka akan diabaikan dan dilanjutkan ke node berikutnya
        {
            continue;
    	}
    	
        if (temp->left != NULL) // JIka anak kiri dari temp tidak null maka anak kiri tersebut akan dimasukkan ke queue di posisi rear dan akan meningkatkan posisi rear sebanyak satu
            queue[++rear] = temp->left;
        else // JIka anak kiri kosong maka akan ditambahkan sebuah node
        {
            temp->left = buatNodeTree(data);
            return rootTree;
        }
        

        if (temp->right != NULL) // JIka anak kanan dari temp tidak null maka anak kanan tersebut akan dimasukkan ke queue di posisi rear dan akan meningkatkan posisi rear sebanyak satu
            queue[++rear] = temp->right;
        else // JIka anak kanan kosong maka akan ditambahkan sebuah node
        {
            temp->right = buatNodeTree(data);
            return rootTree;
        }
    }

    return rootTree;
}

int maxDepth (addressTree rootTree)
{
	// Algoritma
    if (rootTree == NULL) // JIka root tree kosong maka kedalaman tree tersebut berarti 0
        return 0;
    
    else 
	{
		// Deklarasi dan Inisialisasi
        int lDepth = maxDepth(rootTree->left); // Ini adalah langkah rekursif untuk mencari berapa nilai maksimal kedalaman dari anak kiri yang dimiliki root
        int rDepth = maxDepth(rootTree->right); // Ini adalah langkah rekursif untuk mencari berapa nilai maksimal kedalaman dari anak kanan yang dimiliki root

        if (lDepth > rDepth) // Membandingkan kedalaman yang lebih dalam itu apakah anak kiri yang dimiliki root atau anak kanan yang dimiliki root
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}

void kategoriJawaban (addressTree rootTree) 
{
    // Deklarasi
    char *tandaTanya;
    
    // Algoritma
    if (rootTree == NULL) // Jika node tree kosong maka akan return
	{
        return;
    }

    if (rootTree->left == NULL && rootTree->right == NULL) // Mengecek apakah node tersebut adalah node yang baru ditambahkan
    {    
        tandaTanya = strchr(rootTree->info, '?'); // Mengecek apakah info pada node ini memiliki tanda tanya atau tidak
        if (tandaTanya == NULL) // Jika tidak memiliki tanda tanya maka node tersebut akan ditandai sebagai jawaban
        {
            rootTree->isJawaban = true;
            return;
        }
    }
    
    kategoriJawaban(rootTree->left);
    kategoriJawaban(rootTree->right);
}

void printParent(addressTree rootTree, int *adaPertanyaan)
{
    if (rootTree == NULL) // JIka root tree kosong maka akan return
    {
        return;
    }
    
    // Deklarasi dan inisialisasi
    addressTree temp;
    addressTree queue[100];
    int front = -1, rear = -1;
    queue[++rear] = rootTree; // Root dari tree akan dimasukkan kedalam queue di indeks rear yaitu -1 kemudian rear akan di tingkatkan menjadi 0
    
    while (front != rear) // JIka tidak ada lagi node yang bisa di proses maka program akan berhenti
    {
        temp = queue[++front]; // temp akan berisi nilai front kemudian nilai front akan ditingkatkan sebanyak satu
        
        if (temp->isJawaban == true) // Jika node saat ini merupakan jawaban maka akan diabaikan dan dilanjutkan ke node berikutnya
        {
            continue;
    	}
    	
        if (temp->left != NULL) // JIka anak kiri dari temp tidak null maka anak kiri tersebut akan dimasukkan ke queue di posisi rear dan akan meningkatkan posisi rear sebanyak satu
            queue[++rear] = temp->left;
        else // Jika anak kiri temp null maka temp akan di print
        {
        	printf("\nValidasi saat ini: %s", temp->info);
            *adaPertanyaan = 0;
            break;
        }

        if (temp->right != NULL) // JIka anak kanan dari temp tidak null maka anak kanan tersebut akan dimasukkan ke queue di posisi rear dan akan meningkatkan posisi rear sebanyak satu
            queue[++rear] = temp->right;
        else // Jika anak kanan temp null maka temp akan di print
        {
        	printf("\nValidasi saat ini: %s", temp->info);
            *adaPertanyaan = 0;
            break;
        }
    }
}

void buatTree(addressList P) {
    // Deklarasi
    int adaPertanyaan = 1;
    infotype data, temp_data;

    // Algoritma
    // Melakukan validasi awal ketika root tree null
    if (P->root == NULL) {
        printf("Gunakan tanda '?' jika merupakan sebuah pertanyaan.\nKetik 'SELESAI' ketika anda sudah selesai.\nValidasi awal: ");
        fflush(stdin);
        fgets(data, sizeof(data), stdin);
        data[strcspn(data, "\n")] = '\0';
        strcpy(temp_data, data);
        if (strcmp(strupr(temp_data), "SELESAI") == 0) {
            return;
        }

        P->root = insertNodeTree(P->root, data);
        kategoriJawaban(P->root);
    }
	
	// Melakukan pengisian untuk node yang belum terisi selama inputan user bukan 'SELESAI' dan kedalaman tree tersebut belum sebanyak 6 atau lebih
    while (strupr(temp_data) != "SELESAI" && maxDepth(P->root) <= 6) {
        printf("Kedalaman tree saat ini: %d (minimal memiliki kedalaman 6)\n", maxDepth(P->root));
        printParent(P->root, &adaPertanyaan);
        if (adaPertanyaan == 1) {
            printf("\nTree sudah tidak memiliki pertanyaan yang bisa diisi.");
            if (maxDepth(P->root) <= 6) {
                printf("\nTree tidak memenuhi syarat memiliki kedalaman 6, silahkan anda gunakan fitur Tambah Node Tree.");
            }
            break;
        }

        printf("\nJika 'YA': ");
        fflush(stdin);
        fgets(data, sizeof(data), stdin);
        data[strcspn(data, "\n")] = '\0';
        strcpy(temp_data, data);
        if (strcmp(strupr(temp_data), "SELESAI") == 0) {
            if (maxDepth(P->root) <= 6) {
                printf("\nAnda belum memenuhi syarat memiliki kedalaman 6.\n");
                continue;
            } else {
                break;
            }
        }

        P->root = insertNodeTree(P->root, data);
        kategoriJawaban(P->root);

        printf("Jika 'TIDAK': ");
        fflush(stdin);
        fgets(data, sizeof(data), stdin);
        data[strcspn(data, "\n")] = '\0';
        strcpy(temp_data, data);
        if (strcmp(strupr(temp_data), "SELESAI") == 0) {
            printf("\nAnda belum mengisi kondisi jika 'TIDAK'\n");
            continue;
        }

        P->root = insertNodeTree(P->root, data);
        kategoriJawaban(P->root);
        adaPertanyaan = 1;
    }
}


void simpanTree(addressList P) 
{
	// Deklarasi dan Inisialisasi
    char folder[] = "Topik"; // Nama folder
    char filepath[100]; // Nama file
    addressTree temp;
    addressTree queue[100];
    addressTree rootTree;
    int front = -1, rear = -1;
    rootTree = P->root;
    
    if (rootTree == NULL) // JIka root tree kosong maka akan return
    {
        return;
    }
    
    queue[++rear] = rootTree; // Root dari tree akan dimasukkan kedalam queue di indeks rear yaitu -1 kemudian rear akan di tingkatkan menjadi 0
	
	// Membuat path file
    sprintf(filepath, "%s/%s.txt", folder, P->topik);
	
	// Buka file untuk penulisan
    FILE *file = fopen(filepath, "w");
    if (file == NULL) 
	{
        printf("Gagal membuat file.\n");
        exit(1);
    }

    while (front != rear) // JIka tidak ada lagi node yang bisa di proses maka program akan berhenti
	{
        temp = queue[++front]; // temp akan berisi nilai front kemudian nilai front akan ditingkatkan sebanyak satu
        fprintf(file, "%s\n", temp->info); // temp akan di print

        if (temp->left != NULL) // JIka anak kiri dari temp tidak null maka anak kiri tersebut akan dimasukkan ke queue di posisi rear dan akan meningkatkan posisi rear sebanyak satu
		{
            queue[++rear] = temp->left;
        }

        if (temp->right != NULL) // JIka anak kanan dari temp tidak null maka anak kanan tersebut akan dimasukkan ke queue di posisi rear dan akan meningkatkan posisi rear sebanyak satu
		{
            queue[++rear] = temp->right;
        }
    }
	
	// Tutup file setelah proses penulisan selesai
    fclose(file);
}

void bacaFileTree (addressList P) 
{
	// Deklarasi dan Inisialisasi
	infotype data;
    char folder[] = "Topik"; // Nama folder
    char filepath[100]; // Nama file
    
    // Membuat path file
    sprintf(filepath, "%s/%s.txt", folder, P->topik);
    
    // Buka file untuk melakukan pembacaan
    FILE *file = fopen(filepath, "r");
    if (file == NULL) 
	{
    	system("cls");
        printf("Gagal membaca file.\n");
        exit(1);
    }
    
    // Loop untuk membaca file hingga akhir file
    while (!feof(file)) 
    {
        fscanf(file, "%s\n", data); // Membaca data dari file dan menyimpannya ke variabel data
        P->root = insertNodeTree(P->root, data); // Memasukkan data ke dalam pohon menggunakan fungsi insertNodeTree
        kategoriJawaban(P->root); // Memperbarui kategori jawaban setelah memasukkan data baru
    }
}

void traversalInOrder (addressTree rootTree) 
{
    if (rootTree != NULL) {
        traversalInOrder(rootTree->left);
        printf("%s ", rootTree->info);
        traversalInOrder(rootTree->right);
    }
}

void verifikasiJawaban (addressTree rootTree) 
{
	// Deklarasi dan Inisialisasi
    char pilihanJawaban[2];
    char *tandaTanya;
    bool sudahValid;
    infotype tempInfo;
    addressTree temp;
    addressTree queue[100];
    int front = -1, rear = -1;
    queue[++rear] = rootTree;

    while (front != rear) // JIka tidak ada lagi node yang bisa di proses maka program akan berhenti
    {
        temp = queue[++front]; // temp akan berisi nilai front kemudian nilai front akan ditingkatkan sebanyak satu
        if (temp->left != NULL) // JIka temp memiliki anak kiri maka anak kiri tersebut akan dimasukkan kedalam queue
            queue[++rear] = temp->left;
        if (temp->right != NULL) // JIka temp memiliki anak kanan maka anak kanan tersebut akan dimasukkan kedalam queue
            queue[++rear] = temp->right;

        if (temp->isJawaban == true) // Jika node merupakan jawaban
        {
            sudahValid = false;
            printf("\nKetik 'SELESAI' ketika anda sudah selesai.");
            printf("\nJawaban saat ini: %s", temp->info); // Menampilkan jawaban saat ini
            printf("\nApakah anda ingin menyimpan ini sebagai jawaban? (y/n): ");
            scanf("%s", pilihanJawaban);

            if (pilihanJawaban[0] == 'n' || pilihanJawaban[0] == 'N') // Jika pengguna memilih 'n' atau 'N' maka user akan diminta menginputkan sebuah pertanyaan
            {
                do
                {
                    printf("Silahkan anda tulis sebuah pertanyaan (Gunakan tanda '?'): ");
                    fflush(stdin);
                    fgets(tempInfo, sizeof(tempInfo), stdin);
                    tempInfo[strcspn(tempInfo, "\n")] = '\0';
                    tandaTanya = strchr(tempInfo, '?');

                    if (tandaTanya == NULL) // Jika tidak ditemukan tanda tanya dalam pertanyaan
                    {
                        printf("\nPertanyaan tidak valid, mohon input ulang kembali.\n\n");
                    } 
                    else // Jika ditemukan tanda tanya dalam pertanyaan
                    {
                        strcpy(temp->info, tempInfo); // Menyalin info yang baru ke dalam node
                        temp->isJawaban = false; // Menandai node tidak lagi sebagai jawaban
                        sudahValid = true;
                    }
                } while (!sudahValid); // Melakukan looping selama input pertanyaan tidak valid
            }
            else if (pilihanJawaban[0] == 'y' || pilihanJawaban[0] == 'Y') // Jika pengguna memilih 'y' atau 'Y'
            {
                continue; // Lanjut ke node berikutnya
            }
            else if (strcmp(strupr(pilihanJawaban), "SELESAI") == 0) // Jika pengguna memilih 'SELESAI'
            {
                break; // Keluar dari loop
            }
        }
    }
}






