#include <bits/stdc++.h>
#include <iostream>
#include "tree.h"
#include "DLL.h"
#include "TLL.h"
#include "cctype"

using namespace std;

int menu(int input){
    cout << "=== My Calkulator ===" << endl;
    cout << "1. Masukan Operasi Matematika" << endl;
    cout << "2. Edit Operasi Matematika" << endl;
    cout << "3. Hapus Operasi Matematika" << endl;
    cout << "4. Gabung Operasi Matematika" << endl;
    cout << "5. Print Hasil Operasi Matematika" << endl;
    cout << "0. Keluar" << endl;
    cout << "Jawaban (0-5): ";
    cin >> input;
    return input;
}

// INFO :
// List total ada 2.
// satu temporary buat simpen operasi matematika lalu push ke tree
// satu buat save history operasi matematika

int main() {
    List L;
    TList T;
    //address R;
    //createTree(R);
    createList(L);
    string input;
    int in;
    string del = " ";
    adrList p;

    in = menu(in);

    while (in != 0){
        switch (in) {
            case 0:
                cout << "Anda Keluar." << endl;
                break;
            case 1: {
                cout << "Masukan operasi matematika: ";
                getline(cin, input); // read full line
                auto pos = input.find(del); // Find first occurrence of the delimiter
                while (pos != string::npos) { // While there are still delimiters in the string
                    p = allocate(input.substr(0, pos)); // Extracting the substring up to the delimiter
                    insertLast(L, p);
                    input.erase(0, pos + del.length()); // Erase the extracted part from the original string
                    pos = input.find(del); // Find the next occurrence of the delimiter
                }
                p = allocate(input); //allocate last substring
                insertLast(L, p);
                in = menu(in);
                break;
            }
            case 2: {
                printInfo(T);
                cout << "Pilih operasi yang ingin diedit: ";
                getline(cin, input);
                in = menu(in);
                break;
            }
            case 3: {
                printInfo(T);
                cout << "Pilih operasi yang ingin dihapus: ";
                getline(cin, input);
                in = menu(in);
                break;
            }
            case 4: {// incomplete
                printInfo(T);
                cout << "Pilih 2 operasi yang ingin digabung (cth: 1 2): ";
                getline(cin, input);
                auto pos = input.find(del); // Find first occurrence of the delimiter
                while (pos != string::npos) { // While there are still delimiters in the string
                    //input.substr(0, pos); // Extracting the substring up to the delimiter
                    input.erase(0, pos + del.length()); // Erase the extracted part from the original string
                    pos = input.find(del); // Find the next occurrence of the delimiter
                }
                //
                in = menu(in);
                break;
            }
            case 5: {
                printInfo(T);
                in = menu(in);
                break;
            }
            default: {
                cout << "Input salah" << endl;
                in = menu(in);
                break;
            }
        }
    }

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
