#include "stack.h"

void createStack(Stack &s){
    s.top = nullptr;
}
bool isEmptyStack(Stack s){
    return s.top == nullptr;
}
 // Buat push pointer tree ke stack
 // YANG DI PUSH ADALAH POINTER TREE
void push(Stack &s, infoStack pTree){
    adrStack p = new elmStack;
    p->info = pTree;
    p->next = s.top;
    s.top = p;
}
void pop(Stack &s, infoStack &pTree){
    if(!isEmptyStack(s)){
        adrStack p = s.top;
        pTree = p->info; // Nyimpen alamat node, soalnya p mau dihapus
        s.top = s.top->next;
        delete p;
    }
}
