#ifndef TREENODE_H
#define TREENODE_H

#include "record.h"

class Tree;

class TreeNode: public Record
{
    TreeNode * LeftChild = nullptr;
    TreeNode * RightChild = nullptr;
    TreeNode * Parent = nullptr;
    TreeNode * Next = nullptr;
    color Color = RED;

public:

    friend class Tree;

    TreeNode() = default;
    ~TreeNode() = default;

};

#endif // TREENODE_H


