#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "student.h"
#include <stdio.h>

class List;
class ListNode;
class ListNode: public Student
{
	private:
        ListNode *Next = nullptr;
	public:
        friend class List;
        ListNode * get_next () const
        {
            return Next;
        }
        void set_next (ListNode *next)
        {
            this -> Next = next;
        }    
};

#endif
