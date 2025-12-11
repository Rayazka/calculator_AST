#include <iostream>
#include <string>
#include "tree.h"
#include "DLL.h"
#include "TLL.h"

using namespace std;

// Input check
bool validasi(const string& input) {
    try {
        int angka = stoi(input);
    } catch (const invalid_argument& e) {
        cout << (input.empty() ? "Error: Input tidak boleh kosong!" : "Error: Input bukan angka!") << endl;
        return false;
    }
    return true;
}

// Fungsi Menu untuk tampilan bersih
int showMenu() {
    string choice;
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
    if (!validasi(choice)) return 'E';
    int pilihan = stoi(choice);
    return pilihan;
}

void hitungBaru(TList &History){
    List L;
    createList(L);
    string expression;

    cout << "\n--- INPUT OPERASI ---" << endl;
    cout << "Format: Angka dan Operator dipisah SPASI." << endl;
    cout << "Contoh: 3 + 5 * 2" << endl;
    cout << "Masukkan Operasi: ";
    getline(cin, expression);

    // Simpan copy string asli untuk history
    string originalExpr = expression;
    string del = " ";
    size_t pos = expression.find(del);

    if (!validasi(expression.substr(0, pos))){
        return;
    }

    // Parsing string lalu masukkan ke DLL sebagai Tree Node
    while ((pos = expression.find(del)) != string::npos) {
        string token = expression.substr(0, pos);
        if (token.empty()) {
            expression.erase(0, pos + del.length());
            continue;
        }
        // Buat node tree dari token (angka/operator)
        address tNode = allocateTree(token);
        // Masukkan pointer node tree tersebut ke dalam DLL
        insertLast(L, allocateDLL(tNode));
        expression.erase(0, pos + del.length());
    }
    // Proses token terakhir (sisa string)
    if (!expression.empty()) {
        address tNode = allocateTree(expression);
        insertLast(L, allocateDLL(tNode));
    }

    // Build Tree dari DLL
    address root = buildTreeFromDLL(L);

    if (root == nullptr) {
        cout << "Error: Gagal membangun tree. Cek format input!" << endl;
        return;
    }

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
}

void editHistory(TList &History){
    showHistory(History);
    if (isEmpty(History)) return; // Balik ke menu jika kosong (menggunakan isEmpty dari TLL.cpp)

    string idx;
    cout << "\nPilih Nomor History yang mau diedit: ";
    cin >> idx;

    if (!validasi(idx)) return;
    int id = stoi(idx);

    // Ambil pointer root tree dari history yang dipilih
    address targetRoot = getTreeFromHistory(History, id);

    if (targetRoot == nullptr) return;

    string pilihan, cari, ganti;
    address nodeKetemu;
    int target;
    cout << "\n--- EDIT MODE ---" << endl;
    cout << "Operasi saat ini: "; printInOrder(targetRoot); cout << endl;

    // //

    cout << "1. Ganti Operator" << endl;
    cout << "2. Ganti Angka" << endl;
    cout << "0. Kembali ke menu utama" << endl;
    cout << "Pilih Menu: ";
    cin >> pilihan;

    if (!validasi(pilihan)) return;
    id = stoi(pilihan);

    switch (id){
        case 1:{
            cout << "Operasi saat ini: "; printInOrder(targetRoot); cout << endl;
            cout << "Masukkan urutan operator yang mau diganti (dari kiri ke kanan): ";
            cin >> cari;

            if (!validasi(cari)) editHistory(History);
            target = stoi(cari);

            // cari operator sesuai urutan
            int count = 0;
            nodeKetemu = findOperatorByOrder(targetRoot, target, count);

            if (!nodeKetemu) return cout << "Error: Karakter '" << cari << "' tidak ditemukan dalam operasi tersebut." << endl, void();

            cout << "Ganti menjadi: ";
            cin >> ganti;

            if (ganti != "+" && ganti != "-" && ganti != "*" && ganti != "/") {
                cout << (ganti.empty() ? "Error: Input tidak boleh kosong!" : "Error: Input bukan operator!") << endl;
                return;
            }
            break;
        }
        case 2:{
            cout << "Masukkan Angka yang mau diganti: ";
            cin >> cari;

            // Cari node di dalam tree (Fungsi findNode dari tree.cpp)
            nodeKetemu = findNode(targetRoot, cari);

            if (!nodeKetemu) return cout << "Error: Karakter '" << cari << "' tidak ditemukan dalam operasi tersebut." << endl, void();

            cout << "Ganti menjadi: ";
            cin >> ganti;

            if (!validasi(ganti)) return;
            target = stoi(ganti);
            break;
        }
        case 0:
            cout << "Kembali ke menu utama" << endl;
            return;
        default:
            cout << "Pilihan tidak valid." << endl;
            return;
    }

    // Update node tree
    updateNode(nodeKetemu, ganti);

    // Hitung Ulang
    int newResult = evaluate(targetRoot);

    address newRoot = copyTree(targetRoot);
    string newExp = treeToString(newRoot);
    deleteHistoryByIndex(History, id);
    // Buat node history baru dengan data yang sudah fresh
    adrTList newHistoryNode = allocateTList(newRoot, newExp, newResult);
    insertFirst(History, newHistoryNode);

    cout << "\n>>> UPDATE BERHASIL! <<<" << endl;
    cout << "Operasi Baru: "<< newExp << endl;
    cout << "Hasil Baru  : " << newResult << endl;
}

int main() {
    // Inisialisasi History List (TLL)
    TList History;
    createTList(History);

    int pilihan;
    do {
        pilihan = showMenu();
        cin.ignore(); // Membersihkan buffer enter sebelum getline

        switch (pilihan) {
            case 1 :
                // HITUNG BARU
                hitungBaru(History);
                break;
            case 2:
                // LIHAT HISTORY
                showHistory(History);
                break;
            case 3:
                // EDIT OPERASI
                editHistory(History);
                break;
            case 0:
                // KELUAR SYSTEM
                cout << "Terima kasih telah menggunakan aplikasi ini." << endl;
                break;
            default:
                // INVALID NUMBER INPUT
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                break;
        }
    } while (pilihan != 0);

    return 0;
}
