#include <bits/stdc++.h>
#include <iostream>
#include "tree.h"
#include "DLL.h"
#include "cctype"

using namespace std;

int main() {
    List L;
    //address R;
    //createTree(R);
    createList(L);
    string input;
    string del = " ";
    adrList p;

    cout << "=== My Calkulator ===" << endl;
    cout << "Masukan operasi matematika: ";
    getline(cin, input); // read full line

    // Find first occurrence of the delimiter
    auto pos = input.find(del);

    // While there are still delimiters in the
  	// string
    while (pos != string::npos) {

        // Extracting the substring up to the
      	// delimiter
        p = allocate(input.substr(0, pos));
        insertLast(L, p);

        // Erase the extracted part from the
      	// original string
        input.erase(0, pos + del.length());

        // Find the next occurrence of the
      	// delimiter
        pos = input.find(del);
    }

    //allocate last substring
    p = allocate(input);
    insertLast(L, p);

    printInfo(L); //placeholder: cek kode



    // Step 5: Ketemu '+', Pop dua node teratas (sub-tree tadi dan 3)
    //p = alokasi('+');
    //pop(s, n2);    // Pop kanan (sub-tree 5*2)
    //pop(s, n1);
    //p->right = n2;
    //p->left = n1;
    //push(s, p);       // Tree utuh ada di puncak stack

    // Ambil Root Tree dari Stack
    //address root;
    //pop(s, root);

    //cout << "In-Order Traversal (Bentuk Matematika): ";
    //printInOrder(root);
    //cout << endl;

    //cout << "Hasil Perhitungan: " << evaluate(root) << endl;
}
