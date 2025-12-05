#include "TLL.h"
#include "tree.h"
#include <iostream>

using namespace std;

void createTList(TList &T){
    T.first = nullptr;
}

bool isEmpty(TList T){
    return T.first == nullptr;
}

adrTList allocate(infotype x){
    adrTList p = new elmTList;

    p->info = x;
    p->next = nullptr;

    return p;
}

void printInfo(TList T){
    if (isEmpty(T)){
        cout << "List Kosong" << endl;
    } else {
        adrTList p = T.first;
        int count = 1;
        while (p != nullptr) {
            cout << count << ". ";
            printInOrder(p->info);
            cout << endl;
        }
    }
}

void insertFirst(TList &T, adrTList p){
    if (isEmpty(T)){
        T.first = p;
    } else {
        p->next = T.first;
        T.first = p;
    }
}

void insertAfter(TList &T, adrTList p){
}

void insertPrev(TList &T, adrTList p){
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

void deleteFirst(TList &T, adrTList p){
}

void deleteAfter(TList &T, adrTList &p, adrTList q){
}

void deletePrev(TList &T, adrTList p){
}
