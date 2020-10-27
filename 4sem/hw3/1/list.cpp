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


ListNode* List::func(Student s)
{
    ListNode *next = nullptr, *prev = Head, *current = Head;

    if(head == nullptr)
    {
        return head;
    }

    current = current -> get_next();
    next = current -> get_next();
    if(next && current && ((*current) > s))
    {
        set_head(current);
        prev -> Next = next;
        next -> Previous = prev;
    }
    else if (current && ((*current) > s))
    {
        set_head(current);
        prev -> Next = nullptr;
    }
    while(next)
    {
        prev = current -> get_prev();
        if(*current > s)
        {
            prev -> Next = next;
            next -> Previous = prev;
            set_head(current);

        }
        current = next;
        next = current -> get_next();
    }
    if(current && (*current) > s)
    {
        set_head(current);
        prev -> Next = nullptr;

    }
    next = prev = current = nullptr;
    return head;
}















