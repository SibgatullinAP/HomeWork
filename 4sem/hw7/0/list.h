#ifndef LIST_H
#define LIST_H

#include "listNode.h"
#include "student.h"
#include "addons.h"

class List
{
	private:
        ListNode *Head = nullptr;
        ListNode *Current = nullptr;
	public:
		List ()  = default;
		~List ();

		void delete_list ();
        void print(FILE* out = stdout);
		int read (FILE *fp);

		
		ListNode* get_head () const
		{
			return Head;
		}

		void swap(ListNode *);
		void bubbleSort(bool (*comp)(ListNode*, ListNode*));
		void bubbleSort0(bool (*comp)(ListNode*, ListNode*));
};
#endif
