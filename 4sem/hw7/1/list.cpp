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
        Length = 0;
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
            Length++;
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

void List::addHead(ListNode* src)
{
    if ( Head != nullptr || src == nullptr)
    {
        return;
    }
    Head = src;
    Head -> Next = nullptr;
    Current = Head;
    Length++;

}

void List::addBeforeHead(ListNode* a)
{
    if(!a) return;
    if(Head == nullptr)
    {
        Head = a;
        Head -> Next = nullptr;
        Current = Head;
        Length ++;
        return;
    }
    else
    {
        a -> Next = Head;
        Head = a;
        Current = Head;
        Length ++;
        return;
    }
}

void List::addR(ListNode *src)
{
    if ( (Current && Current -> Next) || !src) return;
    if(Head == nullptr)
    {
        addHead(src);
        return;
    }

    if (Current == nullptr)
    {
        Current = Head;
        while(Current -> Next)
        {
            Current = Current -> Next;
        }
    }

    Current -> Next = src;
    Current -> Next -> Next = nullptr;
    Current = Current -> Next;
    Length ++;
}

ListNode* List::moveFromList(ListNode* src)
{
    if(src == Head)
    {
        if (Head -> Next != nullptr)
        {
            Head = Head -> Next;
            src -> Next = nullptr;
            Length--;
            return src;
        }
        else
        {
            Head = nullptr;
            Length--;
            return src;
        }
    }
    if (Current -> Next -> Next != nullptr)
    {
        ListNode* tmp = Current -> Next;
        Current -> Next = Current -> Next -> Next;
        tmp -> Next = nullptr;
        Length--;
        return tmp;
    }
    else
    {
        Current -> Next = nullptr;
        Length --;
        return src;
    }

    return src;
}


void List::bubbleSort(bool (*comp)(ListNode*, ListNode*))
{
    ListNode *a = Head, *prev, *tmp;
    for (int i = 0; i < Length; ++i)
    {
        prev = a;
        tmp = nullptr;
        for (int j = 0; j < Length - i - 1; ++j)
        {
            if(comp(prev, prev -> Next))
            {
                if (tmp == nullptr)
                {
                    a = prev -> Next;
                    prev -> Next = prev -> Next -> Next;
                    a -> Next = prev;
                }
                else
                {
                    tmp -> Next = prev -> Next;
                    prev -> Next = prev -> Next -> Next;
                    tmp -> Next -> Next = prev;
                }
            }
            else
            {
                prev = prev -> Next;
            }
            if (tmp == nullptr)
            {
                tmp = a;
            }
            else
            {
                tmp = tmp -> Next;
            }
        }
    }

    Head = a;
    a = nullptr;
}

void List::maxFinSort(bool (*comp)(ListNode*, ListNode*))
{
    ListNode *element = nullptr, *cur_max = Head;
    int i = 0, j = 0;
    for (i = 0; i < Length; i++)
    {
        cur_max = Head;
        for (element = Head, j = 0; j < Length - i; j++)
        {
            if(comp(element, cur_max))
            {
                cur_max = element;
            }
            if (j < Length - i - 1)
            {
                element = element->Next;
            }
        }
        cur_max->swap (*element);
    }
    return;
}

void List::minFinSort(bool (*comp)(ListNode*, ListNode*))
{
    ListNode *element = nullptr, *curr = nullptr, *cur_min = Head;
    for (curr = Head; curr; curr = curr->Next)
    {
        cur_min = curr;
        for (element = curr->Next; element; element = element->Next)
        {
            if(comp(cur_min, element))
            {
                cur_min = element;
            }
        }
        cur_min->swap (*curr);
    }
    return;
}

void List::linInsSort(bool (*comp)(ListNode*, ListNode*))
{  
    List sorted;
    ListNode* curr = Head, *next;

    while (curr != nullptr)
    {
        next = curr -> Next;
        sorted.linIns(curr,comp);
        curr = next;
    }

    Head = sorted.Head;
    Length = sorted.Length;
    sorted.Head = nullptr;

} 

void List::linIns(ListNode* newNode, bool (*comp)(ListNode*, ListNode*)) 
{ 
    ListNode* curr; 
    if (Head == nullptr || !comp(newNode, Head))
    { 
        newNode -> Next = Head; 
        Head = newNode; 
    } 
    else
    { 
        curr = Head; 
        while (curr -> Next != nullptr && comp(newNode, curr -> Next))
        { 
            curr = curr -> Next; 
        } 
        newNode -> Next = curr -> Next; 
        curr -> Next = newNode; 
    } 
} 


