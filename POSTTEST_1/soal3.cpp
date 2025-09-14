#include <iostream>
using namespace std;

// Definisi struct Mahasiswa
struct Mahasiswa {
    string nama;
    string nim;
    double ipk;
};

int main() {
    const int N = 5;
    Mahasiswa mhs[N] = {
        {"Andi",   "231001", 3.25},
        {"Budi",   "231002", 3.80},
        {"Citra",  "231003", 3.80},
        {"Dewi",   "231004", 3.40},
        {"Eka",    "231005", 3.10}
    };

    // Cari IPK tertinggi
    double maxIPK = mhs[0].ipk;
    for (int i = 1; i < N; i++) {
        if (mhs[i].ipk > maxIPK) {
            maxIPK = mhs[i].ipk;
        }
    }

    // Tampilkan semua mahasiswa dengan IPK tertinggi
    cout << "Mahasiswa dengan IPK tertinggi (" << maxIPK << "):\n";
    for (int i = 0; i < N; i++) {
        if (mhs[i].ipk == maxIPK) {
            cout << "----------------------\n";
            cout << "Nama : " << mhs[i].nama << endl;
            cout << "NIM  : " << mhs[i].nim << endl;
            cout << "IPK  : " << mhs[i].ipk << endl;
        }
    }

    return 0;
}
