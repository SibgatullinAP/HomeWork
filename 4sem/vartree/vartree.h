#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include "../student/student.h"

#define PRINT_LEVEL 3
#define PRINT_CHILD 4

class vartree_node;

class vartree
{
private:
    vartree_node *current = nullptr;
    vartree_node *root = nullptr;
    int ord = 0;
    int keysize = 0;
    
    int paste_proc(vartree_node *, student *&, vartree_node *&);
    void print_proc(vartree_node *start, int level, int index);

public:
    vartree(int ord = 0) { this->ord = ord; this->keysize = 2*ord + 1; }
    ~vartree() { deleteTree(root); current = root = nullptr; }
    void deleteTree(vartree_node *);
    
    int read(FILE *);
    int paste(student *);
    void print() { print_proc(root, 0, 0); }
};

#endif
