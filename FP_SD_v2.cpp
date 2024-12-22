#include <iostream>
#include <cstring>
#include <iomanip>
#include <ctime>
#include <stack>
using namespace std;

// Tugas Alif Valeri Sabrifin Struktur untuk menyimpan informasi kendaraan
struct Kendaraan {
    int id; // ID kendaraan
    char jenis[50]; // Jenis kendaraan
    int kapasitas; // Kapasitas kendaraan dalam kg
    int harga_sewa; // Harga sewa kendaraan per unit durasi
    char durasi[20]; // Durasi waktu sewa (misalnya "per hari")
    bool tersedia; // Status ketersediaan kendaraan (true = tersedia, false = tidak tersedia)
};

// Struktur untuk menyimpan data pelanggan yang menyewa kendaraan
struct Pelanggan {
    char nama[50]; // Nama pelanggan
    char no_telp[20]; // Nomor telepon pelanggan
    Kendaraan kendaraan; // Kendaraan yang disewa
    char tanggal_mulai[20]; // Tanggal mulai sewa
    char tanggal_selesai[20]; // Tanggal selesai sewa
    int lama_pinjam; // Lama pinjam dalam hari
};

// Struktur Node untuk implementasi Linked List
// Tugas Melisa Tresia Patadang - Linked List
struct Node {
    Pelanggan data; // Data pelanggan dalam Node
    Node* next; // Pointer ke Node berikutnya
};

