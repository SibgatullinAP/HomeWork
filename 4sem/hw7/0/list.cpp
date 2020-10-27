#include "list.h"

List::~List()
{
    delete_list();
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
            Current = tmp;
            Current -> Next = nullptr;
            tmp = nullptr;
	}
	return 0;
}

void List::print(FILE* out)
{
    Current = Head;

    for (int i = 0; Current && i < MAX_PRINT; i ++)
    {
        Current -> print(out);
        Current = Current -> Next;
    }
}














