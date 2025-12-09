#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <iostream>
using namespace std;

// Tipe data Tree
typedef string infotype;
typedef struct Node *address;

struct Node{
    infotype info;
    address left;
    address right;
};

// Fungsi dasar Tree
address allocateTree(infotype x);
void createTree(address &root);
bool isLeaf(address p); // Cek apakah angka atau operator
int evaluate(address p); // Hitung hasil

// Traversal
void printInOrder(address p);
void printPreOrder(address p);
void printPostOrder(address p);

// Copy Tree
address copyTree(address root);
void deleteAllNodes(address &root);
string treeToString(address root);

// Edit & Search
address findNode(address root, string val);
void updateNode(address p, string newVal);

#endif // TREE_H_INCLUDED
