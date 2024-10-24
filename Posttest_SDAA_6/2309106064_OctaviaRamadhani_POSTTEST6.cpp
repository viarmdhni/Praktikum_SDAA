#include <iostream>
#include <string>
#include <cmath>
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
void top(Node* top);
void quickSort(Node** head);
void shellSort(Node** head);
Node* partition(Node* head, Node* end, Node** newHead, Node** newEnd);
Node* getTail(Node* head);
int getCount(Node* head);
void inisialisasiData();
int fibonacciSearch(Node* head, int x);
int jumpSearch(Node* head, int x);
void boyerMooreSearch(Node* head, string pattern);
void searchMenu(Node* front);

void inisialisasiData() {
    Produk dataProduk[] = {
        {"serum", "wardah", 150000, 25},
        {"moisturizer", "skintific", 130000, 40},
        {"sunscreen", "facetology", 90000, 30},
        {"facial Wash", "wardah", 50000, 50},
        {"toner", "avoskin", 130000, 45}
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
        if (cur->data.merk < pivot->data.merk) {
            if (*newHead == nullptr) *newHead = cur;
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

    if (*newHead == nullptr) *newHead = pivot;

    *newEnd = tail;

    return pivot;
}

Node* getTail(Node* head) {
    while (head != nullptr && head->next != nullptr) {
        head = head->next;
    }
    return head;
}

Node* quickSortUtil(Node* head, Node* end) {
    if (!head || head == end) return head;

    Node* newHead = nullptr;
    Node* newEnd = nullptr;

    Node* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        Node* temp = newHead;
        while (temp->next != pivot) temp = temp->next;
        temp->next = nullptr;

        newHead = quickSortUtil(newHead, temp);

        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortUtil(pivot->next, newEnd);

    return newHead;
}

void quickSort(Node** head) {
    *head = quickSortUtil(*head, getTail(*head));
}

int getCount(Node* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

void shellSort(Node** head) {
    int n = getCount(*head);
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Node* temp = *head;
            Node* gapNode = *head;

            for (int j = 0; j < i; j++) {
                temp = temp->next;
            }
            for (int j = 0; j < i - gap; j++) {
                gapNode = gapNode->next;
            }

            if (temp->data.merk > gapNode->data.merk) {
                Produk tempData = temp->data;
                temp->data = gapNode->data;
                gapNode->data = tempData;
            }
        }
    }
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
        cout << "Merk: " << temp->data.merk << "\n";
        cout << "Jenis Produk: " << temp->data.nama << "\n";
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


int fibonacciSearch(Node* head, int x) {
    int arr[100];
    int n = 0;
    Node* temp = head;
    while (temp != nullptr) {
        arr[n++] = temp->data.harga;
        temp = temp->next;
    }
    
    int fibM2 = 0;
    int fibM1 = 1;
    int fibM = fibM2 + fibM1; 
    
    while (fibM < n) {
        fibM2 = fibM1;
        fibM1 = fibM;
        fibM = fibM2 + fibM1;
    }
    
    int offset = -1; 
    
    while (fibM > 1) {
        int i = min(offset + fibM2, n - 1);
        
        if (arr[i] < x) {
            fibM = fibM1;
            fibM1 = fibM2;
            fibM2 = fibM - fibM1;
            offset = i;
        } else if (arr[i] > x) {
            fibM = fibM2;
            fibM1 = fibM1 - fibM2;
            fibM2 = fibM - fibM1;
        } else {
            return i;
        }
    }

    if (fibM1 && arr[offset + 1] == x)
        return offset + 1;
    
    return -1; 
}

int jumpSearch(Node* head, int x) {
    int arr[100];
    int n = 0;
    Node* temp = head;
    while (temp != nullptr) {
        arr[n++] = temp->data.jumlah_stok;
        temp = temp->next;
    }
    
    int step = sqrt(n);
    int prev = 0;
    
    while (arr[min(step, n) - 1] < x) {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }
    
    while (arr[prev] < x) {
        prev++;
        if (prev == min(step, n))
            return -1;
    }
    
    if (arr[prev] == x) {
        return prev; 
    }
    
    return -1; 
}

void boyerMooreSearch(Node* head, string pattern) {
    string arr[100]; 
    int n = 0;
    Node* temp = head;
    while (temp != nullptr) {
        arr[n++] = temp->data.nama;
        temp = temp->next;
    }

    int m = pattern.length();
    for (int i = 0; i < n; i++) {
        size_t found = arr[i].find(pattern);
        if (found != string::npos) {
            cout << "Produk ditemukan:\n";
            cout << "Nama: " << arr[i] << endl;
            cout << "Merk: " << head->data.merk << endl;
            cout << "Harga: " << head->data.harga << endl;
            cout << "Stok: " << head->data.jumlah_stok << endl;
            return;
        }
    }
    cout << "Produk dengan nama \"" << pattern << "\" tidak ditemukan.\n";
}

void searchMenu(Node* front) {
    int pilihan;
    cout << "\nMenu Pencarian:\n";
    cout << "1. Cari berdasarkan harga\n";
    cout << "2. Cari berdasarkan stok\n";
    cout << "3. Cari berdasarkan nama\n";
    cout << "Pilihan: ";
    cin >> pilihan;
    
    switch (pilihan) {
        case 1: {
            int harga;
            cout << "Masukkan harga yang dicari: ";
            cin >> harga;
            int result = fibonacciSearch(front, harga);
            if (result != -1) {
                Node* temp = front;
                for (int i = 0; i < result; i++) {
                    temp = temp->next;
                }
                cout << "\nProduk ditemukan:\n";
                cout << "Nama: " << temp->data.nama << endl;
                cout << "Merk: " << temp->data.merk << endl;
                cout << "Harga: " << temp->data.harga << endl;
                cout << "Stok: " << temp->data.jumlah_stok << endl;
            } else {
                cout << "Produk dengan harga tersebut tidak ditemukan.\n";
            }
            break;
        }
        case 2: {
            int stok;
            cout << "Masukkan jumlah stok yang dicari: ";
            cin >> stok;
            int result = jumpSearch(front, stok);
            if (result != -1) {
                Node* temp = front;
                for (int i = 0; i < result; i++) {
                    temp = temp->next;
                }
                cout << "\nProduk ditemukan:\n";
                cout << "Nama: " << temp->data.nama << endl;
                cout << "Merk: " << temp->data.merk << endl;
                cout << "Harga: " << temp->data.harga << endl;
                cout << "Stok: " << temp->data.jumlah_stok << endl;
            } else {
                cout << "Produk dengan stok tersebut tidak ditemukan.\n";
            }
            break;
        }
        case 3: {
            string nama;
            cin.ignore();
            cout << "Masukkan jenis produk yang dicari: ";
            getline(cin, nama);
            boyerMooreSearch(front, nama);
            break;
        }
        default:
            cout << "Pilihan tidak valid.\n";
    }
}

int main() {
    inisialisasiData();
    int pilih;

    do {
        cout << "\nSistem Antrian Pendataan Produk Skincare\n";
        cout << "1. Tambah Produk\n";
        cout << "2. Tampilkan Produk\n";
        cout << "3. Update Stok\n";
        cout << "4. Hapus Produk Teratas\n";
        cout << "5. Lihat Produk Teratas\n";
        cout << "6. Cari\n";
        cout << "7. Keluar\n";
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
                cout << "1. Tampilkan secara ascending \n2. Tampilkan secara descending\nPilihan anda :\n";
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
                searchMenu(FRONT);
                break;
            case 7: 
                cout << "Terima kasih telah menggunakan sistem ini.\n"; 
                break;
            default: 
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
        
    } while (pilih != 7);

    while (FRONT != nullptr) {
        Node* temp = FRONT;
        FRONT = FRONT->next;
        delete temp;
    }

    return 0;
}