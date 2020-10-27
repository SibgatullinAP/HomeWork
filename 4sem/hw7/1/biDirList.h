#ifndef LIST_H
#define LIST_H

#include "biDirListNode.h"
#include "student.h"
#include "addons.h"

class List
{
	private:
        ListNode *Head = nullptr;
        ListNode *Current = nullptr;
        ListNode *Tail = nullptr;
        int Length = 0;

	public:
		List ()  = default;
		~List ();

		ListNode *get_head() const
		{
			return Head;
		}

		void delete_list ();
        void print(FILE* out = stdout);
		int read (FILE *fp);
		int get_len()
		{
			return Length;
		}

		void delete_head();
		void addBeforeHead(ListNode*);
		void addAfterHead(ListNode*);
		void addAfterTail(ListNode*);
		ListNode* moveFromList(ListNode*);
		void delete_current();
		void addL(ListNode *dest, ListNode *src);
		void addR(ListNode *dest, ListNode *src);

        //Bubblesort
		void swap(ListNode *, ListNode*);
		void bubbleSort0(bool (*comp)(ListNode*, ListNode*));
		void bubbleSort(bool (*comp)(ListNode*, ListNode*));

        //Maximum finding sort
        void maxFinSort(bool (*comp)(ListNode*, ListNode*));
        ListNode* maxFin(bool (*comp)(ListNode*, ListNode*));

        //Minimum finding sort
		void minFinSort(bool (*comp)(ListNode*, ListNode*));
        ListNode* minFin(bool (*comp)(ListNode*, ListNode*));

        //Linear insertion sort
        void linInsSort(bool (*comp)(ListNode*, ListNode*));
        void linIns(ListNode*, bool (*comp)(ListNode*, ListNode*));

        //Merge sort
        void mergeSort (bool (*comp)(ListNode*, ListNode*));
        ListNode *merge(ListNode *first, ListNode *second, ListNode *last, bool (*comp)(ListNode*, ListNode*));
        ListNode *getCurNext (ListNode *node, int step);

        void quickSort(ListNode* head, ListNode *first, ListNode *last, bool (*comp)(ListNode*, ListNode*));
        void callQuickSort(bool (*comp)(ListNode*, ListNode*));

		/*void callMergeSortRecur(bool (*comp)(ListNode*, ListNode*));
		void mergeSort(ListNode**, bool (*comp)(ListNode*, ListNode*));
		ListNode* mergeLists(ListNode* a, ListNode* b, bool (*comp)(ListNode*, ListNode*));
		void partition(ListNode* , ListNode **, ListNode **);

		void mergeSort1(bool (*comp)(ListNode*, ListNode*));
		void merge(ListNode* start1, ListNode* end1, ListNode* start2, ListNode* end2, bool (*comp)(ListNode*, ListNode*));
        void swapMerge(ListNode*, ListNode*);

        ListNode* partitionQuick(ListNode *l, ListNode *h, bool (*comp)(ListNode*, ListNode*));
        void quickSort(bool (*comp)(ListNode*, ListNode*));
        void quickSortRec(ListNode* l, ListNode *h, bool (*comp)(ListNode*, ListNode*));
        */
};

#endif
