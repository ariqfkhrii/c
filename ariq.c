#include "global.h"
#include "ariq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

addressTree buatNodeTree(infotype data) 
{
    // Mengalokasikan memori untuk sebuah node tree
    addressTree R = (addressTree)malloc(sizeof(Tree));

    // Mengecek apakah alokasi memori berhasil
    if (R == NULL) 
	{
        // Jika alokasi gagal, program akan membersihkan layar dan menampilkan pesan kesalahan
        system("cls");
        printf("Alokasi memori gagal.");
        printf("\n\nTekan apapun untuk keluar.");
        getchar();
        exit(1);
    } 
	else 
	{
        // Jika alokasi berhasil, mengisi data node dengan nilai yang diberikan
        strcpy(R->info, data);
        // Menginisialisasi pointer left dan right dengan NULL
        R->left = NULL;
        R->right = NULL;
        // Menandai bahwa node ini bukan node jawaban
        R->isJawaban = false;
    }
    
    // Mengembalikan alamat node Tree baru
    return R;
}


addressQueueNode buatNodeQueue(addressTree nodeTree) 
{
    // Mengalokasikan memori untuk sebuah node queue
    addressQueueNode nodeBaru = (addressQueueNode)malloc(sizeof(QueueNode));

    // Mengecek apakah alokasi memori berhasil
    if (nodeBaru == NULL) 
	{
        // Jika alokasi gagal, program akan membersihkan layar dan menampilkan pesan kesalahan
        system("cls");
        printf("Alokasi memori gagal.");
        printf("\n\nTekan apapun untuk keluar.");
        getchar();
        exit(1);
    }

    // Menginisialisasi node queue
    nodeBaru->data = nodeTree; // Mengisi data dengan node tree yang diberikan
    nodeBaru->next = NULL; // Mengatur pointer next ke NULL

    // Mengembalikan alamat node queue
    return nodeBaru;
}


addressQueue buatQueue() 
{
    // Mengalokasikan memori untuk sebuah queue
    addressQueue queue = (addressQueue)malloc(sizeof(Queue));

    // Mengecek apakah alokasi memori berhasil
    if (queue == NULL) 
	{
        // Jika alokasi gagal, program akan membersihkan layar dan menampilkan pesan kesalahan
        system("cls");
        printf("Alokasi memori gagal.");
        printf("\n\nTekan apapun untuk keluar.");
        getchar();
        exit(1);
    }

    // Menginisialisasi queue baru
    queue->front = queue->rear = NULL; // Mengatur pointer front dan rear ke NULL

    // Mengembalikan alamat queue
    return queue;
}


bool isEmpty(addressQueue queue) 
{
    // Mengecek apakah queue kosong dengan memeriksa apakah pointer front adalah NULL
    return (queue->front == NULL);
}


void Enqueue(addressQueue queue, addressTree nodeTree) 
{
    // Membuat node queue baru dengan node tree yang diberikan
    addressQueueNode nodeBaru = buatNodeQueue(nodeTree);

    // Mengecek apakah queue kosong
    if (isEmpty(queue)) 
	{
        // Jika queue kosong, atur front dan rear ke node baru
        queue->front = queue->rear = nodeBaru;
    } 
	else 
	{
        // Jika queue tidak kosong, tambahkan node baru di belakang queue
        queue->rear->next = nodeBaru; // Hubungkan node baru dengan node terakhir saat ini
        queue->rear = nodeBaru; // Perbarui rear ke node baru
    }
}


addressTree Dequeue(addressQueue queue) 
{
    // Mengecek apakah queue kosong
    if (isEmpty(queue)) 
	{
        // Jika queue kosong, membersihkan layar dan menampilkan pesan kesalahan
        system("cls");
        printf("Queue kosong.");
        printf("\n\nTekan apapun untuk keluar.");
        getchar();
        exit(1);
    }

    // Menyimpan node yang akan dihapus
    addressQueueNode temp = queue->front;
    
    // Menyimpan data dari node yang akan dihapus
    addressTree nodeTree = temp->data;
    
    // Memperbarui front ke node berikutnya
    queue->front = queue->front->next;
    
    // Jika front menjadi NULL, berarti queue sekarang kosong, jadi perbarui rear ke NULL
    if (queue->front == NULL) 
	{
        queue->rear = NULL;
    }
    
    // Membebaskan memori node yang dihapus
    free(temp);
    
    // Mengembalikan data dari node yang dihapus
    return nodeTree;
}


