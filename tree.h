#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <iostream>
using namespace std;

// Tipe data Tree
typedef char infotype;
typedef struct Node *address;

struct Node{
    infotype info;
    address left;
    address right;
};

// Fungsi dasar Tree
address alokasi(infotype x);
void createTree(address &root);
bool isLeaf(address p); // Cek apakah angka atau operator
int evaluate(address p); // Hitung hasil
void printInOrder(address p);

#endif // TREE_H_INCLUDED
