#include <iostream>
using namespace std;

// Fungsi untuk menukar dua variabel menggunakan double pointer
void tukar(int **a, int **b) {
    int temp = **a;
    **a = **b;
    **b = temp;
}

int main() {
    int x, y;
    cout << "Masukkan nilai x: ";
    cin >> x;
    cout << "Masukkan nilai y: ";
    cin >> y;

    cout << "\nSebelum pertukaran:" << endl;
    cout << "x = " << x << ", y = " << y << endl;

    // Buat pointer ke variabel x dan y
    int *px = &x;
    int *py = &y;

    // Panggil fungsi tukar dengan alamat pointer
    tukar(&px, &py);

    cout << "\nSesudah pertukaran:" << endl;
    cout << "x = " << x << ", y = " << y << endl;

    return 0;
}