addressTree insertNodeTree(addressTree rootTree, infotype data) 
{
    // Jika root tree kosong, buat node baru dan jadikan sebagai root
    if (rootTree == NULL) 
	{
        rootTree = buatNodeTree(data);
        return rootTree;
    }

    // Inisialisasi queue untuk traversal level-order
    addressQueue queue = buatQueue();
    Enqueue(queue, rootTree);

    // Traversal level-order
    while (!isEmpty(queue)) 
	{
        // Ambil node pertama dari queue
        addressTree temp = Dequeue(queue);

        // Jika node ini adalah jawaban, lanjutkan ke node berikutnya
        if (temp->isJawaban == true) 
		{
            continue;
        }

        // Jika anak kiri dari node ini kosong, tambahkan node baru sebagai anak kiri
        if (temp->left == NULL) 
		{
            temp->left = buatNodeTree(data);
            free(queue); // Bebaskan memori yang dialokasikan untuk queue
            return rootTree; // Kembalikan rootTree setelah penambahan node baru
        }
		else 
		{
            // Jika anak kiri tidak kosong, tambahkan ke dalam queue
            Enqueue(queue, temp->left);
        }

        // Jika anak kanan dari node ini kosong, tambahkan node baru sebagai anak kanan
        if (temp->right == NULL) 
		{
            temp->right = buatNodeTree(data);
            free(queue); // Bebaskan memori yang dialokasikan untuk queue
            return rootTree; // Kembalikan rootTree setelah penambahan node baru
        } 
		else 
		{
            // Jika anak kanan tidak kosong, tambahkan ke dalam queue
            Enqueue(queue, temp->right);
        }
    }

    // Bebaskan memori yang dialokasikan untuk queue setelah traversal selesai
    free(queue);
    return rootTree; // Kembalikan rootTree
}

int maxDepth(addressTree rootTree) 
{
    // Jika rootTree kosong, maka kedalaman tree adalah 0
    if (rootTree == NULL)
        return 0;
    else 
	{
        // Mencari kedalaman subtree dari anak kiri
        int lDepth = maxDepth(rootTree->left);
        // Mencari kedalaman subtree dari anak kanan
        int rDepth = maxDepth(rootTree->right);
        
        // Membandingkan kedalaman subtree dari anak kiri dan anak kanan
        if (lDepth > rDepth)
            // Jika kedalaman subtree dari anak kiri lebih besar, tambahkan 1 dan kembalikan
            return (lDepth + 1);
        else
            // Jika kedalaman subtree dari anak kanan lebih besar atau sama, tambahkan 1 dan kembalikan
            return (rDepth + 1);
    }
}


void kategoriJawaban(addressTree rootTree)
{
    // Jika rootTree kosong, maka tidak perlu dilakukan pengecekan kategori jawaban
    if (rootTree == NULL) 
	{
        return;
    }
    
    // Jika root tree hanya memiliki satu node dan tidak memiliki anak, maka periksa apakah node tersebut merupakan jawaban
    if (rootTree->left == NULL && rootTree->right == NULL) 
	{
        // Mencari tanda tanya (?) dalam info node
        char *tandaTanya = strchr(rootTree->info, '?');
        
        // Jika tidak ditemukan tanda tanya, tandai node tersebut sebagai jawaban
        if (tandaTanya == NULL) 
		{
            rootTree->isJawaban = true;
            return;
        }
    }
    
    // Rekursi ke anak kiri dan anak kanan untuk melakukan pengecekan kategori jawaban
    kategoriJawaban(rootTree->left);
    kategoriJawaban(rootTree->right);
}


