#include "student.h"
#include "listNode.h"
#include "list.h"
#include "addons.h"


List::~List()
{
    delete_list();
}

void List::set_head(ListNode *head )
{
    head -> Next = Head;
    Head = head;
    head -> Previous = nullptr;
}

void List::delete_list ()
{
        while(Head)
        {
            Current = Head;
            Head = Head -> Next;
            delete Current;
        }
        delete Head;
}

int List::read (FILE *fp)
{
	delete_list ();

    ListNode *tmp;
    tmp = new ListNode ();
    if (tmp == nullptr)
    {
        return ERROR_CANNOT_ALLOCATE_MEMMORY;
    }

    int ret = tmp -> read (fp);
    if (ret < 0)
    {
        return delete tmp, ret;
    }
    if(ret > 0)
    {
        return delete tmp, NOT_ERROR_END_OF_INPUT;
    }

	Head = Current = tmp; 

	for (;;)
	{
            tmp = new ListNode ();
            if (tmp == nullptr)
            {
                return ERROR_CANNOT_ALLOCATE_MEMMORY;
            }

            ret = tmp -> read (fp);
            if (ret < 0)
            {
                return delete tmp, ret;
            }
            if(ret > 0)
            {
                return delete tmp, NOT_ERROR_END_OF_INPUT;
            }
            Current -> Next = tmp;
            tmp -> Previous = Current;
            Current = tmp; 
            tmp = nullptr;
	}
	return 0;
}

void List:: print(FILE* out)
{
    Current = Head;

    for (int i = 0; Current && i < MAX_PRINT; i ++)
    {
        Current -> print(out);
        Current = Current -> Next;
    }
    printf("\n");
}


ListNode* List::func(int shift)
{
    if(Head == nullptr)
    {
        return nullptr;
    }

    int listLen = 1;
    ListNode *current, *next, *tail = nullptr;

    current = Head;
    next = current -> get_next();
    while(next)
    {
        listLen++;
        current = next;
        tail = current;
        next = current -> get_next();
    }

    if (listLen < shift)
    {
        shift = shift % listLen;
    }

    printf("%d\n",shift );

    current = get_head();

    Head -> print();

    listLen = 1;
    while(listLen <= 3)
    {
        next = current -> get_next();
        listLen++;
    }
    next -> print();

    Head -> Previous = tail;
    tail -> Next = Head;
    current -> Next = nullptr;
    set_head(next);

    return Head;
}















