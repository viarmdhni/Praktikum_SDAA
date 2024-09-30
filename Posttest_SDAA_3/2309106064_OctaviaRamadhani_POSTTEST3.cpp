#include <iostream>
#include <string>
using namespace std;

struct Produk {
    string nama;
    string merk;
    int harga;
    int jumlah_stok;
    Produk *next;
};

Produk *head = nullptr;
int jumlahproduk = 0;

void data() {
    Produk dataProduk[] = {
        {"serum", "wardah", 150000, 25},
        {"moisturizer", "skintific", 130000, 40},
        {"sunscreen", "facetology", 90000, 30},
        {"facial Wash", "wardah", 50000, 50},
        {"toner", "avoskin", 120000, 45}
    };

    int data = sizeof(dataProduk) / sizeof(dataProduk[0]);

    for (int i = data - 1; i >= 0; i--) {
        Produk* produkBaru = new Produk();
        produkBaru->nama = dataProduk[i].nama;
        produkBaru->merk = dataProduk[i].merk;
        produkBaru->harga = dataProduk[i].harga;
        produkBaru->jumlah_stok = dataProduk[i].jumlah_stok;
        produkBaru->next = head;
        head = produkBaru;
        jumlahproduk++;
    }
}

void tambahproduk() {
    Produk* ProdukBaru = new Produk();
    cin.ignore();
    
    cout << "Masukkan nama produk: ";
    getline(cin, ProdukBaru->nama);

    cout << "Masukkan merk produk: ";
    getline(cin, ProdukBaru->merk);

    cout << "Masukkan harga produk: ";
    while (!(cin >> ProdukBaru->harga)) {
        cout << "Input tidak valid. Harap masukkan angka.\n";
        cin.clear();
        cin.ignore();
        cout << "Masukkan harga produk: ";
    }

    cout << "Masukkan jumlah stok: ";
    while (!(cin >> ProdukBaru->jumlah_stok)) {
        cout << "Input tidak valid. Harap masukkan angka.\n";
        cin.clear();
        cin.ignore();
        cout << "Masukkan jumlah stok: ";
    }

    ProdukBaru->next = head;
    head = ProdukBaru;
    jumlahproduk++;
    
    cout << "Produk berhasil ditambah.\n";
}

void tampilkanproduk() {
    if (head == nullptr) {
        cout << "Tidak ada produk untuk ditampilkan.\n";
        return;
    }

    cout << "Daftar Produk:\n";
    Produk* temp = head;
    int i = 1;
    while (temp != nullptr) {
        cout << "Produk " << i << ":\n";
        cout << "Nama: " << temp->nama << "\n";
        cout << "Merk: " << temp->merk << "\n";
        cout << "Harga: " << temp->harga << "\n";
        cout << "Jumlah Stok: " << temp->jumlah_stok << "\n\n";
        temp = temp->next;
        i++;
    }
}

void updatestok() {
    string update;
    cin.ignore();

    cout << "Masukkan nama produk yang ingin diupdate: ";
    getline(cin, update);

    Produk* temp = head;
    while (temp != nullptr) {
        if (temp->nama == update) {
            cout << "Jumlah stok saat ini: " << temp->jumlah_stok << "\n";
            cout << "Masukkan jumlah stok yang baru: ";
            
            while (!(cin >> temp->jumlah_stok)) {
                cout << "Input tidak valid. Harap masukkan angka.\n";
                cin.clear();
                cin.ignore();
                cout << "Masukkan jumlah stok yang baru: ";
            }
            
            cout << "Stok berhasil diupdate.\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Produk tidak ditemukan.\n";
}

void hapusproduk() {
    string hapus;
    cin.ignore();
    cout << "Masukkan nama produk yang ingin dihapus: ";
    getline(cin, hapus);

    if (head == nullptr) {
        cout << "Daftar produk kosong.\n";
        return;
    }

    Produk* temp = head;
    Produk* prev = nullptr;

    while (temp != nullptr && temp->nama != hapus) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Produk tidak ditemukan.\n";
        return;
    }

    if (prev == nullptr) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    delete temp;
    jumlahproduk--;
    cout << "Produk berhasil dihapus.\n";
}

int main() {
    data();
    int pilih;

    do {
        cout << "\nSistem Pendataan Produk Skincare\n";
        cout << "1. Tambah Produk\n";
        cout << "2. Tampilkan Produk\n";
        cout << "3. Update Stok\n";
        cout << "4. Hapus Produk\n";
        cout << "5. Keluar\n";
        cout << "Pilih Menu: ";
        cin >> pilih;
        cin.ignore();

        if (cin.fail()) {
            cout << "Input tidak valid. Harap masukkan angka.\n";
            cin.clear();
            cin.ignore();
            continue;
        }

        switch (pilih) {
            case 1:
                tambahproduk();
                break;
            case 2:
                tampilkanproduk();
                break;
            case 3:
                tampilkanproduk();
                updatestok();
                break;
            case 4:
                tampilkanproduk();
                hapusproduk();
                break;
            case 5:
                cout << "Terima kasih telah menggunakan sistem ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilih != 5);

    return 0;
}