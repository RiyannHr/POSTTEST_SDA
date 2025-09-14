#include <iostream>
using namespace std;

int main() {
    const int N = 3;
    int matriks[N][N];
    int nilai = 1;

    // Isi matriks otomatis dengan angka 1-9
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriks[i][j] = nilai++;
        }
    }

    // Tampilkan matriks
    cout << "Matriks 3x3:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << matriks[i][j] << "\t";
        }
        cout << endl;
    }

    // Hitung jumlah diagonal utama dan sekunder
    int jumlahDiagonalUtama = 0, jumlahDiagonalSekunder = 0;
    for (int i = 0; i < N; i++) {
        jumlahDiagonalUtama += matriks[i][i];            // diagonal utama
        jumlahDiagonalSekunder += matriks[i][N - 1 - i]; // diagonal sekunder
    }

    // Tampilkan hasil
    cout << "\nJumlah diagonal utama     = " << jumlahDiagonalUtama << endl;
    cout << "Jumlah diagonal sekunder = " << jumlahDiagonalSekunder << endl;
    cout << "Total keduanya           = " << (jumlahDiagonalUtama + jumlahDiagonalSekunder) << endl;

    return 0;
}
