#include "TLL.h"
#include <iostream>

using namespace std;

void createTList(TList &T){
    T.first = nullptr;
}

bool isEmpty(TList T){
    return T.first == nullptr;
}

adrTList allocateTList(address root, string exp, int res){
    adrTList p = new elmTList;
    p->root = root;
    p->expression = exp;
    p->result = res;
    p->next = nullptr;

    return p;
}

void insertFirst(TList &T, adrTList p){
    if(T.first == nullptr){
        T.first = p;
    } else {
        p->next = T.first;
        T.first = p;
    }
}

// Fungsi Mencari Tree berdasarkan Nomor Urut (Untuk fitur Edit)
address getTreeFromHistory(TList T, int index) {
    adrTList p = T.first;
    int i = 1;

    // Loop sampai ketemu index yang diminta atau list habis
    while (p != nullptr && i < index) {
        p = p->next;
        i++;
    }

    // Jika ketemu, kembalikan pointer Root Tree-nya
    if (p != nullptr && i == index) {
        cout << ">> Memilih ekspresi: " << p->expression << endl;
        return p->root;
    }

    return nullptr; // Tidak ketemu
}

// Menampilkan seluruh riwayat
void showHistory(TList T) {
    if (T.first == nullptr) {
        cout << ">> History Kosong. Belum ada perhitungan." << endl;
        return;
    }

    adrTList p = T.first;
    int i = 1;

    cout << "\n=== RIWAYAT KALKULASI ===" << endl;
    while (p != nullptr) {
        cout << i << ". " << p->expression << " = " << p->result << endl;
        p = p->next;
        i++;
    }
    cout << "=========================" << endl;
}

void insertLast(TList &T, adrTList p){
    if (isEmpty(T)){
        insertFirst(T, p);
    } else {
        adrTList q = T.first;
        while (q != nullptr) {
            q = q->next;
        }
        q->next = p;
    }
}

void deleteHistoryByIndex(TList &T, int index) {
    if (T.first == nullptr) return;

    adrTList p = T.first;
    adrTList prev = nullptr;
    int i = 1;

    // Cari node ke-index
    while (p != nullptr && i < index) {
        prev = p;
        p = p->next;
        i++;
    }

    // Jika ketemu
    if (p != nullptr && i == index) {
        // 1. Putuskan link dari list
        if (p == T.first) {
            T.first = p->next;
        } else {
            prev->next = p->next;
        }

        // 2. Hapus tree lama yang menempel di node ini (PENTING!)
        deleteAllNodes(p->root);

        // 3. Hapus node history
        delete p;
    }
}