void List::mergeSort (bool (*comp)(ListNode*, ListNode*))
{
    ListNode *first, *second, *last, *new_head, *prev;
    int step = 1;

    if (Head == nullptr)
    {
        return;
    }

    first = Head;

    if (first->Next == nullptr)
    {
        return;
    }

    while(true)
    {
        prev = nullptr;
        first = Head;
        second = getCurNext(first, step);
        if (second == nullptr)
        {
            break;
        }

        while (first)
        {
            second = getCurNext(first, step);
            last = getCurNext(second, step);
            if (second == nullptr)
            {
                break;    
            }
            new_head = merge (first, second, last, comp);
            if (prev == nullptr)
            {
                Head = new_head;
            }
            else
            {
                prev->Next = new_head;
            }
            for (prev = new_head; prev->Next != last; prev = prev->Next);
            first = last;
        }
      step *= 2;
    }
}


ListNode *List::merge(ListNode *first, ListNode *second, ListNode *last, bool (*comp)(ListNode*, ListNode*))
{
    ListNode *new_curr, *curr_first = first, *curr_second = second, *next, *new_head;

    if(comp(curr_second, curr_first))
    {
        new_curr = new_head = first;
        curr_first = curr_first->Next;
    }
    else
    {
        new_curr = new_head = second;
        curr_second = curr_second->Next;
    }

    while (curr_first != second && curr_second != last)
    {
        if(comp(curr_second, curr_first))
        {
            next = curr_first->Next;
            new_curr->Next = curr_first;
            new_curr = curr_first;
            curr_first = next;
        }
        else
        {
            next = curr_second->Next;
            new_curr->Next = curr_second;
            new_curr = curr_second;
            curr_second = next;
        }
    }
    if (curr_first != second)
    {
        new_curr->Next = curr_first;
        for (; curr_first->Next != second; curr_first = curr_first->Next);
        curr_first->Next = last;
    }
    else if (curr_second != last)
    {
        new_curr->Next = curr_second;
    }
    return new_head;
}


ListNode * List::getCurNext (ListNode *node, int step)
{
    ListNode *current = node;
    int current_step;
    for (current = node, current_step = 0; current_step < step && current; current = current->Next, current_step++);
    if (current_step < step)
    {
        return nullptr; 
    }
    return current;
}

void List::callQuickSort(bool (*comp)(ListNode*, ListNode*))
{
    quickSort(Head, Head,nullptr, nullptr, comp);
}

void List::quickSort (ListNode* head,ListNode *first, ListNode *last, ListNode *prev_first, bool (*comp)(ListNode*, ListNode*))
{
    ListNode *curr, *first_less, *first_more, *less, *more, *new_prev, *new_prev_first, *curr_prev;

    if (head == nullptr)
    {
        return;
    }
    if (first == nullptr)
    {
        return;
    }
    if (first->Next == last)
    {
        return;
    }

    while (first->Next != last)
    {
        first_less = less = nullptr;
        new_prev = prev_first;
        first_more = more = first;
        int length_less = 0;
        int length_more = 1;
        for (curr_prev = first, curr = first->Next; curr != last; curr_prev = curr, curr = curr->Next)
        {
            //if (*curr < *first)
            if(comp(first,curr))
            {
                if (less == nullptr)
                {
                    new_prev_first = curr_prev;
                    first_less = less = curr;
                }
                else
                {
                    less->Next = curr;
                    less = curr;
                }
                length_less++;
            }
            else
            {
                more->Next = curr;
                more = curr;
                length_more++;
            }
        }
        if (first_less != nullptr)
        {
            more->Next = last;
            less->Next = first_more;
            new_prev = less;
            if (first == Head)
            {
                Head = first_less;
                new_prev_first = nullptr;
            }
            else
            {
                prev_first->Next = first_less;
                new_prev_first = prev_first;
            }
        }
        else
        {
            new_prev_first = new_prev;
            first_less = first_more;
            new_prev = first_more;
            first_more = first_more->Next;
        }
        if (length_less < length_more)
        {
            quickSort (head, first_less, first_more, new_prev_first, comp);
            first = first_more;
            prev_first = new_prev;
        }
        else
        {
            if (first_more != last && first_more->Next != last)
            {
                quickSort(head, first_more, last, new_prev, comp);
            }
            last = first_more;
            first = first_less;
            prev_first = new_prev_first;
        }
    }
  return;
}