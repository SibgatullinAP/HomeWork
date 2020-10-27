#ifndef LIST_H
#define LIST_H

#include "listNode.h"
#include "tree.h"

class List
{
	private:
        ListNode *Head = nullptr;
        ListNode *Current = nullptr;
        ListNode *Tail = nullptr;

        enum MENU_PROPERTIES
        {
            MENU = 'm',
            EXIT = 'e',
            PRINT_LIST = 'p',
            PRINT_CURRENT = 'c',
	    PRINT_HEAD = 'o',
	    PRINT_TAIL = 'f',
            WORK_WITH_TREE = 'w',
            GO_HEAD = 'h',
            GO_LEFT = 'l',
            GO_RIGHT = 'r',
            DELETE_LEFT = 'b',
            DELETE_RIGHT = 'n',
            ADD_BEFORE_HEAD = 'y',
            DELETE_LIST = 'x',
            DELETE_CURRENT = 'd',
            ADD_LEFT = 't',
            ADD_RIGHT = 'z'
        };

	public:
        List ()  = default;
        ~List ();
        ListNode *get_head() const
        {
            return Head;
        }

        void delete_list ();
        void print(FILE* out = stdout);
        int read (FILE *fp, int size_list, int size_tree, int size_queue);
        void delete_head();
        void addBeforeHead(ListNode*);
        void addAfterHead(ListNode*);
        void addAfterTail(ListNode*);
        ListNode* moveFromList(ListNode*);
        void delete_current();
        void addL(ListNode *dest, ListNode *src);
        void addR(ListNode *dest, ListNode *src);
	void addHead(ListNode* a);
        void menu();
        void print_menu();
};

#endif
