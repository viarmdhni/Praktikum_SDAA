#include <iostream>
using namespace std;

// Fungsi rekursif mencetak bintang
void Bintang(int kolom) {
    if (kolom > 0) {
        cout << "* ";
        Bintang(kolom - 1);
    }
}

// Fungsi rekursif mencetak segitiga
void Segitiga(int baris) {
    if (baris > 0) {
        Segitiga(baris - 1);
        Bintang(baris);
        cout << endl;
    }
}

int main() {
    cout << "Segitiga :\n";
    Segitiga(3);
    return 0;
}
