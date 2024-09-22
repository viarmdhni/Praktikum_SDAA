#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct produk {
    string nama;
    string merk;
    int harga;
    int jumlah_stok;
};

const int maxproduk = 50;
produk daftar[maxproduk] = {
    {"serum", "wardah", 150000, 25},
    {"moisturizer", "skintific", 130000, 40},
    {"sunscreen", "facetology", 90000, 30},
    {"facial Wash", "wardah", 50000, 50},
    {"toner", "avoskin", 120000, 45}
};
int jumlahproduk = 5;


void tambahproduk(produk* daftar, int& jumlahproduk) {
    if (jumlahproduk < maxproduk) {
        cin.ignore(); // Membersihkan karakter newline dari input sebelumnya
        
        cout << "Masukkan nama produk: ";
        getline(cin, daftar[jumlahproduk].nama);

        cout << "Masukkan merk produk: ";
        getline(cin, daftar[jumlahproduk].merk);

        cout << "Masukkan harga produk: ";
        while (!(cin >> daftar[jumlahproduk].harga)) {
            cout << "Input tidak valid. Harap masukkan angka.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Masukkan harga produk: ";
        }

        cout << "Masukkan jumlah stok: ";
        while (!(cin >> daftar[jumlahproduk].jumlah_stok)) {
            cout << "Input tidak valid. Harap masukkan angka.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Masukkan jumlah stok: ";
        }
        
        jumlahproduk++;
        cout << "Produk berhasil ditambah.\n";
    } else {
        cout << "Maaf, produk sudah penuh.\n";
    }
}

void tampilkanproduk(const produk* daftar, int jumlahproduk) {
    if (jumlahproduk == 0) {
        cout << "Tidak ada produk untuk ditampilkan.\n";
        return;
    }

    cout << "Daftar Produk:\n";
    for (int i = 0; i < jumlahproduk; i++) {
        cout << "Produk " << i + 1 << ":\n";
        cout << "Nama: " << daftar[i].nama << "\n";
        cout << "Merk: " << daftar[i].merk << "\n";
        cout << "Harga: " << daftar[i].harga << "\n";
        cout << "Jumlah Stok: " << daftar[i].jumlah_stok << "\n\n";
    }
}

void updatestok(produk* daftar, int jumlahproduk) {
    string update;
    cin.ignore(); // Bersihkan buffer sebelum menggunakan getline

    cout << "Update Stok:\nMasukkan nama produk untuk mengupdate stok: ";
    getline(cin, update);

    for (int i = 0; i < jumlahproduk; i++) {
        if (daftar[i].nama == update) {
            cout << "Jumlah stok saat ini: " << daftar[i].jumlah_stok << "\n";
            cout << "Masukkan jumlah stok yang baru: ";
            
            while (!(cin >> daftar[i].jumlah_stok)) { // Periksa input yang tidak valid
                cout << "Input tidak valid. Harap masukkan angka.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Masukkan jumlah stok yang baru: ";
            }
            
            cout << "Stok berhasil diupdate.\n";
            return;
        }
    }
    cout << "Produk tidak ditemukan.\n";
}

void hapusproduk(produk* daftar, int& jumlahproduk) {
    string hapus;
    cin.ignore(); // Bersihkan buffer sebelum menggunakan getline

    cout << "Masukkan nama produk yang ingin dihapus: ";
    getline(cin, hapus);

    int indeks = -1;
    for (int i = 0; i < jumlahproduk; i++) {
        if (daftar[i].nama == hapus) {
            indeks = i;
            break;
        }
    }

    if (indeks != -1) {
        for (int i = indeks; i < jumlahproduk - 1; i++) {
            daftar[i] = daftar[i + 1];
        }
        jumlahproduk--;
        cout << "Produk berhasil dihapus.\n";
    } else {
        cout << "Produk tidak ditemukan.\n";
    }
}

int main() {
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

        if (cin.fail()) { // Periksa jika input bukan angka
            cout << "Input tidak valid. Harap masukkan angka.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; // Lewatkan loop dan minta input lagi
        }

        switch (pilih) {
            case 1:
                tambahproduk(daftar, jumlahproduk);
                break;
            case 2:
                tampilkanproduk(daftar, jumlahproduk);
                break;
            case 3:
                updatestok(daftar, jumlahproduk);
                break;
            case 4:
                hapusproduk(daftar, jumlahproduk);
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
