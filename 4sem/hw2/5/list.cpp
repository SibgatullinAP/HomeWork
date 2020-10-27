#include "student.h"
#include "listNode.h"
#include "list.h"
#include "addons.h"


List::~List()
{
    delete_list();
}

void List::delete_list ()
{
        while(head)
        {
            current = head;
            head = head -> next;
            delete current;
        }
        delete head;
}

int List::read (FILE *fp)
{
	delete_list ();

    ListNode *next;
    next = new ListNode ();
    if (next == nullptr)
    {
        return ERROR_CANNOT_ALLOCATE_MEMMORY;
    }

    int ret = next -> read (fp);
    if (ret < 0)
    {
        return delete next, ret;
    }
    if(ret > 0)
    {
        return delete next, NOT_ERROR_END_OF_INPUT;
    }

	head = current = next; 

	for (;;)
	{
            next = new ListNode ();
            if (next == nullptr)
            {
                return ERROR_CANNOT_ALLOCATE_MEMMORY;
            }

            ret = next -> read (fp);
            if (ret < 0)
            {
                return delete next, ret;
            }
            if(ret > 0)
            {
                return delete next, NOT_ERROR_END_OF_INPUT;
            }
            current -> next = next;
            current = next;
            next = nullptr;
	}
	return 0;
}

void List:: print(FILE* out)
{
    current = head;

    for (int i = 0; current && i < MAX_PRINT; i ++)
    {
        current -> print(out);
        current = current -> next;
    }
}















