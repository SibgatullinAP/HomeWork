#include "biDirList.h"

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
        Length = 0;
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

	Head = Current = Tail = tmp; 

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
                Tail = Current;
                return delete tmp, NOT_ERROR_END_OF_INPUT;
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

    for (int i = 0; Current && i < MAX_PRINT; i ++)
    {
        Current -> print(out);
        Current = Current -> Next;
    }
    printf("\n");
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
        Length ++;
    }
    else
    {
        Head -> destroy();
        Head = nullptr;
        Tail = nullptr;
        Length ++;
    }
}

void List::addBeforeHead(ListNode* a)
{
    if(Head == nullptr)
    {
        Tail = a;
        Head = a;
        Length ++;
        return;
    }
    else
    {
        Head -> Previous = a;
        a -> Next = Head;
        Head = a;
        Length ++;
    }
}

void List::addAfterHead(ListNode* a)
{
    if (Head == nullptr)
    {
        Head = a;
        Tail = a;
        Length ++;
        return;
    }

    ListNode *tmp = Head -> Next;
    if(tmp != nullptr)
    {
        tmp -> Previous = a;
        a -> Previous = Head;
        Head -> Next = a;
        a -> Next = tmp;
        Length ++;
    }
    else
    {
        Head -> Next = a;
        a -> Previous = Head;
        Tail = a;
        Length ++;
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
    Length ++;
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
        Length --;
        return a;
    }
    else if(prevTmp == nullptr && nextTmp == nullptr)
    {
        Head = nullptr;
        Tail = nullptr;
        Length --;
        return a;
    }
    else if(prevTmp == nullptr && nextTmp != nullptr)
    {
        nextTmp -> Previous = nullptr;
        a -> Next = nullptr;
        Head = nextTmp;
        Length --;
        return a;
    }
    else if(prevTmp != nullptr && nextTmp == nullptr)
    {
        prevTmp -> Next = nullptr;
        a -> Previous = nullptr;
        Tail = prevTmp;
        Length --;
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
    Length --;
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
        Length ++;
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
        Length ++;
        src -> Next = dest -> Next;
        dest -> Next = src;
        src -> Next -> Previous = src;
        src -> Previous = dest;
        return;
    }
}

void List::swap(ListNode *left, ListNode *right)
{
    ListNode *tmp;

    tmp = left->Previous;
    if (tmp != nullptr)
    {
        tmp->Next = right;
    }

    right->Previous = tmp;
    left->Previous = right;
    left->Next = right->Next;
    right->Next = left;

    if(left->Next != nullptr)
    {
        left->Next->Previous = left;
    }

    if(left == Head)
    {
        Head = right;
        right -> Previous = nullptr;
    }
    if(right == Tail)
    {
        Tail = left;
        left -> Next = nullptr;
    }
}


void List::bubbleSort0(bool (*comp)(ListNode*, ListNode*))
{
    ListNode *i , *j;
    bool fl;

    for (i = Head; i != nullptr; i = i -> Next)
    {
        fl = true;
        for (j = Head; j != nullptr; j = j -> Next)
        {
            if(!comp(i,j))
            {
                i -> swap(*j);
                fl = false;
            }
        
        }
        if(fl)
        {
            break;
        }

    }
}

void List::bubbleSort(bool (*comp)(ListNode*, ListNode*))
{
    ListNode *j;
    int k, l;
    bool fl;

    for (k = 0; k < Length; k++)
    {
        fl = true;
        for (l = 0, j = Head; j->Next && l < Length - k - 1; l++)
        {
            if(comp(j,j -> Next))
            {
                this -> swap(j,j->Next);
                fl = false;
            } 
            else j = j -> Next;

        }
        if(fl)
        {
            break;
        }

    }
}



