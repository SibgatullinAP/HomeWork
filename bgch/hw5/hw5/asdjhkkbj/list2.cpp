#include "list2.h"

int list2::m;
int list2::r;

list2::~list2 ()
{
  destroy ();
}

void list2::destroy ()
{
  list2_node *tmp = nullptr;
  while (head)
    {
      tmp = head;
      head = head->next;
      delete tmp;
    }

  delete head;
}

bool list2::add (list2_node *tmp)
{
  if (tmp == nullptr)
    return false;

  if (head == nullptr)
    {
      head = tmp;
      head->prev = nullptr;
      head->next = nullptr;
      current = head;

      return true;
    }

  if (current == nullptr)
    return false;

  current->next = tmp;
  tmp->prev = current;
  current = tmp;
  current->next = nullptr;

  return true;
}

int list2::read (FILE * fp)
{
  current = head;
  list2_node *tmp = nullptr;

  int read_counter = m;
  if (read_counter > 0)
    {
      while (read_counter > 0)
        {
          tmp = new list2_node;
          int ret = tmp->read (fp);
          if (ret != SUCCESS)
            {
              delete tmp;
              return ret;
            }

          if (!add (tmp))
            return ERROR_INTERNAL_ERROR_LIST2;

          read_counter--;
        }
    }
  else
    {
      while (true)
        {
          tmp = new list2_node;
          int ret = tmp->read (fp);
          if (ret != SUCCESS)
            {
              delete tmp;
              return ret;
            }

          if (!add (tmp))
            return ERROR_INTERNAL_ERROR_LIST2;
        }
    }

  current = head;

  return SUCCESS;
}

void list2::print () const
{
  list2_node *tmp = head;
  int print_counter = r;
  if (print_counter > 0)
    {
      printf ("\n--------\n");
      while (tmp && print_counter > 0)
        {
          tmp->print ();
          tmp = tmp->next;
          print_counter--;
        }
      printf ("--------\n");
    }
  else
    {
      printf ("\n--------\n");
      while (tmp)
        {
          tmp->print ();
          tmp = tmp->next;
        }
      printf ("--------\n");
    }
}

int list2::get_length () const
{
  list2_node *tmp = head;
  int i = 0;
  for (; tmp; i++, tmp = tmp->next);
  return i;
}

bool list2::is_empty () const
{
  return ((head == nullptr) ? true : false);
}


int list2::operator< (const list2& b) const
{
  if ((is_empty () && b.is_empty ()))
    return false;

  if (is_empty ())
    return true;

  if (b.is_empty ())
    return false;

  return *head < *b.head;
}

int list2::operator> (const list2& b) const
{
  if ((is_empty () && b.is_empty ()))
    return false;

  if (is_empty ())
    return false;

  if (b.is_empty ())
    return true;

  return *head > *b.head;
}

