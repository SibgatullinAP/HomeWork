#ifndef LIST_H
#define LIST_H

#include "listNode.h"

class List
{
	private:
        ListNode *Head = nullptr;
        ListNode *Current = nullptr;
	public:
		List ()  = default;
		~List ();    

		ListNode *get_head() const
		{
			return Head;
		}
		void set_head(ListNode *head );

		void delete_list ();
        void print(FILE* out = stdout);
		int read (FILE *fp);

		ListNode* func(int shift);

};
#endif
