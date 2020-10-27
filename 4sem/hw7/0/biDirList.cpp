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
    else if(prevTmp == nullptr && prevTmp == nullptr)
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
        Length ++;
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
        Length ++;
        addAfterHead(src);
        return;
    }
    else if(dest -> Next == nullptr)
    {
        Length ++;
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


void List::minFinSort(bool (*comp)(ListNode*, ListNode*))
{
    ListNode *tmp = nullptr, *min = Head;
    Current = Head;
    int len = Length;
    List b;
    for (int j = 0; j < Length ; ++j)
    {
        if(!comp(Current, min))
        {
            min = Current;
        }
        Current = Current -> Next;
    }
    tmp = moveFromList(min);
    b.Head = tmp;
    b.Tail = tmp;


    for (int i = 0; i < len - 1; ++i)
    {
        Current = Head;
        for (int j = 0; j < Length ; ++j)
        {
            if(!comp(Current, min))
            {
                min = Current;
            }
            Current = Current -> Next;
        }
        tmp = moveFromList(min);
        b.addR(b.Tail, tmp);
        b.print();
        printf("--\n");
    }
    Head = b.Head;
    Tail = b.Tail;
    Length = b.Length;
    tmp = min = nullptr;
    b.Head = nullptr;
    b.delete_list();
}

void List::callMergeSortRecur(bool (*comp)(ListNode*, ListNode*))
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
            bool fl= true; 
            if (begin1 == Head)
            {
                fl = false; 
            }
            int mergeCounter = counter; 
            end1 = begin1; 
            while (--counter && end1->Next)
            {
                end1 = end1->Next; 
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
                prevEnd -> print();
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
        //swap(begin1, begin2); 
        //swap(end1, end2); 
        begin1 -> swap(*begin2);
        end1 -> swap(*end2);
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