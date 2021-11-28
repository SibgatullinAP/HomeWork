#ifndef TREE_NODE_H
#define TREE_NODE_H

#include "list2.h"

template <class T> class tree;

template <class T>
class tree_node : public T
{
private:
  tree_node * left = nullptr;
  tree_node * right = nullptr;
public:
  tree_node () = default;
  ~tree_node () = default;

  friend class tree<T>;
};

#endif // TREE_NODE_H
