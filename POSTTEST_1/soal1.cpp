#include <iostream>
using namespace std;

// Fungsi untuk menampilkan array
void tampilArray(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << *(arr + i) << " ";
    }
    cout << endl;
}

// Fungsi untuk membalik isi array menggunakan pointer
void balikArray(int *arr, int n) {
    for (int i = 0; i < n / 2; i++) {
        int temp = *(arr + i);
        *(arr + i) = *(arr + (n - 1 - i));
        *(arr + (n - 1 - i)) = temp;
    }
}

int main() {
    const int N = 7;
    int data[N];

    // Isi array dengan kelipatan 3
    for (int i = 0; i < N; i++) {
        *(data + i) = (i + 1) * 3;
    }

    // Tampilkan sebelum dibalik
    cout << "Array sebelum dibalik: ";
    tampilArray(data, N);

    // Balik array
    balikArray(data, N);

    // Tampilkan sesudah dibalik
    cout << "Array sesudah dibalik: ";
    tampilArray(data, N);

    return 0;
}
