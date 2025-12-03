#include "tree.h"

address alokasi(infotype x){
    address p = new Node;
    if(p != nullptr){
        p->info = x;
        p->left = nullptr;
        p->right = nullptr;
    }
    return p;
}
void createTree(address &root){
    root = nullptr;
}

// Cek apakah angka atau operator
bool isLeaf(address p){
    // Kalo ga punya anak di kiri dan kanan maka dia angka
    return (p->left == nullptr && p->right == nullptr);
}

// Hitung hasil
int evaluate(address p){
    if(p == nullptr) return 0;

    // Kalo nodenya angka, maka kembalikan nilainya
    if(isLeaf(p)) return stoi(p->info); // Konversi dari char ke int

    // Kalo nodenya operator maka hitung anak kiri lalu anak kanan
     int leftTotal = evaluate(p->left);
     int rightTotal = evaluate(p->right);

     if(p->info == "+") return leftTotal + rightTotal;
     if(p->info == "-") return leftTotal - rightTotal;
     if(p->info == "*") return leftTotal * rightTotal;
     if(p->info == "/") {
        if (leftTotal == 0 || rightTotal == 0) return 0;
            return leftTotal / rightTotal;
     }

     return 0;
}
void printInOrder(address p){
    if(p != nullptr){
        printInOrder(p->left);
        cout << p->info << " ";
        printInOrder(p->right);
    }
}
