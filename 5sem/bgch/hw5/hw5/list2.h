#ifndef LIST2_H
#define LIST2_H

#include "list2_node.h"

class list2
{
private:
  list2_node * head = nullptr;
  list2_node * current = nullptr;

  static int m;
  static int r;

public:
  list2 () = default;
  ~list2 ();

  void destroy ();

  int get_length () const;
  bool is_empty () const;

  int read (FILE * fp);
  bool add (list2_node *tmp);
  void print () const;

  int operator< (const list2& b) const;
  int operator> (const list2& b) const;

  static void set_m (int m) { list2::m = m; }
  static void set_r (int r) { list2::r = r; }
};

#endif // LIST2_H
