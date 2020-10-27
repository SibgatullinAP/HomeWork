#ifndef LIST_H
#define LIST_H

#include "listNode.h"
#include "string.h"

class List
{
	private:
        ListNode *Head = nullptr;
        ListNode *Current = nullptr;
        ListNode *Tail = nullptr;

	public:
        List ()  = default;
        ~List ();
        ListNode *get_head() const
        {
            return Head;
        }

        ListNode* func(const char *s);

        void delete_list ();
        void print(FILE* out = stdout);
        int read (FILE *fp);
        void delete_head();
        void addBeforeHead(ListNode*);
        void addAfterHead(ListNode*);
        void addAfterTail(ListNode*);
        ListNode* moveFromList(ListNode*);
        void delete_current();
        void addL(ListNode *dest, ListNode *src);
        void addR(ListNode *dest, ListNode *src);
	void addHead(ListNode* a);
};

#endif
