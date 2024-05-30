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
            printf("\n\t\t\t\t\t\t\t\t\t\t\tValidasi saat ini: %s", temp->info);
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
            printf("\n\t\t\t\t\t\t\t\t\t\t\tValidasi saat ini: %s", temp->info);
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

bool periksaKompleksitasTopik(addressTree root) 
{
    // Deklarasi variabel
    addressQueue queue;
    addressTree temp;
    addressQueueNode current, next;

    // Inisialisasi variabel
    queue = buatQueue();
    i = 0;

    // Memeriksa apakah root adalah NULL
    if (root == NULL) 
	{
        free(queue); // Jika root kosong, bebaskan memori antrian dan kembalikan true
        return true;
    }

    Enqueue(queue, root); // Menambahkan root ke dalam antrian

    // Menggunakan BFS untuk memeriksa 32 node pertama
    while (!isEmpty(queue) && i < 32) 
	{
        temp = Dequeue(queue); // Mengambil node dari antrian untuk diperiksa

        if (temp->isJawaban) 
		{
            // Jika ditemukan jawaban dalam 32 node pertama, bebaskan memori antrian dan kembalikan false
            while (!isEmpty(queue)) 
			{
                Dequeue(queue); // Mengosongkan antrian
            }
            free(queue);
            return false;
        }

        // Menambahkan anak-anak dari node saat ini ke dalam antrian untuk diperiksa selanjutnya
        if (temp->left != NULL) 
		{
            Enqueue(queue, temp->left);
        }
        if (temp->right != NULL) 
		{
            Enqueue(queue, temp->right);
        }

        i++; // Menambah jumlah node yang telah diperiksa
    }

    // Membersihkan memori dari elemen antrian yang tersisa
    current = queue->front;
    while (current != NULL) 
	{
        next = current->next;
        free(current);
        current = next;
    }
    free(queue);

    return true; // Semua node dari root sampai node ke-32 adalah pertanyaan
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
        printf("\n\t\t\t\t\t\t\t\t\t\t\tGunakan tanda '?' jika merupakan sebuah pertanyaan.\n\t\t\t\t\t\t\t\t\t\t\tKetik 'SELESAI' ketika anda sudah selesai.\n\t\t\t\t\t\t\t\t\t\t\tValidasi awal: ");
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
    while (strcmp(strupr(temp_data), "SELESAI") != 0) 
	{
        // Menampilkan kedalaman pohon saat ini
        printf("\n\t\t\t\t\t\t\t\t\t\t\tKompleksitas topik saat ini: %d (minimal memiliki kompleksitas 6)\n", maxDepth(P->root));
        
        // Mencetak parent node yang belum memiliki anak
        printParent(P->root, &adaPertanyaan);
        
        // Jika tidak ada lagi pertanyaan yang bisa diisi, keluar dari loop
        if (adaPertanyaan == 1) 
		{
            printf("\n\t\t\t\t\t\t\t\t\t\t\tTopik sudah tidak memiliki pertanyaan yang bisa diisi.\n");
            // Jika kompleksitas tree masih kurang dari 6, beritahu pengguna untuk menggunakan fitur Tambah Node Tree
            if (!periksaKompleksitasTopik(P->root)) 
			{
		        printf("\n\t\t\t\t\t\t\t\t\t\t\tKompleksitas topik saat ini tidak direkomendasikan karena terdapat jawaban dalam 5 kompleksitas pertama.");
		        printf("\n\t\t\t\t\t\t\t\t\t\t\tDisarankan untuk menggunakan fitur Tambah Pertanyaan dan Jawaban untuk menambahkan lebih banyak pertanyaan.\n");
            }
            break;
        }
        
        // Input jawaban jika pertanyaan sudah tersedia
        printf("\n\t\t\t\t\t\t\t\t\t\t\tJika 'YA': ");
        fflush(stdin);
        fgets(data, sizeof(data), stdin);
        data[strcspn(data, "\n")] = '\0'; // Menghapus karakter newline dari data yang dimasukkan
        strcpy(temp_data, data); // Menyalin data ke variabel temp_data
        
        // Jika pengguna mengetik "SELESAI"
        if (strcmp(strupr(temp_data), "SELESAI") == 0) 
		{
			// Jika kompleksitas tree masih kurang dari 6, beritahu pengguna untuk menggunakan fitur Tambah Node Tree
            if (!periksaKompleksitasTopik(P->root)) 
			{
		        printf("\n\t\t\t\t\t\t\t\t\t\t\tKompleksitas topik saat ini tidak direkomendasikan karena terdapat jawaban dalam 5 kompleksitas pertama.");
		        printf("\n\t\t\t\t\t\t\t\t\t\t\tDisarankan untuk menggunakan fitur Tambah Pertanyaan dan Jawaban untuk menambahkan lebih banyak pertanyaan.\n");
            }
            break;
        }
        
        // Memasukkan jawaban "YA" ke dalam pohon dan menetapkan apakah jawaban "YA" itu merupakan kategori jawaban
        P->root = insertNodeTree(P->root, data);
        kategoriJawaban(P->root);
        
        // Input jawaban jika pertanyaan sudah tersedia
        printf("\t\t\t\t\t\t\t\t\t\t\tJika 'TIDAK': ");
        fflush(stdin);
        fgets(data, sizeof(data), stdin);
        data[strcspn(data, "\n")] = '\0'; // Menghapus karakter newline dari data yang dimasukkan
        strcpy(temp_data, data); // Menyalin data ke variabel temp_data
        
        // Jika pengguna mengetik "SELESAI", beritahu pengguna untuk mengisi kondisi jika "TIDAK"
        if (strcmp(strupr(temp_data), "SELESAI") == 0) 
		{
            printf("\n\t\t\t\t\t\t\t\t\t\t\tAnda belum mengisi kondisi jika 'TIDAK'\n");
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
		system("cls");
        printf("\n\t\t\t\t\t\t\t\t\t\t\tGagal membuat file.\n");
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

void verifikasiJawaban(addressTree rootTree) 
{
    // Deklarasi variabel
    char jawabanYangDicari[100];
    char pilihan[2];
    char *tandaTanya;
    bool sudahValid;
    bool jawabanDitemukan = false;
    char tempInfo[100];
    addressQueue queue;
    addressTree temp;

    // Menanyakan kepada pengguna apakah ingin mengubah jawaban menjadi pertanyaan
    printf("\n\t\t\t\t\t\t\t\t\t\t\tApakah anda ingin mengubah jawaban menjadi pertanyaan? (y/n): ");
    scanf("%s", pilihan);

    // Jika pengguna tidak ingin melakukan pengubahan
    if (pilihan[0] != 'y' && pilihan[0] != 'Y') 
	{
        return;
    }

    // Meminta input dari pengguna untuk jawaban yang ingin diedit
    printf("\n\t\t\t\t\t\t\t\t\t\t\tMasukkan jawaban yang ingin diedit: ");
    fflush(stdin);
    fgets(jawabanYangDicari, sizeof(jawabanYangDicari), stdin);
    jawabanYangDicari[strcspn(jawabanYangDicari, "\n")] = '\0';

    // Inisialisasi antrian dan memasukkan rootTree ke dalam antrian
    queue = buatQueue();
    Enqueue(queue, rootTree);

    // Melakukan pengulangan selama antrian tidak kosong
    while (!isEmpty(queue)) 
	{
        temp = Dequeue(queue); // Menghapus elemen pertama dari antrian

        // Memeriksa dan memasukkan anak kiri dan kanan dari node saat ini ke dalam antrian
        if (temp->left != NULL) 
		{
            Enqueue(queue, temp->left);
        }
        if (temp->right != NULL) 
		{
            Enqueue(queue, temp->right);
        }

        // Jika node saat ini merupakan jawaban yang dicari
        if (temp->isJawaban == true && strcmp(temp->info, jawabanYangDicari) == 0) 
		{
            jawabanDitemukan = true; // Menandakan bahwa jawaban ditemukan
            sudahValid = false; // Inisialisasi status validasi

            // Meminta input pertanyaan baru
            do 
			{
                printf("\n\t\t\t\t\t\t\t\t\t\t\tSilahkan anda tulis sebuah pertanyaan (Gunakan tanda '?'): ");
                fflush(stdin);
                fgets(tempInfo, sizeof(tempInfo), stdin);
                tempInfo[strcspn(tempInfo, "\n")] = '\0';
                tandaTanya = strchr(tempInfo, '?');
                if (tandaTanya == NULL) 
				{
                    printf("\n\t\t\t\t\t\t\t\t\t\t\tPertanyaan tidak valid, mohon input ulang kembali.\n\n");
                }
				else 
				{
                    strcpy(temp->info, tempInfo); // Mengganti info node dengan pertanyaan baru
                    temp->isJawaban = false; // Mengubah status node menjadi bukan jawaban
                    sudahValid = true; // Mengubah status validasi menjadi true
                }
            } while (!sudahValid); // Melakukan pengulangan hingga pertanyaan valid

            break; // Menghentikan pencarian setelah jawaban ditemukan dan diedit
        }
    }

    // Jika jawaban tidak ditemukan
    if (!jawabanDitemukan) 
	{
        printf("\n\t\t\t\t\t\t\t\t\t\t\tJawaban yang dicari tidak ditemukan dalam tree.\n");
    }

    // Membersihkan memori dari elemen antrian
    addressQueueNode current = queue->front;
    while (current != NULL) 
	{
        addressQueueNode next = current->next;
        free(current);
        current = next;
    }
    free(queue); // Membebaskan memori dari antrian
}
