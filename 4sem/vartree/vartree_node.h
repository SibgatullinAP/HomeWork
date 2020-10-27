#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <stdio.h>
#include "../student/student.h"

class vartree_node;
class vartree;

class vartree_node
{
private:
    int size = 0; // кол-во детей
    student **data = nullptr;
    vartree_node **keys = nullptr;
    
    friend class vartree;

public:
    vartree_node() = default;
    vartree_node(int k);
    ~vartree_node();
    
    int search(student *);
    void print();
};

#endif
