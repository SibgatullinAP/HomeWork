#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "tree.h"
#include <stdio.h>

class ListNode;
class List;
class ListNode: public Tree
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
                void set_next (ListNode *next)
                {
                    this -> Next = next;
                }
                void set_prev (ListNode *prev)
                {
                    this -> Previous = prev;
                }
};

#endif
