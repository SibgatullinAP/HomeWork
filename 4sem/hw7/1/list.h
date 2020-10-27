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
        int Length = 0;

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

		void addBeforeHead(ListNode*);
		void addR(ListNode *src);
		ListNode* moveFromList(ListNode*);
		void addHead(ListNode*);

		//BubleSort
		void bubbleSort(bool (*comp)(ListNode*, ListNode*));

		//Maximum finding sort
        void maxFinSort(bool (*comp)(ListNode*, ListNode*));

        //Minimum finding sort
        void minFinSort(bool (*comp)(ListNode*, ListNode*));

		//Linear insertion sort
		void linInsSort(bool (*comp)(ListNode*, ListNode*));
        void linIns(ListNode*, bool (*comp)(ListNode*, ListNode*));

        //Merge sort
        void mergeSort (bool (*comp)(ListNode*, ListNode*));
        ListNode *merge(ListNode *first, ListNode *second, ListNode *last, bool (*comp)(ListNode*, ListNode*));
        ListNode *getCurNext (ListNode *node, int step);

        //Quicksort
        void quickSort(ListNode* head, ListNode *first, ListNode *last, ListNode *prev_first, bool (*comp)(ListNode*, ListNode*));
        void callQuickSort(bool (*comp)(ListNode*, ListNode*));
};
#endif
