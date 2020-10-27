#ifndef LIST_H
#define LIST_H

#include "listNode.h"

class List
{
	private:
        ListNode *head = nullptr;
        ListNode *current = nullptr;
	public:
		List ()  = default;
		~List ();

		void delete_list ();
        void print(FILE* out = stdout);
		int read (FILE *fp);
		
		ListNode* get_head ()
		{
			return head;
		}

};
#endif
