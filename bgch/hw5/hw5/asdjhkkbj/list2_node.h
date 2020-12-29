#ifndef LIST2_NODE_H
#define LIST2_NODE_H

#include "student.h"

class list2;

class list2_node : public student
{
private:
  list2_node *next = nullptr;
  list2_node *prev = nullptr;

public:
  list2_node () = default;
  list2_node (char *name, int value);
  ~list2_node () = default;

  list2_node * get_next () const;
  list2_node * get_prev () const;

  friend class list2;
};

#endif // LIST2_NODE_H
