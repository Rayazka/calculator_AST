#ifndef DLL_H_INCLUDED
#define DLL_H_INCLUDED

#include "tree.h"

typedef struct elmList *adrList; // pointer ke tree

struct elmList{
    address treeNode;
    adrList next;
    adrList prev;
};

struct List{
    adrList First;
    adrList Last;
};

// Basic
void createList(List &L);
bool isEmpty(List L);
adrList allocateDLL(address node);
void printInfo(List L);

void insertFirst(List &L, adrList p);
void insertAfter(List &L, adrList p);
void insertPrev(List &L, adrList p);
void insertLast(List &L, adrList p);

void deleteFirst(List &L, adrList p);
void deleteAfter(List &L, adrList &p, adrList q);
void deletePrev(List &L, adrList &p, adrList q);
void deleteLast(List &L, adrList p);

// untuk menghapus node dari List (tanpa menghapus tree-nya)
void deleteNodeList(List &L, adrList p);

// Menggabungkan node kiri dan kanan dengan operator
void joinNodeToTree(List &L, adrList opNode);


// Mengubah List DLL menjadi Satu Root Tree
address buildTreeFromDLL(List &L);


// void pushToTree(List &L, adrList &root); // ubah list ke tree

#endif // DLL_H_INCLUDED
