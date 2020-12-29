#include "student.h"

student::student (char *name_, int value_)
{
  init (name_, value_);
}

student::~student ()
{
  if (!is_empty())
    delete [] name;

  value = 0;
}

int student::read (FILE *fp)
{
  char name_[BUFF_LEN];
  int value_ = 0;

  if (fscanf (fp, "%s %d\n", name_, &value_) != 2)
    {
      if (feof(fp))
        return END_OF_FILE;

      return ERROR_CANNOT_READ_FILE;
    }

  int ret = init (name_, value_);
  if (ret < 0)
    return ERROR_INTERNAL_ERROR_STUDENT;

  return SUCCESS;
}

bool student::init (char *name_, int value_)
{
  if (set_name(name_))
    {
      set_value(value_);
      return true;
    }
  return false;
}

bool student::is_empty () const
{
  return ((name == nullptr) ? true : false);
}

int student::get_length () const
{
  return (int) !is_empty ();
}

void student::print () const
{
  if (!is_empty ())
    printf ("%-15s %-10d\n", name, value);
  else
    printf ("(null) %d\n", value);
}

bool student::operator< (const student &b) const
{
  if ((is_empty () && b.is_empty ()))
    return value < b.value;

  if (is_empty ())
    return true;

  if (b.is_empty ())
    return false;

  int cmp = strcmp (name, b.name);
  if (cmp < 0)
    return true;
  else if (cmp > 0)
    return false;
  else
    return value < b.value;
}

bool student::operator> (const student &b) const
{

  if ((is_empty () && b.is_empty ()))
    return value > b.value;

  if (is_empty ())
    return false;

  if (b.is_empty ())
    return true;

  int cmp = strcmp (name, b.name);
  if (cmp < 0)
    return false;
  else if (cmp > 0)
    return true;
  else
    return value > b.value;
}

int student::get_value () const
{
  return value;
}

void student::set_value (int value_)
{
  value = value_;
}

char * student::get_name () const
{
  return name;
}

bool student::set_name (char *name_)
{
  if (name_ != nullptr)
    {
      delete [] name;

      int len = strlen (name_) + 1;
      name = new char [len];
      if (name == nullptr)
        return false;

      memcpy (name, name_, len);
      name[len - 1] = 0;

      return true;
    }
  return false;
}

