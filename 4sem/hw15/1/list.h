#ifndef LIST_H
#define LIST_H

#include "listNode.h"

template <class T>
class List
{
	private:
            ListNode <T> *Head = nullptr;
	    ListNode <T> *Current = nullptr;
	    ListNode <T> *Tail = nullptr;

        public:
	    List ()  = default;
	    /*~List ();

	    int read (FILE *fp = stdin);
	    bool insert(char *name, int phone, int group);
	    int print(const char* outFileName = nullptr);

	    void deleteList();
	    void deleteHead();
	    void deleteCurrent();

	    ListNode <T>* moveFromList(ListNode <T> *a);

	    void addHead(ListNode <T>* a);
	    void addBeforeHead(ListNode <T> *a);
	    void addAfterHead(ListNode <T> *a);

	    void addAfterTail(ListNode <T> *a);

	    void addLeft(ListNode <T> *dest, ListNode <T> *src);
	    void addRight(ListNode <T> *dest, ListNode <T> *src);*/

	    ~List()
	    {
		deleteList();
		Head = Current = Tail = nullptr;
	    }

	    //без проверки повторений
	    bool insertingRequest(char* string, int phone, int group)
	    {
		ListNode<T> *tmp;
		tmp = new ListNode<T>;
		if(!(tmp->setName(string) && tmp->setPhone(phone) && tmp->setGroup(group)))
		{
		    return false;
		}

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

	    /*bool insertingRequest(char* string, int phone, int group)
	    {
		ListNode<T> *tmp;
		tmp = new ListNode<T>;
		if(!(tmp->setName(string) && tmp->setPhone(phone) && tmp->setGroup(group)))
		{
		    return false;
		}
		if(Head == nullptr)
		{
		    Head = tmp;
		    tmp->Previous = tmp->Next = nullptr;
		    return true;
		}

		ListNode<T> *i;
		for(i = Head; i->Next; i = i->Next)
		{
		    if(*i == *tmp)
		    {
			return false;
		    }
		}

		if(*i == *tmp)
		{
		    return false;
		}
		i->Next = tmp;
		tmp->Previous = i;
		tmp->Next = nullptr;
		return true;
	    }*/

	    bool selectingRequest(Command &current, FILE* outFile = stdout)
	    {
		ListNode<T> *i = nullptr;
		for(i = searching(current); i; i = i->RequestNext)
		{
		    i->print(outFile);
		}
		return true;
	    }

	    bool deletingRequest(Command &condition)
	    {
		ListNode<T> *tmp, *i;
		for(i = searching(condition); i;)
		{
		    tmp = i->RequestNext;
		    if (i == nullptr)
		    {
			return false;
		    }
		    if (i == Head)
		    {
			deleteHead();
			return true;
		    }
		    /*if (i->Next != nullptr)
		    {
			i->Next->Previous = i->Previous;
		    }
		    i->Previous->Next = i->Next;
		    delete i;*/
		    deleteCurrent(i);

		    i = tmp;
		}
		return true;
	    }

	    ListNode<T> *searching(Command &condition)
	    {
		ListNode<T> *newHead = nullptr;
		ListNode<T> *i = nullptr;

		for(i = Head; i; i = i->Next)
		{
		    if(i->check(condition))
		    {
			newHead = i;
			break;
		    }
		}

		if(newHead == nullptr)
		{
		    return nullptr;
		}

		ListNode<T> *tmp = newHead;

		for(i = newHead->Next; i; i = i->Next)
		{
		    if(i->check(condition))
		    {
			tmp->RequestNext = i;
			tmp = i;
		    }
		}
		return newHead;
	    }

	    void deleteList()
	    {
		    while(Head)
		    {
			Current = Head;
			Head = Head -> Next;
			delete Current;
		    }
		    delete Head;
	    }

	    int deleteCurrent(ListNode<T> *curr){
		    if(!curr) return -1;

		    if(curr == Head){
			    Head = Head->Next;
			    if(Head) Head->Previous = nullptr;
			    delete curr;
		    }
		    else{
			    curr->Previous->Next = curr->Next;
			    if(curr->Next) curr->Next->Previous = curr->Previous;
			    delete curr;
		    }

		    return 0;
	    }
	    int print(const char* outFileName = nullptr)
	    {
		if(outFileName == nullptr)
		{
		    ListNode<T> *tmp = Head;

		    for (int i = 0; tmp && i < MAX_PRINT_LIST; i ++)
		    {
			if(tmp != nullptr)
			{
			    tmp->print();
			}
			tmp = tmp -> Next;
		    }
		    tmp = nullptr;
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

	    int read (FILE *inFile)
	    {
		deleteList ();

		char buff[BUFF_LEN];
		char name[BUFF_LEN];
		int phone = 0, group = 0;

		while (fgets(buff, BUFF_LEN, inFile))
		{

		    if(sscanf(buff,"%s %d %d", name, &phone, &group) != 3)
		    {
			return ERROR_CANNOT_READ_INPUT_FILE;
		    }
		    if(!insertingRequest(name, phone, group))
		    {
			return ERROR_CANNOT_ALLOCATE_MEMMORY_TO_READ_NAME;
		    }

		}
		return 0;
	    }

	    void deleteHead()
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

	    void deleteCurrent()
	    {
		if (Head == nullptr || Current == nullptr)
		{
		    return;
		}
		moveFromList(Current);
		Current -> ~ListNode;
	    }

	    ListNode <T>* moveFromList(ListNode <T> *a)
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

	    void addBeforeHead(ListNode <T> *a)
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

	    void addAfterHead(ListNode <T> *a)
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

	    void addHead(ListNode <T>* a)
	    {
		a->Previous = nullptr;
		a->Next = nullptr;
		Head = Current = Tail = a;
	    }

	    ListNode <T> *getHead() const
	    {
		return Head;
	    }

	    void addAfterTail(ListNode <T> *a)
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

	    void addLeft(ListNode <T> *dest, ListNode <T> *src)
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

	    void addRight(ListNode <T> *dest, ListNode <T> *src)
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

};

#endif
