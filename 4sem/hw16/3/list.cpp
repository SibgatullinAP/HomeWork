#include "list.h"

List::~List()
{
    deleteList();
    Head = Current = Tail = nullptr;
}

bool List::insert(ListNode *tmp)
{
    if(Head == nullptr)
    {
	addHead(tmp);
	Current = Head;
    }
    else
    {
	addRight(Current,tmp);
	Current = Current->Next;
    }
    Current = Tail;
    return true;
}

bool List::selectingRequest(Command &current, FILE* outFile = stdout)
{
    ListNode *i = nullptr;
    for(i = Head; i; i = i->Next)
    {
	if(i->check(current))
	{
	    i->print(outFile);
	}
    }
    return true;
}

bool List::deletingRequest(Command &condition)
{
    ListNode *tmp = nullptr, *i = nullptr;
    i = Head;
    while (i)
    {
	if(i->check(condition))
	{
	    tmp = i->Next;
	    if(i == Head)
	    {
		Head = Head->Next;
		if(Head != nullptr)
		{
		    Head->Previous = nullptr;
		}
		delete i;
	    }
	    else
	    {
		i->Previous->Next = i->Next;
		if(i->Next != nullptr)
		{
		    i->Next->Previous = i->Previous;
		}
		delete i;
	    }
	    i = tmp;
	}
	else
	{
	    i = i->Next;
	}
    }
    return true;
}

void List::deleteList()
{
        while(Head)
	{
	    Current = Head;
	    Head = Head -> Next;
	    delete Current;
	}
	delete Head;
}

int List::print(FILE* outFile)
{
    ListNode *tmp = Head;

    for (int i = 0; tmp; i ++)
    {
	if(tmp != nullptr)
	{
	    tmp->print(outFile);
	}
	tmp = tmp -> Next;
    }
    tmp = nullptr;
    printf("\n");
    return 0;
}

void List::deleteHead()
{
    if(Head == nullptr)
    {
	return;
    }

    ListNode  *tmp = Head -> Next;
    if(tmp != nullptr)
    {
	tmp -> Previous = nullptr;
	Head -> ~ListNode();
	Head = tmp;
    }
    else
    {
	Head -> ~ListNode();
	Head = nullptr;
	Tail = nullptr;
    }
}

void List::deleteCurrent()
{
    if (Head == nullptr || Current == nullptr)
    {
	return;
    }
    moveFromList(Current);
    Current -> ~ListNode();
}

ListNode * List::moveFromList(ListNode  *a)
{
    if(Head == nullptr || a == nullptr)
    {
	return nullptr;
    }
    ListNode * prevTmp = a -> Previous;
    ListNode * nextTmp = a -> Next;

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

void List::addBeforeHead(ListNode  *a)
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

void List::addAfterHead(ListNode  *a)
{
    if (Head == nullptr)
    {
	addHead(a);
	return;
    }

    ListNode  *tmp = Head -> Next;
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

void List::addHead(ListNode * a)
{
    a->Previous = nullptr;
    a->Next = nullptr;
    Head = Current = Tail = a;
}

ListNode * List::getHead() const
{
    return Head;
}

void List::addAfterTail(ListNode  *a)
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

void List::addLeft(ListNode  *dest, ListNode  *src)
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

void List::addRight(ListNode  *dest, ListNode  *src)
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
