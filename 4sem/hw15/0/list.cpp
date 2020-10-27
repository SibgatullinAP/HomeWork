#include "list.h"


List<T>::~List()
{
    deleteList();
    Head = Current = Tail = nullptr;
}

bool List<T>::insert(const char* string, int phone, int group)
{
    ListNode<T> tmp;
    if(!(tmp.setName(string) && tmp.setPhone(phone) && tmp.setGroup(group)))
    {
	return false;
    }

    Current -> Next = tmp;
    tmp -> Previous = Current;
    Current = tmp;
    Tail = Current;
    Tail -> Next = nullptr;
    tmp = nullptr;

    return true;
}
// дописать возвращаемые значения

void List<T>::deleteList()
{
        while(Head)
	{
	    Current = Head;
	    Head = Head -> Next;
	    delete Current;
	}
	delete Head;
}

int List<T>::print(const char* outFileName = nullptr)
{
    if(outFilenName == nullptr)
    {
	Current = Head;
	printf("LIST:\n");

	for (int i = 0; Current && i < MAX_PRINT_LIST; i ++)
	{
	    if(Current != nullptr)
	    {
		Current->print();
	    }
	    Current = Current -> Next;
	}
	Current = Head;
	printf("\n");
	return 0;
    }
    else
    {
	FILE* outFile = nullptr;
	if((outFile = fopen(outFileName, "w")) == nullptr)
	{
	    return ERROR_CANNOT_OPEN_OUTPUT_FILE;
	}

	Current = Head;
	fprintf(outFile,"LIST:\n");

	for (int i = 0; Current && i < MAX_PRINT_LIST; i ++)
	{
	    if(Current != nullptr)
	    {
		Current->print(outFile);
	    }
	    Current = Current -> Next;
	}
	Current = Head;
	fprintf(outFile,"\n");
	return 0;
    }
}

int List<T>::read (FILE *inFile)
{
    deleteList ();

    char buff[BUFF_LEN];
    char name[BUFF_LEN];
    int phone = 0, group = 0;

    ListNode<T> *tmp;
    tmp = new ListNode<T>;
    if(tmp == nullptr)
    {
	return ERROR_CANNOT_ALLOCATE_MEMMORY_TO_READ_NAME;
    }

    if(sscanf(buff,"%s %d %d", name, phone, group) != 3)
    {
	return ERROR_CANNOT_READ_INPUT_FILE;
    }

    Head = Current = Tail = tmp;
    if(!(tmp.setName(string) && tmp.setPhone(phone) && tmp.setGroup(group)))
    {
	return ERROR_CANNOT_ALLOCATE_MEMMORY_TO_READ_NAME;
    }


    while (fgets(buff, LEN, inFile))
    {

	if(sscanf(buff,"%s %d %d", name, phone, group) != 3)
	{
	    return ERROR_CANNOT_READ_INPUT_FILE;
	}
	if(!insert(name, phone, group)
	{
	    return ERROR_CANNOT_ALLOCATE_MEMMORY_TO_READ_NAME;
	}

    }
    return 0;
}

void List<T>::deleteHead()
{
    if(Head == nullptr)
    {
	return;
    }

    ListNode <T> *tmp = Head -> Next;
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

void List<T>::deleteCurrent()
{
    if (Head == nullptr || Current == nullptr)
    {
	return;
    }
    moveFromList(Current);
    Current -> ~ListNode;
}

ListNode <T>* List<T>::moveFromList(ListNode <T> *a)
{
    if(Head == nullptr || a == nullptr)
    {
	return nullptr;
    }
    ListNode <T>* prevTmp = a -> Previous;
    ListNode <T>* nextTmp = a -> Next;

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

void List<T>::addBeforeHead(ListNode <T> *a)
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

void List<T>::addAfterHead(ListNode <T> *a)
{
    if (Head == nullptr)
    {
	addHead(a);
	return;
    }

    ListNode <T> *tmp = Head -> Next;
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

void List<T>::addHead(ListNode <T>* a)
{
    a->Previous = nullptr;
    a->Next = nullptr;
    Head = Tail = a;
}

ListNode <T> *List<T>::getHead() const
{
    return Head;
}

void List<T>::addAfterTail(ListNode <T> *a)
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

void List<T>::addLeft(ListNode <T> *dest, ListNode <T> *src)
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

void List<T>::addRight(ListNode <T> *dest, ListNode <T> *src)
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
