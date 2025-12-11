#include "tree.h"

address allocateTree(infotype x){
    address p = new Node;
    p->info = x;
    p->left = nullptr;
    p->right = nullptr;
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

// Traversal
void printInOrder(address p){
    if(p != nullptr){
        printInOrder(p->left);
        cout << p->info << " ";
        printInOrder(p->right);
    }
}
void printPreOrder(address p){
    if(p!=nullptr){
        cout << p->info << " ";
        printPreOrder(p->left);
        printPreOrder(p->right);
    }
}
void printPostOrder(address p){
    if(p!=nullptr){
        printPostOrder(p->left);
        printPostOrder(p->right);
        cout << p->info << " ";
    }
}

// Mencari node tertentu dalam tree
address findNode(address root, string val) {
    if (root == nullptr) return nullptr;

    // Cek apakah node saat ini adalah yang dicari
    if (root->info == val) return root;

    // cari di subtree kiri
    address found = findNode(root->left, val);
    if (found != nullptr) return found;

    //subtree kanan
    return findNode(root->right, val);
}

// Mencari node operator dalam tree
address findOperatorByOrder(address root, int targetOrder, int &count) {
    if (root == nullptr) return nullptr;

    // Traverse subtree kiri
    address found = findOperatorByOrder(root->left, targetOrder, count);
    if (found != nullptr) return found;

    // Cek node saat ini
    if (root->info == "+" || root->info == "-" || root->info == "*" || root->info == "/") {
        count++;
        if (count == targetOrder) return root;
    }

    // Traverse subtree kanan
    return findOperatorByOrder(root->right, targetOrder, count);
}

// Mengupdate nilai info pada node
void updateNode(address p, string newVal) {
    if (p != nullptr) p->info = newVal;
}

address copyTree(address root) {
    if (root == nullptr) {
        return nullptr;
    }

    // 1. Buat node baru dengan info yang sama
    address newNode = allocateTree(root->info);

    // 2. Salin anak kiri dan kanan secara rekursif
    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);

    return newNode;
}

// Fungsi untuk menghapus seluruh tree (agar memori tidak bocor saat ditimpa)
void deleteAllNodes(address &root) {
    if (root == nullptr) return;

    // Hapus anak-anak dulu (Post-Order delete)
    deleteAllNodes(root->left);
    deleteAllNodes(root->right);

    // Hapus node itu sendiri
    delete root;
    root = nullptr;
}

// Konversi Tree ke String (In-Order traversal)
string treeToString(address p) {
    if (p == nullptr) return "";

    if (isLeaf(p)) return p->info;

    // Format: (kiri operator kanan)
    return treeToString(p->left) + " " + p->info + " " + treeToString(p->right);
}
