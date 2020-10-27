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

    int ret = tmp->read(fp);
    if (ret < 0)
    {
        return delete tmp, ret;
    }
    if(ret > 0)
    {
        return delete tmp, ret;
    }

    Head = Current = Tail = tmp;
    for (;;)
    {
        tmp = new ListNode ();
        if (tmp == nullptr)
        {
            return ERROR_CANNOT_ALLOCATE_MEMMORY;
        }

        int ret = tmp->read(fp);
        if (ret < 0)
        {
            return delete tmp, ret;
        }
        if(ret > 0)
        {
            return delete tmp, ret;
        }

        Current -> Next = tmp;
        tmp -> Previous = Current;
        Current = tmp;
        Tail = Current;
        Tail -> Next = nullptr;
        tmp = nullptr;
    }
    return 0;
}

void List:: print(FILE* out)
{
    Current = Head;

    for (int i = 0; Current && i < MAX_PRINT_LIST; i ++)
    {
        if(Current != nullptr)
        {
            Current->print(out);
        }
        Current = Current -> Next;
    }
    Current = Head;
}

void List::delete_head()
{
    if(Head == nullptr)
    {
        return;
    }

    ListNode *tmp = Head -> Next;
    if(tmp != nullptr)
    {
        tmp -> Previous = nullptr;
        Head -> destroy();
        Head = tmp; 
    }
    else
    {
        Head -> destroy();
        Head = nullptr;
        Tail = nullptr;
    }
}

void List::addHead(ListNode *a)
{
    a->Previous = nullptr;
    a->Next = nullptr;
    Head = Tail = a;
}

void List::addBeforeHead(ListNode* a)
{
    if(Head == nullptr)
    {
	addHead(a);
        return;
    }
    else
    {
        Head -> Previous = a;
        a -> Next = Head;
        Head = a;
    }
}

void List::addAfterHead(ListNode* a)
{
    if (Head == nullptr)
    {
	addHead(a);
        return;
    }

    ListNode *tmp = Head -> Next;
    if(tmp != nullptr)
    {
        tmp -> Previous = a;
        a -> Previous = Head;
        Head -> Next = a;
        a -> Next = tmp;
    }
    else
    {
        Head -> Next = a;
        a -> Previous = Head;
        Tail = a;
    }
}

void List::addAfterTail(ListNode* a)
{
    if (Tail == nullptr)
    {
        return ;
    }
    Tail -> Next = a;
    a -> Previous = Tail;
    a -> Next = nullptr;
    Tail = a;
}


ListNode* List::moveFromList(ListNode* a)
{
    if(Head == nullptr || a == nullptr)
    {
        return nullptr;
    }
    ListNode* prevTmp = a -> Previous;
    ListNode* nextTmp = a -> Next;

    if (prevTmp != nullptr && nextTmp != nullptr)
    {
        nextTmp -> Previous = prevTmp;
        prevTmp -> Next = nextTmp;
        a -> Next = nullptr;
        a -> Previous = nullptr;
        return a;
    }
    else if(prevTmp == nullptr && nextTmp == nullptr)
    {
        Head = nullptr;
        Tail = nullptr;
        return a;
    }
    else if(prevTmp == nullptr && nextTmp != nullptr)
    {
        nextTmp -> Previous = nullptr;
        a -> Next = nullptr;
        Head = nextTmp;
        return a;
    }
    else if(prevTmp != nullptr && nextTmp == nullptr)
    {
        prevTmp -> Next = nullptr;
        a -> Previous = nullptr;
        Tail = prevTmp;
        return a;
    }
    return nullptr;
}

void List::delete_current()
{
    if (Head == nullptr || Current == nullptr)
    {
        return;
    }
    moveFromList(Current);
    Current -> destroy();
}

void List::addL(ListNode *dest, ListNode *src)
{
    if (dest == nullptr || src == nullptr)
    {
        return;
    }
    if(dest == Head)
    {
        addBeforeHead(src);
        return;
    }
    else
    {
        src -> Next = dest;
        dest -> Previous -> Next = src;
        src -> Previous = dest -> Previous;
        dest -> Previous = src;
        return;

    }   
}

void List::addR(ListNode *dest, ListNode *src)
{
    if (dest == nullptr || src == nullptr)
    {
        return;
    }
    if(dest -> Previous == nullptr)
    {
        addAfterHead(src);
        return;
    }
    else if(dest -> Next == nullptr)
    {
        addAfterTail(src);
        return;
    }
    else
    {
        src -> Next = dest -> Next;
        dest -> Next = src;
        src -> Next -> Previous = src;
        src -> Previous = dest;
        return;
    }
}




ListNode* List::func(const char *s)
{
    if(Head == nullptr)
    {
        return nullptr;
    }
    ListNode* tmp = nullptr;
    ListNode* del = nullptr;
    for (Current = Head; Current!= nullptr && Current != Tail; Current = Current->Next)
    {

        /*if(Current->comp(s))
        {
            printf("++++++++\n");
            Current->print();
            printf("++++++++\n");

            if (Current->Next != nullptr && Current->Next->Next != nullptr && Current->Next->Next->Next != nullptr)
            {
                    printf("--------------\n");
                    Current->Next->Next->Next->print();
                    printf("--------------\n");
                if(Current->Next->Next->Next->comp(s))
                {
                    Current = Current->Next->Next;
                    del = moveFromList(Current->Previous);
                    delete del;
                    del = nullptr;

                    Current = Current->Next->Next->Next;
                    del = moveFromList(Current->Previous);
                    delete del;
                    del = nullptr;

                    Current = Current -> Next;
                }
            }
        }*/


        if(Current->Next != nullptr)
        {
            tmp = Current->Next;
        }
        else if (Current->Previous != nullptr)
        {
            tmp = Current->Previous;
        }
        else
        {
            tmp = nullptr;
        }

        if((Current->Next != nullptr && Current->Next->comp(s))
            ||(Current->Previous != nullptr && Current->Previous->comp(s)))
        {

            del = moveFromList(Current);
            delete del;
            Current = tmp;
            tmp = nullptr;
            del = nullptr;

            if(Current != nullptr && Current->Next != nullptr && Current->Next->comp(s))
            {
                tmp = Current->Next;
                del = moveFromList(Current);
                delete del;
                del = nullptr;
                Current = tmp;
            }
        }
    }
    return Head;
}

/*
ListNode* List::func(const char *s)
{
    if(Head == nullptr)
    {
        return nullptr;
    }
    ListNode* tmp = nullptr;
    ListNode* del = nullptr;
    //bool fl1 = false;
    //bool fl2 = false;
    for (Current = Head; Current && Current != Tail; Current = Current->Next)
    {
        //fl1 = false;
        //fl2 = false;
        if(Current->Next != nullptr)
        {
            tmp = Current->Next;
        }
        else if (Current->Previous != nullptr)
        {
            tmp = Current->Previous;
        }
        else
        {
            tmp = nullptr;
        }


        printf("HUI!!!!!!!!!!!\n");
        Current->print();

        if((Current->Next != nullptr && Current->Next->comp(s))
            ||(Current->Previous != nullptr && Current->Previous->comp(s)))
        {
            //fl1 = true;
            del = moveFromList(Current);
            delete del;
            Current = tmp;
            tmp = nullptr;
            del = nullptr;
        }

        if ((Current->Next != nullptr && Current->Next->comp(s))
             ||(Current->Previous != nullptr && Current->Previous->comp(s)))
        {
            fl2 = true;
        }

        if (! (fl1 && fl2))
        {
            Current = Current->Next;
        }
        

    }
    return Head;
}

*/