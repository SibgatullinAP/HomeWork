#include "list2_node.h"

list2_node::list2_node (char *name, int value) : student (name, value) { }

list2_node * list2_node::get_next () const
{
  return next;
}

list2_node * list2_node::get_prev () const
{
  return prev;
}
