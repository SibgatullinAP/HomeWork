#include "list.h"

List::~List()
{
    deleteList();
    Head = Current = Tail = nullptr;
}

bool List::insert(ListNode *tmp)
{
    if(tmp == nullptr)
    {
	return false;
    }
    tmp->Next = Head;
    tmp->Previous = nullptr;
    if(Head != nullptr)
    {
	Head->Previous = tmp;
    }
    Head = tmp;

    return true;
}


ListNode * List::search(Command & command)
{
    ListNode *current = nullptr;
    ListNode *begin = nullptr;
    ListNode *end = nullptr;

    for(current = Head; current; current = current->Next)
    {
	if(command.check(current))
	{
	    break;
	}
    }
    if(current == nullptr)
    {
	return nullptr;
    }

    begin = end = current;
    for(current = current->Next; current; current = current->Next)
    {
	if(command.check(current))
	{
	    end = end->NextSelect = current;
	}
    }

    end->NextSelect = nullptr;

    return begin;
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

ListNode * List::moveFromList(ListNode  *tmp)
{
    if(tmp == nullptr)
    {
	return nullptr;
    }
    if(tmp == Head)
    {
	Head = Head->Next;
	if(Head != nullptr)
	{
	    Head->Previous = nullptr;
	}
	return tmp;
    }
    else
    {
	tmp->Previous->Next = tmp->Next;
	if(tmp->Next != nullptr)
	{
	    tmp->Next->Previous = tmp->Previous;
	}
	return tmp;
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
