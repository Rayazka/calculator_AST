#ifndef TLL_H_INCLUDED
#define TLL_H_INCLUDED

#include "tree.h"

typedef struct elmTList *adrTList;

struct elmTList{
    Node* info;
    adrTList next;
};

struct TList{
    adrTList first;
};

void createTList(TList &T);
bool isEmpty(TList T);
adrTList allocate(infotype x);
void printInfo(TList T);

void insertFirst(TList &T, adrTList p);
void insertAfter(TList &T, adrTList p);
void insertPrev(TList &T, adrTList p);
void insertLast(TList &T, adrTList p);

void deleteFirst(TList &T, adrTList p);
void deleteAfter(TList &T, adrTList &p, adrTList q);
void deletePrev(TList &T, adrTList &p, adrTList q);
void deleteLast(TList &T, adrTList p);

#endif // TLL_H_INCLUDED