void printParent(addressTree rootTree, int *adaPertanyaan) 
{
    // Jika rootTree kosong, maka tidak perlu melakukan pencetakan
    if (rootTree == NULL) 
	{
        return;
    }
    
    // Inisialisasi queue untuk menyimpan node yang akan dicek
    addressQueue queue = buatQueue();
    
    // Tambahkan root tree ke dalam queue
    Enqueue(queue, rootTree);
    
    // Looping untuk memeriksa setiap node dalam queue
    while (!isEmpty(queue)) 
	{
        addressTree temp = Dequeue(queue); // Ambil node pertama dari queue
        
        // Jika node merupakan jawaban, lanjutkan ke node berikutnya
        if (temp->isJawaban == true) 
		{
            continue;
        }
        
        // Jika anak kiri tidak kosong, tambahkan ke dalam queue
        if (temp->left != NULL) 
		{
            Enqueue(queue, temp->left);
        } 
		else 
		{
            // Jika anak kiri kosong, cetak info node dan tandai bahwa masih ada pertanyaan
            printf("\nValidasi saat ini: %s", temp->info);
            *adaPertanyaan = 0;
            break;
        }
        
        // Jika anak kanan tidak kosong, tambahkan ke dalam queue
        if (temp->right != NULL) 
		{
            Enqueue(queue, temp->right);
        } 
		else 
		{
            // Jika anak kanan kosong, cetak info node dan tandai bahwa masih ada pertanyaan
            printf("\nValidasi saat ini: %s", temp->info);
            *adaPertanyaan = 0;
            break;
        }
    }

    // Bebaskan memori yang dialokasikan untuk queue dan setiap node
    addressQueueNode current = queue->front;
    while (current != NULL) 
	{
        addressQueueNode next = current->next;
        free(current);
        current = next;
    }
    free(queue);
}


