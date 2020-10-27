#ifndef LIST_H
#define LIST_H

#include "listNode.h"

class List
{
	private:
            ListNode  *HeadSelect = nullptr;
            ListNode  *Head = nullptr;
	    ListNode  *Tail = nullptr;
	    ListNode  *Current = nullptr;

        public:
	    friend class DataBase;
	    List ()  = default;
	    ~List ();

	    int read (FILE *fp = stdin);
	    bool insert(ListNode * tmp);
	    int print(FILE * outFile);
	    ListNode * search(Command & command);

	    ListNode * getHead() const;

	    void deleteList();
	    void deleteHead();
	    void deleteCurrent();

	    ListNode * moveFromList(ListNode  *a);

	    void addHead(ListNode * a);
	    void addBeforeHead(ListNode  *a);
	    void addAfterHead(ListNode  *a);

	    void addAfterTail(ListNode  *a);

	    void addLeft(ListNode  *dest, ListNode  *src);
	    void addRight(ListNode  *dest, ListNode  *src);
};

#endif
