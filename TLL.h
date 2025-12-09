#ifndef TLL_H_INCLUDED
#define TLL_H_INCLUDED

#include "tree.h"

typedef struct elmTList *adrTList;

struct elmTList{
    address root;
    string expression;
    int result;
    adrTList next;
};

struct TList{
    adrTList first;
};

void createTList(TList &T);
bool isEmpty(TList T);
adrTList allocateTList(address root, string exp, int res);
void showHistory(TList T);
void insertFirst(TList &T, adrTList p);

// Mengambil Tree dari History berdasarkan nomor urut
address getTreeFromHistory(TList T, int index);

// Menghapus history tertentu (beserta tree lamanya)
void deleteHistoryByIndex(TList &T, int index);

#endif // TLL_H_INCLUDED
