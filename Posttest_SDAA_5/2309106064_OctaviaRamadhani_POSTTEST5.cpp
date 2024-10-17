#include <iostream>
#include <string>
using namespace std;

struct Produk {
    string nama;
    string merk;
    int harga;
    int jumlah_stok;
};

struct Node {
    Produk data;
    Node* next;
};

Node* FRONT = nullptr;
Node* REAR = nullptr;
int jumlahproduk = 0;

Node* createNode();
void display(Node* front);
void enqueue(Node** front, Node** rear);
void dequeue(Node** front);
void updatestok(Node* front);
void peek(Node* front);
void quickSort(Node** head);
void shellSort(Node** head);
Node* partition(Node* head, Node* end, Node** newHead, Node** newEnd);
Node* getTail(Node* head);
int getCount(Node* head);

void inisialisasiData() {
    Produk dataProduk[] = {
        {"serum", "wardah", 150000, 25},
        {"moisturizer", "skintific", 130000, 40},
        {"sunscreen", "facetology", 90000, 30},
        {"facial Wash", "wardah", 50000, 50},
        {"toner", "avoskin", 120000, 45}
    };

    int data = sizeof(dataProduk) / sizeof(dataProduk[0]);

    for (int i = 0; i < data; i++) {
        Node* newNode = new Node();
        newNode->data = dataProduk[i];
        newNode->next = nullptr;

        if (REAR == nullptr) {
            FRONT = REAR = newNode;
        } else {
            REAR->next = newNode;
            REAR = newNode;
        }
        jumlahproduk++;
    }
}

Node* partition(Node* head, Node* end, Node** newHead, Node** newEnd) {
    Node* pivot = end;
    Node* prev = nullptr, * cur = head, * tail = pivot;

    while (cur != pivot) {
        if (cur->data.nama < pivot->data.nama) {
            if ((*newHead) == nullptr) (*newHead) = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev) prev->next = cur->next;
            Node* temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if ((*newHead) == nullptr) (*newHead) = pivot;

    *newEnd = tail;

    return pivot;
}

Node* getTail(Node* head) {
    while (head != nullptr && head->next != nullptr) {
        head = head->next;
    }
    return head;
}

Node* quickSortUtil(Node* head) {
    if (!head || !head->next) return head;

    Node* newHead = nullptr;
    Node* newEnd = nullptr;

    Node* pivot = partition(head, getTail(head), &newHead, &newEnd);

    if (newHead != pivot) {
        Node* temp = newHead;
        while (temp->next != pivot) temp = temp->next;
        temp->next = nullptr;

        newHead = quickSortUtil(newHead);

        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortUtil(pivot->next);

    return newHead;
}

void quickSort(Node** head) {
    *head = quickSortUtil(*head);
}

void shellSort(Node** head) {
    int n = getCount(*head);
    Node* h = *head;

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Node* temp = h;
            Node* prev = nullptr;

            for (int j = 0; j < i; j++) {
                prev = temp;
                temp = temp->next;
            }
            Node* gapNode = h;
            for (int j = 0; j < i - gap; j++) {
                gapNode = gapNode->next;
            }

            if (temp && gapNode && temp->data.nama > gapNode->data.nama) {
                if (prev) prev->next = temp->next;

                if (temp == *head) {
                    *head = gapNode;
                } else {
                    temp->next = gapNode->next;
                    gapNode->next = temp;
                }
            }
        }
    }
}


