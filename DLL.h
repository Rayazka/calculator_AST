#ifndef DLL_H_INCLUDED
#define DLL_H_INCLUDED

#include "tree.h"

typedef string infotype; // Info di DLL adalah string
typedef struct elmList *adrList;

struct elmList{
    infotype info;
    adrList next;
    adrList prev;
};

struct List{
    adrList First;
    adrList Last;
};

void createList(List &L);
bool isEmpty(List L);
adrList allocate(infotype x);
void printInfo(List L);

void insertFirst(List &L, adrList p);
//void insertAfter(List &L, adrList p);
//void insertPrev(List &L, adrList p);
void insertLast(List &L, adrList p);

void deleteFirst(List &L, adrList p);
void deleteAfter(List &L, adrList &p, adrList q);
void deletePrev(List &L, adrList &p, adrList q);
void deleteLast(List &L, adrList p);

void pushToTree(List &L, adrList root);

#endif // DLL_H_INCLUDED
