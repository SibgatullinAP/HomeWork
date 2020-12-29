#ifndef STUDENT_H
#define STUDENT_H

#include "common.h"

class student
{
private:
  char *name = nullptr;
  int value = 0;

public:
  student () = default;
  student (char *name_, int value_);
  ~student ();

  bool is_empty () const;
  int get_length () const;
  bool init (char *name, int value);
  void print () const;
  int read (FILE *fp);

  bool operator< (const student &b) const;
  bool operator> (const student &b) const;

  int get_value () const;
  void set_value (int value_);

  char * get_name () const;
  bool set_name (char *name_);
};

#endif // STUDENT_H
