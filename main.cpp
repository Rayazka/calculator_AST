#include <iostream>
#include "tree.h"
#include "stack.h"

using namespace std;

int main()
{
    Stack s;
    createStack(s);
    address p, n1, n2;

    cout << "=== My Calkulator ===" << endl;

    // Step 1: Ketemu '3', Push
    push(s, alokasi('3'));

    // Step 2: Ketemu '5', Push
    push(s, alokasi('5'));

    // Step 3: Ketemu '2', Push
    push(s, alokasi('2'));

    // Step 4: Ketemu '*', Pop dua angka teratas (2 dan 5)
    p = alokasi('*');
    pop(s, n2);
    pop(s, n1);
    p->right = n2;
    p->left = n1;
    push(s, p);  // push (sub-tree 5*2) balik ke stack

    // Step 5: Ketemu '+', Pop dua node teratas (sub-tree tadi dan 3)
    p = alokasi('+');
    pop(s, n2);    // Pop kanan (sub-tree 5*2)
    pop(s, n1);
    p->right = n2;
    p->left = n1;
    push(s, p);       // Tree utuh ada di puncak stack

    // Ambil Root Tree dari Stack
    address root;
    pop(s, root);

    cout << "In-Order Traversal (Bentuk Matematika): ";
    printInOrder(root);
    cout << endl;

    cout << "Hasil Perhitungan: " << evaluate(root) << endl;
}