void List::maxFinSort(bool (*comp)(ListNode*, ListNode*))
{
    ListNode *tmp = nullptr, *min = Head;
    Current = Head;
    int len = Length;

    List b;
    tmp = moveFromList(maxFin(comp));
    b.Head = tmp;
    b.Tail = tmp;
    b.Length ++;

    for (int i = 1; i < len ; ++i)
    {
        tmp = (maxFin(comp));
        b.addBeforeHead(moveFromList(tmp));
    }
    Head = b.Head;
    Tail = b.Tail;
    Length = b.Length;
    tmp = min = nullptr;
    b.Head = nullptr;
}

ListNode* List::maxFin(bool (*comp)(ListNode*, ListNode*))
{
    ListNode* tmp = Head;
    if(tmp == nullptr)
    {
        return nullptr;
    }
    if(tmp -> Next == nullptr)
    {
        return tmp;
    }
    ListNode* max = Head;
    for (int i = 0; i < Length; i++)
    {
        if(comp(tmp, max))
        {
            max = tmp;
        }
        tmp = tmp -> Next;
    }
    tmp = nullptr;
    return max;
}


void List::minFinSort(bool (*comp)(ListNode*, ListNode*))
{
    ListNode *tmp = nullptr, *min = Head;
    Current = Head;
    int len = Length;

    List b;
    tmp = moveFromList(minFin(comp));
    b.Head = tmp;
    b.Tail = tmp;
    b.Length ++;

    for (int i = 1; i < len ; ++i)
    {
        tmp = (minFin(comp));
        b.addAfterTail(moveFromList(tmp));
    }
    Head = b.Head;
    Tail = b.Tail;
    Length = b.Length;
    tmp = min = nullptr;
    b.Head = nullptr;
}

ListNode* List::minFin(bool (*comp)(ListNode*, ListNode*))
{
    ListNode* tmp = Head;
    if(tmp == nullptr)
    {
        return nullptr;
    }
    if(tmp -> Next == nullptr)
    {
        return tmp;
    }
    ListNode* min = Head;
    for (int i = 0; i < Length; i++)
    {
        if(!comp(tmp, min))
        {
            min = tmp;
        }
        tmp = tmp -> Next;
    }
    tmp = nullptr;
    return min;
}


void List::linInsSort(bool (*comp)(ListNode *, ListNode *))
{
    List sorted;
    ListNode* curr = Head;

    while (curr != nullptr)
    {
        ListNode* next = curr -> Next;
        curr -> Previous = curr -> Next = nullptr;
        sorted.linIns(curr,comp);
        curr = next;
    }

    Head = sorted.Head;
    Tail = sorted.Tail;
    Length = sorted.Length;
    sorted.Head = nullptr;
}

void List::linIns(ListNode* newNode, bool (*comp)(ListNode*, ListNode*))
{
    ListNode* curr;

    if (Head == nullptr)
    {
        Head = newNode;
    }
    else if (!comp(newNode, Head))
    {
        newNode -> Next = Head;
        newNode -> Next -> Previous = newNode;
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
        if (curr -> Next != nullptr)
        {
            newNode -> Next -> Previous = newNode;
        }
        curr -> Next = newNode;
        newNode -> Previous = curr;
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
                new_head->Previous = prev;
            }
            //for (prev = new_head; prev->Next != last; prev = prev->Next);
            if (last != nullptr)
            {
                prev = last->Previous;
            }
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
            curr_first->Previous = new_curr;
            new_curr = curr_first;
            curr_first = next;
        }
        else
        {
            next = curr_second->Next;
            new_curr->Next = curr_second;
            curr_second->Previous = new_curr;
            new_curr = curr_second;
            curr_second = next;
        }
    }
    if (curr_first != second)
    {
        new_curr->Next = curr_first;
        curr_first->Previous = new_curr;
        for (; curr_first->Next != second; curr_first = curr_first->Next);
        curr_first->Next = last;
        if (last != nullptr)
        {
            last -> Previous = curr_first;
        }
    }
    else if (curr_second != last)
    {
        new_curr->Next = curr_second;
        curr_second -> Previous = new_curr;
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
    quickSort(Head, Head,nullptr, comp);
}