int getCount(Node* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

Node* createNode() {
    Node* newNode = new Node();
    cin.ignore();
    
    cout << "Masukkan nama produk: ";
    getline(cin, newNode->data.nama);

    cout << "Masukkan merk produk: ";
    getline(cin, newNode->data.merk);

    cout << "Masukkan harga produk: ";
    while (!(cin >> newNode->data.harga)) {
        cout << "Input tidak valid. Harap masukkan angka.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Masukkan harga produk: ";
    }

    cout << "Masukkan jumlah stok: ";
    while (!(cin >> newNode->data.jumlah_stok)) {
        cout << "Input tidak valid. Harap masukkan angka.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Masukkan jumlah stok: ";
    }

    newNode->next = nullptr;
    return newNode;
}

void display(Node* front) {
    if (front == nullptr) {
        cout << "Antrian produk kosong.\n";
        return;
    }

    cout << "Daftar Produk:\n";
    Node* temp = front;
    int i = 1;
    while (temp != nullptr) {
        cout << "Produk " << i << ":\n";
        cout << "Nama: " << temp->data.nama << "\n";
        cout << "Merk: " << temp->data.merk << "\n";
        cout << "Harga: " << temp->data.harga << "\n";
        cout << "Jumlah Stok: " << temp->data.jumlah_stok << "\n";
        cout << "-----------------------------\n";
        temp = temp->next;
        i++;
    }
}

void enqueue(Node** front, Node** rear) {
    Node* newNode = createNode();
    if (*rear == nullptr) {
        *front = *rear = newNode;
    } else {
        (*rear)->next = newNode;
        *rear = newNode;
    }
    jumlahproduk++;
    cout << "Produk berhasil ditambahkan ke antrian.\n";
}

void dequeue(Node** front) {
    if (*front == nullptr) {
        cout << "Antrian produk kosong.\n";
        return;
    }
    Node* temp = *front;
    *front = (*front)->next;
    if (*front == nullptr) {
        REAR = nullptr;
    }
    cout << "Produk " << temp->data.nama << " telah dihapus dari antrian.\n";
    delete temp;
    jumlahproduk--;
}

void updatestok(Node* front) {
    if (front == nullptr) {
        cout << "Antrian produk kosong.\n";
        return;
    }

    string update;
    cin.ignore();
    cout << "Masukkan nama produk yang ingin diupdate: ";
    getline(cin, update);

    Node* temp = front;
    while (temp != nullptr) {
        if (temp->data.nama == update) { 
            cout << "Jumlah stok saat ini: " << temp->data.jumlah_stok << "\n";
            cout << "Masukkan jumlah stok yang baru: ";
            
            while (!(cin >> temp->data.jumlah_stok)) {
                cout << "Input tidak valid. Harap masukkan angka.\n";
                cin.clear();
                cin.ignore('\n');
                cout << "Masukkan jumlah stok yang baru: ";
            }
            
            cout << "Stok berhasil diupdate.\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Produk tidak ditemukan.\n";
}

void top(Node* top) {
    if (top == nullptr) {
        cout << "Stack produk kosong.\n";
        return;
    }
    cout << "\nProduk teratas:\n";
    cout << "Nama: " << top->data.nama << "\n";
    cout << "Merk: " << top->data.merk << "\n";
    cout << "Harga: " << top->data.harga << "\n";
    cout << "Jumlah Stok: " << top->data.jumlah_stok << "\n";
}


int main() {
    inisialisasiData();
    int pilih;

    do {
        cout << "\nSistem Antrian Pendataan Produk Skincare\n";
        cout << "1. Tambah Produk\n";
        cout << "2. Tampilkan Produk\n";
        cout << "3. Update Stok\n";
        cout << "4. Hapus Produk\n";
        cout << "5. Lihat Produk Teratas\n";
        cout << "6. Keluar\n";
        cout << "Pilih Menu: ";
        cin >> pilih;

        if (cin.fail()) {
            cout << "Input tidak valid. Harap masukkan angka.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (pilih) {
            case 1: 
                enqueue(&FRONT, &REAR);
                break;
            case 2: 
                int sort;
                cout << "1. Tampilkan secara ascending \n2. Tampilkan secara descending\n";
                cin.ignore();
                cin >> sort;

                if (sort == 1) {
                    quickSort(&FRONT);
                    cout << "Produk secara ascending :\n";
                    display(FRONT); 
                }
                else if (sort == 2) {
                    shellSort(&FRONT);
                    cout << "Produk secara descending :\n";
                    display(FRONT);
                }
                break;
            case 3: 
                updatestok(FRONT); 
                break;
            case 4: 
                dequeue(&FRONT); 
                break;
            case 5: 
                top(FRONT); 
                break;
            case 6: 
                cout << "Terima kasih telah menggunakan sistem ini.\n"; 
                break;
            default: 
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
        
    } while (pilih != 6);

    while (FRONT != nullptr) {
        Node* temp = FRONT;
        FRONT = FRONT->next;
        delete temp;
    }

    return 0;
}