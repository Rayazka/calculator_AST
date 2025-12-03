#include "DLL.h"
#include "cctype"
#include <iostream>

void createList(List &L){
    L.First = nullptr;
    L.Last = nullptr;
}

bool isEmpty(List L){
    return L.First == nullptr && L.Last == nullptr;
}

adrList allocate(infotype x){
    adrList p = new elmList;
    p->info = x;
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
            cout << p->info;
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

void pushToTree(List &L, adrList root){
}
