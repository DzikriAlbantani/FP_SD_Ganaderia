#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

struct Kendaraan {
    int id;
    char jenis[50];
    int kapasitas;
    int harga_sewa;
    char durasi[20];
    bool tersedia; // true = tersedia, false = tidak tersedia
};

struct Pelanggan {
    char nama[50];
    char no_telp[20];
    Kendaraan kendaraan;
    char tanggal_mulai[20];
    char tanggal_selesai[20];
};

// Struktur Node untuk Linked List
struct Node {
    Pelanggan data;
    Node* next;
};

// Fungsi untuk membuat Node baru
Node* createNode(Pelanggan p) {
    Node* newNode = new Node;
    newNode->data = p;
    newNode->next = NULL;
    return newNode;
}

// Fungsi untuk menambahkan pelanggan ke antrean (enqueue)
void enqueue(Node*& front, Node*& rear, Pelanggan p) {
    Node* newNode = createNode(p);
    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

// Fungsi untuk menghapus pelanggan dari antrean (dequeue)
Pelanggan dequeue(Node*& front, Node*& rear) {
    if (front == NULL) {
        Pelanggan kosong = {"", "", {}, "", ""};
        return kosong;
    }

    Node* temp = front;
    Pelanggan p = front->data;
    front = front->next;

    if (front == NULL) {
        rear = NULL;
    }

    delete temp;
    return p;
}

// Fungsi untuk menampilkan antrean pelanggan
void tampilkanAntrean(Node* front) {
    Node* temp = front;
    if (!temp) {
        cout << "Antrean kosong.\n";
        return;
    }

    cout << left << setw(20) << "Nama" << setw(15) << "No HP" << setw(20) << "Jenis Kendaraan" << endl;
    while (temp) {
        cout << left << setw(20) << temp->data.nama << setw(15) << temp->data.no_telp << setw(20) << temp->data.kendaraan.jenis << endl;
        temp = temp->next;
    }
}

// Fungsi untuk mencetak nota
void cetakNota(Pelanggan p) {
    cout << "\n======== NOTA ========\n";
    cout << "Nama Pelanggan: " << p.nama << endl;
    cout << "No HP: " << p.no_telp << endl;
    cout << "Jenis Kendaraan: " << p.kendaraan.jenis << endl;
    cout << "Tanggal Mulai: " << p.tanggal_mulai << endl;
    cout << "Tanggal Selesai: " << p.tanggal_selesai << endl;
    cout << "Harga Sewa: Rp" << p.kendaraan.harga_sewa << " / " << p.kendaraan.durasi << endl;
    cout << "=======================\n";
}

// Fungsi untuk memperbarui status kendaraan
void updateStatus(Kendaraan* k, bool status) {
    k->tersedia = status;
}

int main() {
    Kendaraan kendaraan[100];
    int jumlahKendaraan = 3;

    // Kendaraan yang sudah ada
    Kendaraan k1 = {1, "Pickup", 1000, 200000, "per hari", true};
    Kendaraan k2 = {2, "Truck Box", 5000, 1000000, "per hari", true};
    Kendaraan k3 = {3, "Van Cargo", 2000, 500000, "per hari", true};
    kendaraan[0] = k1;
    kendaraan[1] = k2;
    kendaraan[2] = k3;

    Node* antreanFront = NULL;
    Node* antreanRear = NULL;

    int pilihan;
    do {
        cout << "\nMenu Utama:\n";
        cout << "1. Lihat Daftar Kendaraan\n";
        cout << "2. Proses Sewa Kendaraan\n";
        cout << "3. Pengembalian Kendaraan\n";
        cout << "4. Lihat Antrean\n";
        cout << "5. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
        case 1:
            cout << left << setw(5) << "ID" << setw(15) << "Jenis" << setw(10) << "Kapasitas" << setw(15) << "Harga" << setw(15) << "Durasi" << "Status" << endl;
            for (int i = 0; i < jumlahKendaraan; ++i) {
                cout << left << setw(5) << kendaraan[i].id << setw(15) << kendaraan[i].jenis << setw(10) << kendaraan[i].kapasitas << setw(15) << kendaraan[i].harga_sewa << setw(15) << kendaraan[i].durasi << (kendaraan[i].tersedia ? "Tersedia" : "Tidak Tersedia") << endl;
            }
            break;

        case 2: {
            Pelanggan p;
            cout << "Masukkan Nama Pelanggan: ";
            cin.getline(p.nama, 50);
            cout << "Masukkan No HP Pelanggan: ";
            cin.getline(p.no_telp, 20);
            cout << "Masukkan Jenis Kendaraan yang Dipilih: ";
            char jenis[50];
            cin.getline(jenis, 50);

            int idx = -1;
            for (int i = 0; i < jumlahKendaraan; ++i) {
                if (strcmp(kendaraan[i].jenis, jenis) == 0 && kendaraan[i].tersedia) {
                    idx = i;
                    break;
                }
            }

            if (idx != -1) {
                p.kendaraan = kendaraan[idx];
                updateStatus(&kendaraan[idx], false);
                cout << "Masukkan Tanggal Mulai (dd/mm/yyyy): ";
                cin.getline(p.tanggal_mulai, 20);
                cout << "Masukkan Tanggal Selesai (dd/mm/yyyy): ";
                cin.getline(p.tanggal_selesai, 20);
                enqueue(antreanFront, antreanRear, p);
                cetakNota(p);
                cout << "Proses sewa berhasil!\n";
            } else {
                cout << "Kendaraan tidak tersedia atau tidak ditemukan.\n";
            }
            break;
        }

        case 3: {
            Pelanggan selesai = dequeue(antreanFront, antreanRear);
            if (strcmp(selesai.nama, "") != 0) {
                int idx = -1;
                for (int i = 0; i < jumlahKendaraan; ++i) {
                    if (strcmp(kendaraan[i].jenis, selesai.kendaraan.jenis) == 0) {
                        idx = i;
                        break;
                    }
                }

                if (idx != -1) {
                    updateStatus(&kendaraan[idx], true);
                }
                cout << "Pengembalian kendaraan berhasil!\n";
            } else {
                cout << "Tidak ada kendaraan dalam antrean.\n";
            }
            break;
        }

        case 4:
            tampilkanAntrean(antreanFront);
            break;

        case 5:
            cout << "Keluar dari program. Data disimpan.\n";
            break;

        default:
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 5);

    return 0;
