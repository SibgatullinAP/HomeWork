#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "student.h"
#include <stdio.h>

class List;
class ListNode;
class ListNode: public Student
{
	private:
                ListNode *next = nullptr;
	public:
                friend class List;
                ListNode * get_next () const
                {
                    return next;
                }
                void set_next (ListNode *next)
                {
                    this -> next = next;
                }
};

#endif
