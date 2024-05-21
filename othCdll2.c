#include <stdio.h>
#include <stdlib.h>

////kode ini mendefinisikan blok penyusun (Node) untuk daftar tautan ganda
typedef struct Node {
    int data;
    struct Node *next; 
    struct Node *prev;
} Node;
//menginisialisasi dua pointer (head dan tail) untuk mengelola node pertama dan terakhir dalam daftar
Node *head = NULL;
Node *tail = NULL;

//mengalokasikan memori untuk node baru
Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node)); //menyimpan node baru
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertNode(int data) {
    Node *newNode = createNode(data); //membuat node baru

    if (head == NULL) {  //mengatur head & tail ke node baru
        head = newNode;
        tail = newNode;
        newNode->next = newNode; //menunjuk ke diri sendiri (ganda melingkar)
        newNode->prev = newNode;
    } else {
        tail->next = newNode; ////untuk menghubungkan node baru di akhir
        newNode->prev = tail;
        newNode->next = head; //untuk mempertahankan struktur melingkar
        head->prev = newNode;
        tail = newNode; // untuk menunjuk ke node yang baru dimasukkan
    }
}

void printList() { //memeriksa dfatar kosong
    Node *curr = head;
    if (curr == NULL) {
        printf("List is empty\n");
        return;
    }

    do { //mencetak alamat node
        printf("Address: %016lx, Data: %d\n", (unsigned long)curr, curr->data);
        curr = curr->next;
    } while (curr != head);
}

void swapNodes(Node *a, Node *b) { //menukar posisi dua node
    if (a->next == b) {  
        a->next = b->next;
        b->prev = a->prev;
        a->prev->next = b;
        b->next->prev = a;
        b->next = a;
        a->prev = b;
    } else {
        Node *tempNext = a->next;
        Node *tempPrev = a->prev; //pointer sementara untuk menyimpan koneksi asli a dan b
        a->next = b->next;
        a->prev = b->prev;
        b->next = tempNext;
        b->prev = tempPrev;
        a->next->prev = a;
        a->prev->next = a;
        b->next->prev = b;
        b->prev->next = b;
    }
 // head/tail menunjuk a/b sebelum pertukaran dan memperbarui untuk menunjuk ke node baru yang benar setelah pertukaran
    if (head == a) {
        head = b;
    } else if (head == b) {
        head = a;
    }

    if (tail == a) {
        tail = b;
    } else if (tail == b) {
        tail = a;
    }
}
//pemeriksaan daftar kosong
void sortList() { 
    if (head == NULL) return; //jika kosong langsung kembali

    int swapped;
    Node *curr;

// perbandingan dan pertukaran
    do {
        swapped = 0; //untuk melacak apakah ada pertukaran yang terjadi pada pass ini
        curr = head; //menunjuk ke nood yang dipertimbangkan

        do {
            Node *nextNode = curr->next;
            if (curr->data > nextNode->data) { // tanda lebih besar dan harus ditukar posisi curr dan nextNode
                swapNodes(curr, nextNode);
                swapped = 1; //pertukaran terjadi pada pass sebelumnya
            } else {
                curr = nextNode;
            }
        } while (curr != tail);
    } while (swapped);
}

int main() {
    int n;
    printf("Masukkan jumlah data: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int data;
        printf("Masukkan data ke-%d: ", i + 1);
        scanf("%d", &data);
        insertNode(data);
    }

    printf("\nList sebelum pengurutan:\n");
    printList();

    sortList();

    printf("\nList setelah pengurutan:\n");
    printList();

    return 0;
}