Node* createNode(Pelanggan p) {
    Node* newNode = new Node;
    newNode->data = p;
    newNode->next = NULL;
    return newNode;
}
// Tugas Anabila Maharani Sutomo
void enqueue(Node*& front, Node*& rear, Pelanggan p) {
    Node* newNode = createNode(p);
    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

Pelanggan dequeue(Node*& front, Node*& rear) {
    if (front == NULL) {
        Pelanggan kosong = {"", "", {}, "", "", 0};
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

void tampilkanAntrean(Node* front) {
    Node* temp = front;
    if (!temp) {
        cout << "\033[1;31mAntrean kosong.\033[0m\n";
        return;
    }

    cout << left << setw(20) << "Nama" << setw(15) << "No HP" << setw(20) << "Jenis Kendaraan" << endl;
    while (temp) {
        cout << left << setw(20) << temp->data.nama << setw(15) << temp->data.no_telp << setw(20) << temp->data.kendaraan.jenis << endl;
        temp = temp->next;
    }
}

void cetakNota(Pelanggan p) {
    int total_harga = p.lama_pinjam * p.kendaraan.harga_sewa;
    cout << "\n\033[1;32m======== NOTA ========\033[0m\n";
    cout << "Nama Pelanggan: " << p.nama << endl;
    cout << "No HP: " << p.no_telp << endl;
    cout << "Jenis Kendaraan: " << p.kendaraan.jenis << endl;
    cout << "Tanggal Mulai: " << p.tanggal_mulai << endl;
    cout << "Lama Pinjam: " << p.lama_pinjam << " hari" << endl;
    cout << "Tanggal Selesai: " << p.tanggal_selesai << endl;
    cout << "Harga Sewa: Rp" << p.kendaraan.harga_sewa << " / " << p.kendaraan.durasi << endl;
    cout << "Total Harga: Rp" << total_harga << endl;
    cout << "\033[1;32m=======================\033[0m\n";
}

void updateStatus(Kendaraan* k, bool status) {
    k->tersedia = status;
}

void hitungTanggalSelesai(const char* tanggal_mulai, int lama_pinjam, char* tanggal_selesai) {
    int dd, mm, yyyy;
    sscanf(tanggal_mulai, "%d/%d/%d", &dd, &mm, &yyyy);

    tm timeinfo = {};
    timeinfo.tm_mday = dd;
    timeinfo.tm_mon = mm - 1;
    timeinfo.tm_year = yyyy - 1900;

    time_t waktu_mulai = mktime(&timeinfo);
    waktu_mulai += lama_pinjam * 24 * 3600;

    tm* waktu_selesai = localtime(&waktu_mulai);
    strftime(tanggal_selesai, 20, "%d/%m/%Y", waktu_selesai);
}
// Tugas Dzikri Albantani - Sorting
void sortKendaraan(Kendaraan kendaraan[], int jumlah, int pilihan) {
    for (int i = 0; i < jumlah - 1; ++i) {
        for (int j = 0; j < jumlah - i - 1; ++j) {
            bool swapRequired = false;
            // Tugas Asep Fadhil Nugraha - Searching
            if (pilihan == 1 && kendaraan[j].harga_sewa > kendaraan[j + 1].harga_sewa) {
                swapRequired = true;
            } else if (pilihan == 2 && kendaraan[j].harga_sewa < kendaraan[j + 1].harga_sewa) {
                swapRequired = true;
            } else if (pilihan == 3 && kendaraan[j].tersedia < kendaraan[j + 1].tersedia) {
                swapRequired = true;
            }

            if (swapRequired) {
                Kendaraan temp = kendaraan[j];
                kendaraan[j] = kendaraan[j + 1];
                kendaraan[j + 1] = temp;
            }
        }
    }
}

// Tugas Muhammad Reksa Pradana - Stack (Riwayat Transaksi)
stack<Pelanggan> riwayatTransaksi;

void tambahkanKeRiwayat(Pelanggan p) {
    riwayatTransaksi.push(p);
}

void tampilkanRiwayat() {
    if (riwayatTransaksi.empty()) {
        cout << "\033[1;31mRiwayat transaksi kosong.\033[0m\n";
        return;
    }

    cout << "\n\033[1;34m======= RIWAYAT TRANSAKSI =======\033[0m\n";
    stack<Pelanggan> tempStack = riwayatTransaksi;
    while (!tempStack.empty()) {
        Pelanggan p = tempStack.top();
        tempStack.pop();

        cout << "Nama: " << p.nama << endl;
        cout << "No HP: " << p.no_telp << endl;
        cout << "Jenis Kendaraan: " << p.kendaraan.jenis << endl;
        cout << "Tanggal Mulai: " << p.tanggal_mulai << endl;
        cout << "Tanggal Selesai: " << p.tanggal_selesai << endl;
        cout << "Lama Pinjam: " << p.lama_pinjam << " hari" << endl;
        cout << "\033[1;34m-------------------------------\033[0m\n";
    }
}

int main() {
    Kendaraan kendaraan[100];
    int jumlahKendaraan = 3;

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
        cout << "\033[1;34m\n Selamat Datang di Penyewaan Ganaderia\033[0m\n";
        cout << "\033[1;34m*=====================================*\033[0m\n";
        cout << "Menu Utama:\n";
        cout << "1. Lihat Daftar Kendaraan\n";
        cout << "2. Proses Sewa Kendaraan\n";
        cout << "3. Pengembalian Kendaraan\n";
        cout << "4. Lihat Antrean\n";
        cout << "5. Tampilkan Riwayat Transaksi\n";
        cout << "6. Keluar\n";
        cout << "\033[1;34m*=====================================*\033[0m\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
        case 1: {
            int opsiSort;
            cout << "\nPilih opsi sorting:\n";
            cout << "1. Harga Terendah\n";
            cout << "2. Harga Tertinggi\n";
            cout << "3. Berdasarkan Ketersediaan\n";
            cout << "Pilihan Anda: ";
            cin >> opsiSort;
            cin.ignore();
			// Tugas Dzikri Albantani - Sorting
            if (opsiSort >= 1 && opsiSort <= 3) {
                sortKendaraan(kendaraan, jumlahKendaraan, opsiSort);
                cout << left << setw(5) << "ID" << setw(15) << "Jenis" << setw(10) << "Kapasitas" << setw(15) << "Harga" << setw(15) << "Durasi" << "Status" << endl;
                for (int i = 0; i < jumlahKendaraan; ++i) {
                    cout << left << setw(5) << kendaraan[i].id << setw(15) << kendaraan[i].jenis << setw(10) << kendaraan[i].kapasitas << setw(15) << kendaraan[i].harga_sewa << setw(15) << kendaraan[i].durasi << (kendaraan[i].tersedia ? "Tersedia" : "Tidak Tersedia") << endl;
                }
            } else {
                cout << "\033[1;31mPilihan sorting tidak valid.\033[0m\n";
            }
            break;
        }

        case 2: {
            Pelanggan p;
            cout << "Masukkan Nama Pelanggan: ";
            cin.getline(p.nama, 50);
            cout << "Masukkan No HP Pelanggan: ";
            cin.getline(p.no_telp, 20);
            cout << "Masukkan Jenis Kendaraan yang Dipilih: ";
            char jenis[50];
            cin.getline(jenis, 50);
			// Tugas Asep Fadhil Nugraha - Searching
            int idx = -1;
            for (int i = 0; i < jumlahKendaraan; ++i) {
                if (strcmp(kendaraan[i].jenis, jenis) == 0 && kendaraan[i].tersedia) {
                    idx = i;
                    break;
                }
            }
            // Tugas Asep Fadhil Nugraha - Searching
            if (idx != -1) {
                p.kendaraan = kendaraan[idx];
                updateStatus(&kendaraan[idx], false);

                cout << "Masukkan Tanggal Mulai (dd/mm/yyyy): ";
                cin.getline(p.tanggal_mulai, 20);
                cout << "Masukkan Lama Pinjam (hari): ";
                cin >> p.lama_pinjam;
                cin.ignore();

                hitungTanggalSelesai(p.tanggal_mulai, p.lama_pinjam, p.tanggal_selesai);
                enqueue(antreanFront, antreanRear, p);
                tambahkanKeRiwayat(p);
                cetakNota(p);
                cout << "\033[1;32mProses sewa berhasil!\033[0m\n";
            } else {
                cout << "\033[1;31mKendaraan tidak tersedia atau tidak ditemukan.\033[0m\n";
            }
            break;
        }

        case 3: {
            Pelanggan selesai = dequeue(antreanFront, antreanRear);
            if (strcmp(selesai.nama, "") != 0) {
            	//Tugas Asep Fadhil Nugraha - Searching
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
                cout << "\033[1;32mPengembalian kendaraan berhasil!\033[0m\n";
            } else {
                cout << "\033[1;31mTidak ada kendaraan dalam antrean.\033[0m\n";
            }
            break;
        }

        case 4:
            tampilkanAntrean(antreanFront);
            break;

        case 5:
            tampilkanRiwayat();
            break;

        case 6:
            cout << "\033[1;34mKeluar dari program. Data disimpan.\033[0m\n";
            break;

        default:
            cout << "\033[1;31mPilihan tidak valid.\033[0m\n";
        }

    } while (pilihan != 6);

    return 0;
}
