#include <iostream>
#include <string>
#include "tree.h"
#include "DLL.h"
#include "TLL.h"

using namespace std;

// Fungsi Menu untuk tampilan bersih
int showMenu() {
    int choice;
    cout << "\n===================================" << endl;
    cout << "      CALCULATOR TREE SYSTEM       " << endl;
    cout << "===================================" << endl;
    cout << "1. Hitung Baru" << endl;
    cout << "2. Lihat History" << endl;
    cout << "3. Edit Operasi" << endl;
    cout << "0. Keluar" << endl;
    cout << "===================================" << endl;
    cout << "Pilih menu: ";

    cin >> choice;
    return choice;
}

int main() {
    // Inisialisasi History List (TLL)
    TList History;
    createTList(History);

    int pilihan;
    do {
        pilihan = showMenu();
        cin.ignore(); // Membersihkan buffer enter sebelum getline

        if (pilihan == 1) {
            // HITUNG BARU
            List L;
            createList(L);
            string expression;

            cout << "\n--- INPUT OPERASI ---" << endl;
            cout << "Format: Angka dan Operator dipisah SPASI." << endl;
            cout << "Contoh: 3 + 5 * 2" << endl;
            cout << "Masukkan Operasi: ";
            getline(cin, expression);

            // Validasi input kosong
            if (expression.empty()) {
                cout << "Error: Input tidak boleh kosong!" << endl;
                continue;
            }

            // Simpan copy string asli untuk history
            string originalExpr = expression;
            string del = " ";
            size_t pos = 0;

            // Parsing string lalu masukkan ke DLL sebagai Tree Node
            while ((pos = expression.find(del)) != string::npos) {
            cout << " 1 " << endl;
                string token = expression.substr(0, pos);
                if (!token.empty()) {
                    // Buat node tree dari token (angka/operator)
                    address tNode = allocateTree(token);
                    // Masukkan pointer node tree tersebut ke dalam DLL
                    insertLast(L, allocateDLL(tNode));
                }
                expression.erase(0, pos + del.length());
            }
            // Proses token terakhir (sisa string)
            if (!expression.empty()) {
                address tNode = allocateTree(expression);
                insertLast(L, allocateDLL(tNode));
            }

            // Build Tree dari DLL
            address root = buildTreeFromDLL(L);

            if (root != nullptr) {
                // Hitung Hasil
                int hasil = evaluate(root);

                cout << "\n>>> HASIL PERHITUNGAN <<<" << endl;
                cout << "Ekspresi (In-Order): ";
                printInOrder(root);
                cout << endl;
                cout << "Hasil Akhir        : " << hasil << endl;

                // Simpan ke History (TLL)
                adrTList historyNode = allocateTList(root, originalExpr, hasil);
                insertFirst(History, historyNode); // Masukkan ke history paling atas
                cout << "(Data berhasil disimpan ke History)" << endl;
            } else {
                cout << "Error: Gagal membangun tree. Cek format input!" << endl;
            }

        } else if (pilihan == 2) {
            // LIHAT HISTORY
            showHistory(History);

        } else if (pilihan == 3) {
            // EDIT OPERASI
            showHistory(History);
            if (isEmpty(History)) continue; // Balik ke menu jika kosong (menggunakan isEmpty dari TLL.cpp)

            int idx;
            cout << "\nPilih Nomor History yang mau diedit: ";
            cin >> idx;

            // Ambil pointer root tree dari history yang dipilih
            address targetRoot = getTreeFromHistory(History, idx);

            if (targetRoot != nullptr) {
                string cari, ganti;
                cout << "\n--- EDIT MODE ---" << endl;
                cout << "Operasi saat ini: "; printInOrder(targetRoot); cout << endl;

                cout << "Masukkan Angka/Operator yang mau diganti: ";
                cin >> cari;

                // Cari node di dalam tree (Fungsi findNode dari tree.cpp)
                address nodeKetemu = findNode(targetRoot, cari);

                if (nodeKetemu != nullptr) {
                    cout << "Ganti menjadi: ";
                    cin >> ganti;

                    // Update node tree
                    updateNode(nodeKetemu, ganti);

                    // Hitung Ulang
                    int newResult = evaluate(targetRoot);

                    address newRoot = copyTree(targetRoot);
                    string newExp = treeToString(newRoot);
                    deleteHistoryByIndex(History, idx);
                    // Buat node history baru dengan data yang sudah fresh
                    adrTList newHistoryNode = allocateTList(newRoot, newExp, newResult);
                    insertFirst(History, newHistoryNode);

                    cout << "\n>>> UPDATE BERHASIL! <<<" << endl;
                    cout << "Operasi Baru: "<< newExp << endl;
                    cout << "Hasil Baru  : " << newResult << endl;
                } else {
                    cout << "Error: Karakter '" << cari << "' tidak ditemukan dalam operasi tersebut." << endl;
                }
            } else {
                cout << "Error: Nomor history tidak valid." << endl;
            }

        } else if (pilihan == 0) {
            cout << "Terima kasih telah menggunakan aplikasi ini." << endl;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }

    } while (pilihan != 0);

    return 0;
}