void List::quickSort (ListNode* head,ListNode *first, ListNode *last, bool (*comp)(ListNode*, ListNode*))
{
    ListNode *curr, *first_less, *first_more, *less, *more, *prev;

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
        first_more = more = first;
        int length_less = 0;
        int length_more = 1;
        if (first != Head)
        {
            prev = first->Previous;
        }
        for (curr = first->Next; curr != last; curr = curr->Next)
        {
            if(comp(first,curr))
            {
                if (less == nullptr)
                {
                    first_less = less = curr;
                }
                else
                {
                    less->Next = curr;
                    curr->Previous = less;
                    less = curr;
                }
                length_less++;
            }
            else
            {
                more->Next = curr;
                curr->Previous = more;
                more = curr;
                length_more++;
            }
        }
        if (first_less != nullptr)
        {
            more->Next = last;
            if (last != nullptr)
            {
                last->Previous = more;
            }
            else
            {
                Tail = more;
            }
            less->Next = first_more;
            first_more->Previous = less;
            if (first == Head)
            {
                Head = first_less;
            }
            else
            {
                prev->Next = first_less;
                first_less->Previous = prev;
            }
        }
        else
        {
            first_less = first_more;
            first_more = first_more->Next;
        }
        if (length_less < length_more)
        {
            quickSort (head, first_less, first_more, comp);
            first = first_more;
        }
        else
        {
            if (first_more != last && first_more->Next != last)
            {
                quickSort(head, first_more, last, comp);
            }
            last = first_more;
            first = first_less;
        }
    }
  return;
}


