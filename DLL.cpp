#include "DLL.h"
#include <iostream>

using namespace std;

void createList(List &L){
    L.First = nullptr;
    L.Last = nullptr;
}

bool isEmpty(List L){
    return L.First == nullptr;
}

adrList allocateDLL(address node){
    adrList p = new elmList;
    p->treeNode = node;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

void printInfo(List L){
    if(isEmpty(L)){
        cout << "List Kosong" << endl;
    } else {
        adrList p = nullptr;
        p = L.First;
        cout << "daftar elemen list: ";
        while(p != nullptr){
            // Kita akses info yang ada di dalam treeNode
            if (p->treeNode != nullptr) {
                cout << "[" << p->treeNode->info << "] ";
            }
            p = p->next;
            if(p != nullptr){
                cout << ", ";
            } else {
                cout << endl;
            }
        }
    }
}

void insertFirst(List &L, adrList p){
    if(isEmpty(L)){
        L.First = p;
        L.Last = p;
    } else {
        p->next = L.First;
        L.First->prev = p;
        L.First = p;
    }
}

//void insertAfter(List &L, adrList p){
//}

//void insertPrev(List &L, adrList p){
//}

void insertLast(List &L, adrList p){
    if(isEmpty(L)){
        insertFirst(L, p);
    } else {
        p->prev = L.Last;
        L.Last->next = p;
        L.Last = p;
    }
}

void deleteFirst(List &L, adrList &p){
    if(isEmpty(L)){
        p = nullptr;
        L.First = nullptr;
        L.Last = nullptr;
    } else {
        p = L.First;
        L.First = L.First->next;
        L.First->prev = nullptr;
        p = nullptr;
    }
}

void deleteAfter(List &L, adrList &p, adrList q){
    q->next = p;
    (p->next)->prev = q;
    q->next = p->next;

    p->next = nullptr;
    p->prev = nullptr;
}

void deletePrev(List &L, adrList &p, adrList q){
    q->prev = p;
    (p->prev)->next = q;
    q->prev = p->prev;

    p->next = nullptr;
    p->prev = nullptr;
}

void deleteLast(List &L, adrList &p){
    if(isEmpty(L)){
        p = nullptr;
        L.First = nullptr;
        L.Last = nullptr;
    } else {
        p = L.Last;
        L.Last = L.Last->prev;
        L.Last->next = nullptr;
        p = nullptr;
    }
}

void deleteNodeList(List &L, adrList p){
    if(p == nullptr) return;

    if(p == L.First && p == L.Last){
        L.First = nullptr;
        L.Last = nullptr;
    }else if(p == L.First){
        L.First = p->next;
        (L.First)->prev=nullptr;
    }else if(p == L.Last){
        L.Last = p->prev;
        (L.Last)->next = nullptr;
    }else{
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }
    delete p;
}

void joinNodeToTree(List &L, adrList opNode){
    adrList kiri = opNode->prev;
    adrList kanan = opNode->next;

    if (kiri != nullptr && kanan != nullptr) {
        // 1. Sambungkan Tree Node
        // Operator menunjuk ke tree milik node kiri dan kanan DLL
        opNode->treeNode->left = kiri->treeNode;
        opNode->treeNode->right = kanan->treeNode;

        // 2. Hapus node kiri dan kanan dari DLL
        // (karena mereka sudah masuk/dicaplok ke dalam tree operator)
        deleteNodeList(L, kiri);  // <-- Perbaikan nama fungsi
        deleteNodeList(L, kanan); // <-- Perbaikan nama fungsi
    }
}

address buildTreeFromDLL(List &L) {
    if (isEmpty(L)) return nullptr;

    // === PASS 1: Prioritas Tinggi (Kali dan Bagi) ===
    adrList P = L.First;
    while (P != nullptr) {
        // SAFETY CHECK: Pastikan treeNode tidak NULL sebelum akses info
        if (P->treeNode != nullptr) {
            string val = P->treeNode->info;

            if (val == "*" || val == "/") {
                joinNodeToTree(L, P);
                // Setelah join, struktur berubah. Pindah ke node selanjutnya yang valid.
                P = P->next;
            } else {
                P = P->next;
            }
        } else {
            // Jika treeNode null (node sampah), lewati saja
            P = P->next;
        }
    }

    // === PASS 2: Prioritas Rendah (Tambah dan Kurang) ===
    P = L.First;
    while (P != nullptr) {
        // SAFETY CHECK: Sama seperti di atas
        if (P->treeNode != nullptr) {
            string val = P->treeNode->info;

            if (val == "+" || val == "-") {
                joinNodeToTree(L, P);
                P = P->next;
            } else {
                P = P->next;
            }
        } else {
            P = P->next;
        }
    }

    // Jika sukses, list tinggal menyisakan 1 node, itulah Root Tree-nya
    if (L.First != nullptr) {
        return L.First->treeNode;
    }
    return nullptr;
}