void buatTree(addressList P)
{
    // Inisialisasi variabel
    int adaPertanyaan = 1;
    infotype data, temp_data;

    // Jika root dari P adalah NULL, artinya pohon belum dibuat
    if (P->root == NULL) 
	{
        // Meminta input pertama dari pengguna untuk membuat root pohon
        printf("Gunakan tanda '?' jika merupakan sebuah pertanyaan.\nKetik 'SELESAI' ketika anda sudah selesai.\nValidasi awal: ");
        fflush(stdin);
        fgets(data, sizeof(data), stdin);
        data[strcspn(data, "\n")] = '\0'; // Menghapus karakter newline dari data yang dimasukkan
        strcpy(temp_data, data); // Menyalin data ke variabel temp_data
        if (strcmp(strupr(temp_data), "SELESAI") == 0) 
		{
            return; // Jika pengguna langsung mengetik "SELESAI", maka keluar dari fungsi
        }
        // Memasukkan data ke dalam root pohon dan menetapkan kategori jawaban
        P->root = insertNodeTree(P->root, data);
        kategoriJawaban(P->root);
    }
    
    // Melakukan input data dan pembuatan pohon selama pengguna belum mengetik "SELESAI" dan kedalaman pohon masih kurang dari 6
    while (strcmp(strupr(temp_data), "SELESAI") != 0 && maxDepth(P->root) < 6) 
	{
        // Menampilkan kedalaman pohon saat ini
        printf("Kedalaman tree saat ini: %d (minimal memiliki kedalaman 6)\n", maxDepth(P->root));
        
        // Mencetak parent node yang belum memiliki anak
        printParent(P->root, &adaPertanyaan);
        
        // Jika tidak ada lagi pertanyaan yang bisa diisi, keluar dari loop
        if (adaPertanyaan == 1) 
		{
            printf("\nTree sudah tidak memiliki pertanyaan yang bisa diisi.");
            // Jika kedalaman pohon masih kurang dari atau sama dengan 6, beritahu pengguna untuk menggunakan fitur Tambah Node Tree
            if (maxDepth(P->root) <= 6) 
			{
                printf("\nTree tidak memenuhi syarat memiliki kedalaman 6, silahkan anda gunakan fitur Tambah Node Tree.");
            }
            break;
        }
        
        // Input jawaban jika pertanyaan sudah tersedia
        printf("\nJika 'YA': ");
        fflush(stdin);
        fgets(data, sizeof(data), stdin);
        data[strcspn(data, "\n")] = '\0'; // Menghapus karakter newline dari data yang dimasukkan
        strcpy(temp_data, data); // Menyalin data ke variabel temp_data
        
        // Jika pengguna mengetik "SELESAI", cek apakah kedalaman pohon sudah mencukupi
        if (strcmp(strupr(temp_data), "SELESAI") == 0) 
		{
            if (maxDepth(P->root) <= 6) 
			{
                printf("\nAnda belum memenuhi syarat memiliki kedalaman 6.\n");
                continue;
            } 
			else 
			{
                break; // Jika kedalaman sudah mencukupi, keluar dari loop
            }
        }
        
        // Memasukkan jawaban "YA" ke dalam pohon dan menetapkan apakah jawaban "YA" itu merupakan kategori jawaban
        P->root = insertNodeTree(P->root, data);
        kategoriJawaban(P->root);
        
        // Input jawaban jika pertanyaan sudah tersedia
        printf("Jika 'TIDAK': ");
        fflush(stdin);
        fgets(data, sizeof(data), stdin);
        data[strcspn(data, "\n")] = '\0'; // Menghapus karakter newline dari data yang dimasukkan
        strcpy(temp_data, data); // Menyalin data ke variabel temp_data
        
        // Jika pengguna mengetik "SELESAI", beritahu pengguna untuk mengisi kondisi jika "TIDAK"
        if (strcmp(strupr(temp_data), "SELESAI") == 0) 
		{
            printf("\nAnda belum mengisi kondisi jika 'TIDAK'\n");
            continue;
        }
        
        // Memasukkan jawaban "TIDAK" ke dalam pohon dan menetapkan apakah jawaban "TIDAK" itu merupakan kategori jawaban
        P->root = insertNodeTree(P->root, data);
        kategoriJawaban(P->root);
        
        // Atur adaPertanyaan kembali ke 1 untuk mengecek pertanyaan berikutnya
        adaPertanyaan = 1;
    }
}

void simpanTree(addressList P) 
{
    // Inisialisasi variabel
    char folder[] = "Topik"; // Nama folder untuk menyimpan file
    char filepath[100]; // Nama file beserta path
    addressQueue queue = buatQueue(); // Membuat antrian baru
    addressTree temp;
    addressTree rootTree = P->root;

    // Jika rootTree adalah NULL, maka tidak ada yang perlu disimpan
    if (rootTree == NULL) 
	{
        return;
    }

    // Memasukkan root tree ke dalam antrian
    Enqueue(queue, rootTree);

    // Membuat path file
    sprintf(filepath, "%s/%s.txt", folder, P->topik);

    // Membuka file untuk ditulis
    FILE *file = fopen(filepath, "w");
    if (file == NULL) 
	{
        printf("Gagal membuat file.\n");
        exit(1);
    }

    // Menyimpan data pohon ke dalam file
    while (!isEmpty(queue)) 
	{
        temp = Dequeue(queue); // Mengambil elemen pertama dari antrian

        // Menulis informasi node ke dalam file
        fprintf(file, "%s\n", temp->info);

        // Jika anak kiri tidak kosong, masukkan ke dalam antrian
        if (temp->left != NULL) 
		{
            Enqueue(queue, temp->left);
        }
        
        // Jika anak kanan tidak kosong, masukkan ke dalam antrian
        if (temp->right != NULL) 
		{
            Enqueue(queue, temp->right);
        }
    }

    // Menutup file setelah selesai menulis
    fclose(file);

    // Membebaskan memori yang dialokasikan untuk antrian
    addressQueueNode current = queue->front;
    while (current != NULL) 
	{
        addressQueueNode next = current->next;
        free(current);
        current = next;
    }
    free(queue);
}