/* List::callMergeSortRecur(bool (*comp)(ListNode*, ListNode*))
{
    ListNode** tmp = &Head;
    mergeSort(tmp, comp);
}

void List::mergeSort(ListNode** source, bool (*comp)(ListNode*, ListNode*))
{
    ListNode* head = *source;
    ListNode *a = nullptr;
    ListNode *b = nullptr;

    if(head == nullptr || head -> Next == nullptr)
    {
        return;
    }

    partition(head, &a, &b);

    mergeSort(&a, comp);
    mergeSort(&b, comp);

    *source = mergeLists(a, b, comp);
}


ListNode* List::mergeLists(ListNode* a, ListNode* b,bool (*comp)(ListNode*, ListNode*))
{
    ListNode * done = nullptr;

    if(a == nullptr)
    {
        return b;
    }
    else if( b == nullptr)
    {
        return a;
    }

    if (!comp(a,b))
    {
        done = a;
        done -> Next = mergeLists(a -> Next, b, comp);
    }
    else
    {
        done = b;
        done -> Next = mergeLists(a, b -> Next, comp);
    }
    return done;
}

void List::partition(ListNode* head, ListNode **front, ListNode **back)
{
    ListNode *fast;
    ListNode *slow;

    if(head == nullptr || head -> Next == nullptr)
    {
        *front = head;
        *back = nullptr;
    }
    else
    {
        slow = head;
        fast = head -> Next;
        while(fast != nullptr)
        {
            fast = fast -> Next;
            if (fast != nullptr)
            {
                slow = slow -> Next;
                fast = fast -> Next;
            }
        }

        *front = head;
        *back = slow -> Next;
        slow -> Next = nullptr;
    }
}



void List::mergeSort1(bool (*comp)(ListNode*, ListNode*)) 
{ 
    ListNode* begin1 = nullptr, *end1 = nullptr; 
    ListNode* begin2 = nullptr, *end2 = nullptr; 
    ListNode* prevEnd = Head ; 

    if (Head == nullptr)
    {
        return; 
    }
    for (int counter = 1; counter < Length; counter *= 2)
    { 
        begin1 = Head; 
        while (begin1)
        { 
            printf("dnkasdnkas\n");
            bool fl= true; 
            if (begin1 == Head)
            {
                fl = false; 
            }
            int mergeCounter = counter; 
            end1 = begin1; 
            while (--counter && end1 -> Next)
            {
                end1 = end1 -> Next; 
                
            }
            begin2 = end1->Next; 
            if (begin2 == nullptr)
            {
                break;   
            }  
            mergeCounter = counter; 
            end2 = begin2; 
            while (--mergeCounter && end2->Next)
            {
                end2 = end2->Next; 
            }
            ListNode *tmp = end2->Next;  
            merge(begin1, end1, begin2, end2, comp); 
            if (fl)
            {
                Head = begin1; 
            }
            else
            {
                prevEnd->Next = begin1; 
            }
            prevEnd = end2; 
            begin1 = tmp; 
        } 
        prevEnd->Next = begin1; 
    } 
} 

void List::merge(ListNode* begin1, ListNode* end1, ListNode* begin2, ListNode* end2, bool (*comp)(ListNode*, ListNode*)) 
{ 
    ListNode* tmp = nullptr; 
    if(comp(begin1, begin2))
    {
        swapMerge(begin1, begin2);
        swapMerge(end1, end2);
        //begin1 -> swap(*begin2);
        //end1 -> swap(*end2);
    }
    ListNode* aBegin = begin1, *aEnd = end1; 
    ListNode* bBegin = begin2;
    ListNode* bEndNext = end2->Next; 

    while (aBegin != aEnd && bBegin != bEndNext) 
    { 
        if(comp(aBegin -> Next, bBegin))
        { 
            tmp = bBegin->Next; 
            bBegin->Next = aBegin->Next; 
            aBegin->Next = bBegin; 
            bBegin = tmp; 
        } 
        aBegin = aBegin->Next; 
    } 
    if (aBegin == aEnd)
    {
        aBegin->Next = bBegin; 
    }
    else
    {
        end2 = end1; 
    }
}

void List::swapMerge(ListNode *a, ListNode *b)
{
    if (a -> Previous == nullptr && b -> Previous == nullptr)
    {
        ListNode* tmp = a -> Next;
        a -> Next = b -> Next;
        b -> Next = tmp;
        if (a -> Next != nullptr && b -> Next !=nullptr)
        {
            a -> Next -> Previous = a;
            b -> Next -> Previous = b;
        }
        a -> Previous = nullptr;
        b -> Previous = nullptr;
    }
    if (a -> Next == nullptr && b -> Next == nullptr)
    {
        ListNode* tmp = a -> Previous;
        a -> Previous = b -> Previous;
        b -> Previous = tmp;
        if (a -> Previous != nullptr && b -> Previous !=nullptr)
        {
            a -> Previous -> Next = a;
            b -> Previous -> Next = b;
        }
        a -> Next = nullptr;
        b -> Next = nullptr;
    }
}

ListNode* List::partitionQuick(ListNode *l, ListNode *h, bool (*comp)(ListNode*, ListNode*))
{
    ListNode *x = h;
    ListNode *i = l -> Previous;

    for (ListNode *j = l; j != h; j = j -> Next)
    {
        if(!comp(j,x))
        {
            if(i == nullptr)
            {
                i = l;
            }
            else
            {
                i = i -> Next;
            }
            i -> swap(*j);
        }
    }
    if(i == nullptr)
    {
        i = l;
    }
    else
    {
        i = i -> Next;
    }
    i -> swap(*h);
    return i;
}

void List::quickSortRec(ListNode* l, ListNode *h, bool (*comp)(ListNode*, ListNode*))
{
    if (h != nullptr && l != h && l != h -> Next)
    {
        ListNode *p = partitionQuick(l, h, comp);
        quickSortRec(l, p -> Previous, comp);
        quickSortRec(p -> Next, h, comp);
    }
}

void List::quickSort(bool (*comp)(ListNode*, ListNode*))
{
    quickSortRec(Head, Tail, comp);
}
*/