#include <iostream>
#include <string>
#include <limits>
#include <cctype>
using namespace std;

// ==================== STRUCT NODE ====================
struct Node {
    int id;             // ID unik item
    string namaItem;
    int jumlah;
    string tipe;
    Node* next;
    Node* prev;
};

// ==================== DOUBLE LINKED LIST ====================
class InventoryGame {
private:
    Node* head;
    Node* tail;
    int idCounter;   // untuk generate ID unik

public:
    InventoryGame() : head(nullptr), tail(nullptr), idCounter(1) {}

    ~InventoryGame() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    // Tambah item di belakang
    void tambahItem(const string& namaItem, const string& tipe, int jumlahAwal) {
        Node* baru = new Node;
        baru->id = idCounter++;
        baru->namaItem = namaItem;
        baru->jumlah = jumlahAwal;
        baru->tipe = tipe;
        baru->next = nullptr;
        baru->prev = tail;

        if (!head) head = tail = baru;
        else {
            tail->next = baru;
            tail = baru;
        }
        cout << "Item \"" << namaItem << "\" ditambahkan (ID=" << baru->id
             << ", jumlah=" << jumlahAwal << ").\n";
    }

    // Sisipkan item di posisi tertentu
    void sisipkanItem(const string& namaItem, const string& tipe, int jumlahAwal, int posisi) {
        Node* baru = new Node;
        baru->id = idCounter++;
        baru->namaItem = namaItem;
        baru->jumlah = jumlahAwal;
        baru->tipe = tipe;
        baru->next = nullptr;
        baru->prev = nullptr;

        if (!head || posisi <= 1) {
            baru->next = head;
            if (head) head->prev = baru;
            head = baru;
            if (!tail) tail = baru;
            cout << "Item \"" << namaItem << "\" disisipkan di posisi 1.\n";
            return;
        }

        Node* temp = head;
        int i = 1;
        while (temp->next && i < posisi - 1) {
            temp = temp->next;
            i++;
        }

        baru->next = temp->next;
        baru->prev = temp;
        if (temp->next) temp->next->prev = baru;
        else tail = baru; // kalau disisip di akhir
        temp->next = baru;

        cout << "Item \"" << namaItem << "\" disisipkan di posisi " << (i + 1) << ".\n";
    }

    // Hapus item terakhir
    void hapusTerakhir() {
        if (!head) {
            cout << "Inventory kosong!\n";
            return;
        }
        cout << "Item \"" << tail->namaItem << "\" dihapus dari inventory.\n";
        Node* hapus = tail;
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            head = tail = nullptr;
        }
        delete hapus;
    }

    // Gunakan item
    void gunakanItem(const string& namaItem) {
        if (!head) {
            cout << "Inventory kosong!\n";
            return;
        }
        Node* temp = head;
        while (temp) {
            if (temp->namaItem == namaItem) {
                temp->jumlah--;
                cout << "Menggunakan 1 \"" << namaItem << "\". Sisa: " << temp->jumlah << '\n';
                if (temp->jumlah <= 0) {
                    cout << "Item \"" << namaItem << "\" habis dan dihapus dari inventory!\n";
                    if (temp->prev) temp->prev->next = temp->next;
                    else head = temp->next;
                    if (temp->next) temp->next->prev = temp->prev;
                    else tail = temp->prev;
                    delete temp;
                }
                return;
            }
            temp = temp->next;
        }
        cout << "Item \"" << namaItem << "\" tidak ditemukan!\n";
    }

    // Tampilkan inventory dari depan
    void tampilkan() const {
        cout << "\n========= INVENTORY RPG (Depan ke Belakang) =========\n";
        if (!head) {
            cout << "Inventory kosong!\n";
            cout << "===================================================\n";
            return;
        }
        Node* temp = head;
        while (temp) {
            cout << "ID: " << temp->id
                 << " | Nama: " << temp->namaItem
                 << " | Jumlah: " << temp->jumlah
                 << " | Tipe: " << temp->tipe << '\n';
            temp = temp->next;
        }
        cout << "===================================================\n";
    }

    // Tampilkan inventory dari belakang
    void tampilkanBelakang() const {
        cout << "\n========= INVENTORY RPG (Belakang ke Depan) =========\n";
        if (!tail) {
            cout << "Inventory kosong!\n";
            cout << "====================================================\n";
            return;
        }
        Node* temp = tail;
        while (temp) {
            cout << "ID: " << temp->id
                 << " | Nama: " << temp->namaItem
                 << " | Jumlah: " << temp->jumlah
                 << " | Tipe: " << temp->tipe << '\n';
            temp = temp->prev;
        }
        cout << "====================================================\n";
    }

    // Cari item berdasarkan ID atau nama
    void detailItem() {
        cout << "Cari berdasarkan (1=ID, 2=Nama): ";
        int pilihan; cin >> pilihan;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pilihan == 1) {
            int cariID;
            cout << "Masukkan ID: "; cin >> cariID;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Node* temp = head;
            while (temp) {
                if (temp->id == cariID) {
                    cout << ">> Ditemukan: ID=" << temp->id
                         << ", Nama=" << temp->namaItem
                         << ", Jumlah=" << temp->jumlah
                         << ", Tipe=" << temp->tipe << "\n";
                    return;
                }
                temp = temp->next;
            }
            cout << "Item dengan ID " << cariID << " tidak ditemukan!\n";
        }
        else if (pilihan == 2) {
            string cariNama;
            cout << "Masukkan Nama: "; getline(cin, cariNama);
            Node* temp = head;
            while (temp) {
                if (temp->namaItem == cariNama) {
                    cout << ">> Ditemukan: ID=" << temp->id
                         << ", Nama=" << temp->namaItem
                         << ", Jumlah=" << temp->jumlah
                         << ", Tipe=" << temp->tipe << "\n";
                    return;
                }
                temp = temp->next;
            }
            cout << "Item dengan nama \"" << cariNama << "\" tidak ditemukan!\n";
        }
        else {
            cout << "Pilihan tidak valid!\n";
        }
    }
};

// ==================== MAIN PROGRAM ====================
int main() {
    string nama = "Riyan Hidayat Rahman";
    string NIM = "2409106085";

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
        cout << "|        GAME INVENTORY MANAGEMENT (DLL)    |\n";
        cout << "| Nama: " << nama << " | NIM: " << NIM << " |\n";
        cout << "+-------------------------------------------+\n";
        cout << "| 1. Tambah Item Baru                        |\n";
        cout << "| 2. Sisipkan Item                           |\n";
        cout << "| 3. Hapus Item Terakhir                     |\n";
        cout << "| 4. Gunakan Item                            |\n";
        cout << "| 5. Tampilkan Inventory (Depan)             |\n";
        cout << "| 6. Tampilkan Inventory (Belakang)          |\n";
        cout << "| 7. Cari Detail Item (ID/Nama)              |\n";
        cout << "| 0. Keluar                                  |\n";
        cout << "+-------------------------------------------+\n";
        cout << "Pilih menu: ";
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Masukkan angka yang valid!\n";
            continue;
        }
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
            case 6:
                inventory.tampilkanBelakang();
                break;
            case 7:
                inventory.detailItem();
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