void bacaFileTree(addressList P) 
{
    // Deklarasi variabel
    infotype data;
    char folder[] = "Topik"; // Nama folder penyimpanan file
    char filepath[100]; // Path file
    
    // Membuat path file
    sprintf(filepath, "%s/%s.txt", folder, P->topik);
    
    // Membuka file untuk dibaca
    FILE *file = fopen(filepath, "r");
        
    // Membaca setiap baris pada file
    while (fscanf(file, "%[^\n]\n", data) == 1) 
	{
        // Memasukkan data ke dalam pohon
        P->root = insertNodeTree(P->root, data);
        // Mengkategorikan jawaban dalam pohon
        kategoriJawaban(P->root);
    }
    
    // Menutup file setelah selesai membaca
    fclose(file);
}

void traversalInOrder(addressTree rootTree) {
    if (rootTree != NULL) {
        traversalInOrder(rootTree->left);
        printf("%s ", rootTree->info);
        traversalInOrder(rootTree->right);
    }
}

void verifikasiJawaban(addressTree rootTree) {
    // Deklarasi variabel
    char pilihanJawaban[2];
    char *tandaTanya;
    bool sudahValid;
    infotype tempInfo;
    addressQueue queue = buatQueue();
    addressTree temp;

    // Memasukkan rootTree ke dalam antrian
    Enqueue(queue, rootTree);

    // Melakukan pengulangan selama antrian tidak kosong
    while (!isEmpty(queue)) {
        temp = Dequeue(queue); // Menghapus elemen pertama dari antrian

        // Memeriksa dan memasukkan anak kiri dan kanan dari node saat ini ke dalam antrian
        if (temp->left != NULL) {
            Enqueue(queue, temp->left);
        }
        if (temp->right != NULL) {
            Enqueue(queue, temp->right);
        }

        // Jika node saat ini merupakan jawaban
        if (temp->isJawaban == true) {
            sudahValid = false; // Inisialisasi status validasi
            printf("\nKetik 'SELESAI' ketika anda sudah selesai.");
            printf("\nJawaban saat ini: %s", temp->info);
            printf("\nApakah anda ingin menyimpan ini sebagai jawaban? (y/n): ");
            scanf("%s", pilihanJawaban);

            // Jika jawaban tidak disimpan
            if (pilihanJawaban[0] == 'n' || pilihanJawaban[0] == 'N') {
                do {
                    printf("Silahkan anda tulis sebuah pertanyaan (Gunakan tanda '?'): ");
                    fflush(stdin);
                    fgets(tempInfo, sizeof(tempInfo), stdin);
                    tempInfo[strcspn(tempInfo, "\n")] = '\0';
                    tandaTanya = strchr(tempInfo, '?');
                    if (tandaTanya == NULL) {
                        printf("\nPertanyaan tidak valid, mohon input ulang kembali.\n\n");
                    } else {
                        strcpy(temp->info, tempInfo); // Mengganti info node dengan pertanyaan baru
                        temp->isJawaban = false; // Mengubah status node menjadi bukan jawaban
                        sudahValid = true; // Mengubah status validasi menjadi true
                    }
                } while (!sudahValid); // Melakukan pengulangan hingga pertanyaan valid
            } else if (pilihanJawaban[0] == 'y' || pilihanJawaban[0] == 'Y') {
                continue; // Melanjutkan ke node berikutnya jika jawaban disimpan
            } else if (strcmp(strupr(pilihanJawaban), "SELESAI") == 0) {
                break; // Menghentikan verifikasi jika user memilih selesai
            }
        }
    }

    // Membersihkan memori dari elemen antrian
    addressQueueNode current = queue->front;
    while (current != NULL) {
        addressQueueNode next = current->next;
        free(current);
        current = next;
    }
    free(queue); // Membebaskan memori dari antrian
}
