#include <iostream>
#include <string>
#include <limits>   // untuk numeric_limits
#include <cctype>   // untuk isdigit
using namespace std;

// ==================== STRUCT NODE ====================
struct Node {
    string namaItem;
    int jumlah;
    string tipe;
    Node* next;
};

// ==================== SINGLE LINKED LIST ====================
class InventoryGame {
private:
    Node* head;

public:
    InventoryGame() : head(nullptr) {}

    // Destructor: hapus semua node saat objek dihancurkan
    ~InventoryGame() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    // Tambah item baru di belakang
    void tambahItem(const string& namaItem, const string& tipe, int jumlahAwal) {
        Node* baru = new Node;
        baru->namaItem = namaItem;
        baru->jumlah = jumlahAwal;
        baru->tipe = tipe;
        baru->next = nullptr;

        if (!head) head = baru;
        else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = baru;
        }
        cout << "Item \"" << namaItem << "\" ditambahkan (jumlah=" << jumlahAwal << ").\n";
    }

    // Sisipkan item di posisi tertentu (1 = kepala)
    void sisipkanItem(const string& namaItem, const string& tipe, int jumlahAwal, int posisi) {
        Node* baru = new Node;
        baru->namaItem = namaItem;
        baru->jumlah = jumlahAwal;
        baru->tipe = tipe;
        baru->next = nullptr;

        if (!head || posisi <= 1) {
            baru->next = head;
            head = baru;
            cout << "Item \"" << namaItem << "\" disisipkan di posisi 1.\n";
            return;
        }

        Node* temp = head;
        int i = 1;
        while (temp->next && i < posisi - 1) {
            temp = temp->next;
            i++;
        }
        // sekarang temp adalah node sebelum posisi sisip
        baru->next = temp->next;
        temp->next = baru;
        cout << "Item \"" << namaItem << "\" disisipkan di posisi " << (i + 1) << ".\n";
    }

    // Hapus item terakhir
    void hapusTerakhir() {
        if (!head) {
            cout << "Inventory kosong!\n";
            return;
        }
        if (!head->next) {
            cout << "Item \"" << head->namaItem << "\" dihapus dari inventory.\n";
            delete head;
            head = nullptr;
            return;
        }
        Node* temp = head;
        while (temp->next->next) temp = temp->next;
        cout << "Item \"" << temp->next->namaItem << "\" dihapus dari inventory.\n";
        delete temp->next;
        temp->next = nullptr;
    }

    // Gunakan item (kurangi 1 jumlah; jika 0 maka hapus)
    void gunakanItem(const string& namaItem) {
        if (!head) {
            cout << "Inventory kosong!\n";
            return;
        }
        Node* temp = head;
        Node* prev = nullptr;
        while (temp) {
            if (temp->namaItem == namaItem) {
                temp->jumlah--;
                cout << "Menggunakan 1 \"" << namaItem << "\". Sisa: " << temp->jumlah << '\n';
                if (temp->jumlah <= 0) {
                    cout << "Item \"" << namaItem << "\" habis dan dihapus dari inventory!\n";
                    if (prev) prev->next = temp->next;
                    else head = temp->next;
                    delete temp;
                }
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        cout << "Item \"" << namaItem << "\" tidak ditemukan!\n";
    }

    // Tampilkan inventory
    void tampilkan() const {
        cout << "\n========= INVENTORY RPG =========\n";
        if (!head) {
            cout << "Inventory kosong!\n";
            cout << "===============================\n";
            return;
        }
        Node* temp = head;
        int i = 1;
        while (temp) {
            cout << i++ << ". " << temp->namaItem
                << " | Jumlah: " << temp->jumlah
                << " | Tipe: " << temp->tipe << '\n';
            temp = temp->next;
        }
        cout << "===============================\n";
    }
};

// ==================== MAIN PROGRAM ====================
int main() {
    string nama = "Riyan Hidayat Rahman";
    string NIM = "2409106085";

    // Ambil dua digit terakhir (jika tersedia), kalau tidak gunakan default 1
    int jumlahAwal = 1;
    if (NIM.size() >= 2 && isdigit(NIM[NIM.size()-1]) && isdigit(NIM[NIM.size()-2])) {
        try {
            jumlahAwal = stoi(NIM.substr(NIM.size()-2));
        } catch (...) {
            jumlahAwal = 1;
        }
    }

    int digitAkhir = 0;
    if (!NIM.empty() && isdigit(NIM.back())) digitAkhir = NIM.back() - '0';
    int posisiSisip = (digitAkhir == 0) ? 2 : digitAkhir + 1;

    InventoryGame inventory;
    int pilihan = -1;
    string inputNama, inputTipe;

    do {
        cout << "\n+-------------------------------------------+\n";
        cout << "|        GAME INVENTORY MANAGEMENT          |\n";
        cout << "| Nama: " << nama << " | NIM: " << NIM << " |\n";
        cout << "+-------------------------------------------+\n";
        cout << "| 1. Tambah Item Baru                        |\n";
        cout << "| 2. Sisipkan Item                            |\n";
        cout << "| 3. Hapus Item Terakhir                     |\n";
        cout << "| 4. Gunakan Item                             |\n";
        cout << "| 5. Tampilkan Inventory                     |\n";
        cout << "| 0. Keluar                                  |\n";
        cout << "+-------------------------------------------+\n";
        cout << "Pilih menu: ";
        if (!(cin >> pilihan)) {
            // jika input bukan angka, bersihkan dan ulangi
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Masukkan angka yang valid!\n";
            continue;
        }
        // bersihkan sisa input sampai newline agar getline berikutnya bekerja
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(pilihan) {
            case 1:
                cout << "Nama Item: "; getline(cin, inputNama);
                cout << "Tipe Item: "; getline(cin, inputTipe);
                inventory.tambahItem(inputNama, inputTipe, jumlahAwal);
                break;
            case 2:
                cout << "Nama Item: "; getline(cin, inputNama);
                cout << "Tipe Item: "; getline(cin, inputTipe);
                inventory.sisipkanItem(inputNama, inputTipe, jumlahAwal, posisiSisip);
                break;
            case 3:
                inventory.hapusTerakhir();
                break;
            case 4:
                cout << "Nama Item yang digunakan: "; getline(cin, inputNama);
                inventory.gunakanItem(inputNama);
                break;
            case 5:
                inventory.tampilkan();
                break;
            case 0:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while(pilihan != 0);

    return 0;
}
