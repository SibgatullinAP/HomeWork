#include "vartree_node.h"

#define PRINT_VALUE 3

vartree_node::vartree_node(int ord)
{
    ord *= 2;
    keys = new vartree_node* [ord + 1];
    data = new student* [ord];
    //
    for(int i=0; i<ord; i++) { data[i] = nullptr; keys[i] = nullptr; }
    keys[ord] = nullptr;
}

vartree_node::~vartree_node()
{
    for(int i=0; i<size; i++) delete data[i];
    //
    if(data) { delete[] data; data = nullptr; }
    if(keys) { delete[] keys; keys = nullptr; }
    size = 0;
}

int vartree_node::search(student *x)
{
    int left = 0, right = size, s;
    //
    while(right != left)
    {
        //s = (left + right) >> 1;
        s = (left + right)/2;
        if(*x > *data[s]) left = s + 1;
        else right = s;
    }
    return right;
}

void vartree_node::print()
{
    int l = size < PRINT_VALUE ? size : PRINT_VALUE;
    //
    for(int i = 0; i < l - 1; i++) data[i]->print();
    //
    if(l != size) printf("...");
    if(l) data[l - 1]->print();
}












