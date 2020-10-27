#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "tree.h"
#include <stdio.h>

template <class T, template <class> class T1, template <class, template <class> class> class T2>
class List;

template <class T, template <class> class T1, template <class, template <class> class> class T2>
class ListNode: public T2 <T, T1>
{
	private:
	        ListNode <T, T1, T2> *Next = nullptr;
		ListNode <T, T1, T2> *Previous = nullptr;
	public:
		friend class List <T, T1, T2>;

		ListNode () = default;
		~ListNode()
		{
		    Next = Previous = nullptr;
		}

		ListNode <T, T1, T2> *get_next () const
                {
                    return Next;
                }
		ListNode <T, T1, T2> *get_prev () const
                {
                    return Previous;
                }
		void set_next (ListNode <T, T1, T2> *next)
                {
                    this -> Next = next;
                }
		void set_prev (ListNode <T, T1, T2> *prev)
                {
                    this -> Previous = prev;
                }
};

#endif
