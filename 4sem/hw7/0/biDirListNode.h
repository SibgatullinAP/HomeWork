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
                ListNode *Previous = nullptr;
	public:
                friend class List;
                ListNode *get_next () const
                {
                    return Next;
                }
                ListNode *get_prev () const
                {
                    return Previous;
                }
                void set_next (ListNode *next) // хз нахуй она нужна , там скорее всего придется делать другую
                {
                    this -> Next = next;
                }
                void set_prev (ListNode *prev) // хз нахуй она нужна , там скорее всего придется делать другую
                {
                    this -> Previous = prev;
                }
};

#endif
