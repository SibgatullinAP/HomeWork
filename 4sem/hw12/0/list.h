#ifndef LIST_H
#define LIST_H

#include "listNode.h"
#include "tree.h"

template <class T, template <class> class T1, template <class, template <class> class> class T2>
class List
{
	private:
	ListNode <T, T1, T2> *Head = nullptr;
	ListNode <T, T1, T2> *Current = nullptr;
	ListNode <T, T1, T2> *Tail = nullptr;

        enum MENU_PROPERTIES
        {
            MENU = 'm',
            EXIT = 'e',
            PRINT_LIST = 'p',
            PRINT_CURRENT = 'c',
	    PRINT_HEAD = 'o',
	    PRINT_TAIL = 'f',
            WORK_WITH_TREE = 'w',
            GO_HEAD = 'h',
            GO_LEFT = 'l',
            GO_RIGHT = 'r',
            DELETE_LEFT = 'b',
            DELETE_RIGHT = 'n',
            ADD_BEFORE_HEAD = 'y',
            DELETE_LIST = 'x',
            DELETE_CURRENT = 'd',
            ADD_LEFT = 't',
            ADD_RIGHT = 'z'
        };

	public:
        List ()  = default;
	~List ()
	{
	    delete_list();
	    Head = Current = Tail = nullptr;
	}

	//
	void delete_list ()
	{
	        while(Head)
		{
		    Current = Head;
		    Head = Head -> Next;
		    delete Current;
		}
		delete Head;
	}
	void print(FILE* out = stdout)
	{
	    Current = Head;
	    printf("LIST:\n");

	    for (int i = 0; Current && i < MAX_PRINT_LIST; i ++)
	    {
		printf("    TREE:\n");
		if(Current != nullptr)
		{
		    Current->print(Current->get_root(), 0, out);
		}
		Current = Current -> Next;
		printf("\n");
	    }
	    Current = Head;
	    printf("\n");
	}

	int read (FILE *fp, int size_list, int size_tree, int size_queue)
	{
	    delete_list ();

	    ListNode <T, T1, T2> *tmp;
	    tmp = new ListNode <T, T1, T2> ;
	    if (tmp == nullptr)
	    {
		return ERROR_CANNOT_ALLOCATE_MEMMORY;
	    }

	    int ret = tmp->read(fp, size_tree, size_queue);
	    if (ret < 0)
	    {
		return delete tmp, ret;
	    }

	    int i = 1;
	    Head = Current = Tail = tmp;
	    for (;;)
	    {
		i++;
		if(i > size_list)
		{
		    return 0;
		}

		tmp = new ListNode <T, T1, T2> ;
		if (tmp == nullptr)
		{
		    return ERROR_CANNOT_ALLOCATE_MEMMORY;
		}

		ret = tmp->read(fp, size_tree, size_queue);
		if (ret < 0)
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

	//
	void delete_head()
	{
	    if(Head == nullptr)
	    {
		return;
	    }

	    ListNode <T, T1, T2> *tmp = Head -> Next;
	    if(tmp != nullptr)
	    {
		tmp -> Previous = nullptr;
		Head -> delete_tree(Head->get_root());
		Head = tmp;
	    }
	    else
	    {
		Head -> delete_tree(Head->get_root());
		Head = nullptr;
		Tail = nullptr;
	    }
	}

	void delete_current()
	{
	    if (Head == nullptr || Current == nullptr)
	    {
		return;
	    }
	    moveFromList(Current);
	    Current -> delete_tree(Current->get_root());
	}

	ListNode <T, T1, T2>* moveFromList(ListNode <T, T1, T2> *a)
	{
	    if(Head == nullptr || a == nullptr)
	    {
		return nullptr;
	    }
	    ListNode <T, T1, T2>* prevTmp = a -> Previous;
	    ListNode <T, T1, T2>* nextTmp = a -> Next;

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

	//
	void addBeforeHead(ListNode <T, T1, T2> *a)
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

	void addAfterHead(ListNode <T, T1, T2> *a)
	{
	    if (Head == nullptr)
	    {
		addHead(a);
		return;
	    }

	    ListNode <T, T1, T2> *tmp = Head -> Next;
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

	void addAfterTail(ListNode <T, T1, T2> *a)
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

	//
	void addL(ListNode <T, T1, T2> *dest, ListNode <T, T1, T2> *src)
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

	void addR(ListNode <T, T1, T2> *dest, ListNode <T, T1, T2> *src)
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

	//
	void addHead(ListNode <T, T1, T2>* a)
	{
	    a->Previous = nullptr;
	    a->Next = nullptr;
	    Head = Tail = a;
	}

	ListNode <T, T1, T2> *get_head() const
	{
	    return Head;
	}

	//
	void menu()
	{
	    clear();
	    print_menu();

	    MENU_PROPERTIES key;
	    char buff[LEN];
	    Current = Head;

	    for(;;)
	    {
		printf("Enter your choise: ");
		if(!fgets(buff, LEN, stdin))
		{
		    return;
		}
		key = MENU_PROPERTIES(buff[0]);
		switch(key)
		{
		    case MENU:
			clear();
			print_menu();
			break;

		    case EXIT:
			return;

		    case PRINT_LIST:
			clear();
			ListNode <T, T1, T2>* curr;
			curr = Current;
			if(Head != nullptr) print();
			else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
			Current = curr;
			curr = nullptr;
			printf("\n");
			break;

		    case PRINT_CURRENT:
			clear();
			if(Current != nullptr) Current->print(Current->get_root(), 0, stdout);
			else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
			printf("\n");
			break;

		    case PRINT_HEAD:
			clear();
			if(Head != nullptr) Head->print(Head->get_root(), 0, stdout);
			else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
			printf("\n");
			break;

		    case PRINT_TAIL:
			clear();
			if(Tail != nullptr) Tail->print(Tail->get_root(), 0, stdout);
			else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
			printf("\n");
			break;

		    case WORK_WITH_TREE:
			clear();
			if(Current != nullptr) Current->menu();
			else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
			printf("\n");
			break;

		    case GO_LEFT:
			clear();
			if(Current != nullptr && Current->Previous != nullptr) Current = Current->Previous;
			else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
			printf("\n");
			break;

		    case GO_RIGHT:
			clear();
			if(Current != nullptr && Current->Next != nullptr) Current = Current->Next;
			else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
			printf("\n");
			break;

		    case GO_HEAD:
			clear();
			if(Head != nullptr) Current = Head;
			else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
			printf("\n");
			break;

		    case DELETE_LEFT:
			clear();
			ListNode <T, T1, T2>* currl;
			currl = Current;
			if(Current != nullptr && Current->Previous != nullptr)
			{
			    ListNode <T, T1, T2> *tmp1 = moveFromList(Current->Previous);
			    delete tmp1;
			    Current = currl;
			    currl = nullptr;
			}
			else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
			printf("\n");
			break;

		    case DELETE_RIGHT:
			clear();
			ListNode <T, T1, T2> *currr;
			currr = Current;
			if(Current != nullptr && Current->Next !=nullptr)
			{
			    ListNode <T, T1, T2> *tmp2 = moveFromList(Current->Next);
			    delete tmp2;
			    Current = currr;
			    currr = nullptr;
			}
			else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
			printf("\n");
			break;

		    case ADD_BEFORE_HEAD:
			clear();
			ListNode <T, T1, T2> *tmp3;
			tmp3 = new ListNode <T, T1, T2>;
			addBeforeHead(tmp3);
			Current = Head;
			printf("\n");
			break;

		    case DELETE_CURRENT:
			clear();
			ListNode <T, T1, T2> *currc;
			currc = Current;
			if(Current != nullptr)
			{
			    ListNode <T, T1, T2> *tmp4;
			    tmp4 = moveFromList(Current);
			    delete tmp4;

			    Current = currc;
			    currc = nullptr;
			    if(Current->Next != nullptr)
			    {
				Current = Current->Next;
			    }
			    else if (Current->Previous != nullptr)
			    {
				Current = Current->Previous;
			    }
			    else
			    {
				Current = Head;
			    }
			}
			else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
			printf("\n");
			break;

		    case DELETE_LIST:
			clear();
			if(Head != nullptr) delete_list();
			else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
			Current = Head = Tail = nullptr;
			printf("\n");
			break;

		    case ADD_LEFT:
			clear();
			if(Current != nullptr)
			{
			    ListNode <T, T1, T2> *tmp5;
			    tmp5 = new ListNode <T, T1, T2>;
			    addL(Current, tmp5);
			    Current = Current->Previous;
			}
			else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
			printf("\n");
			break;

		    case ADD_RIGHT:
			clear();
			if(Current != nullptr)
			{
			    ListNode <T, T1, T2> *tmp6 = new ListNode <T, T1, T2>;
			    addR(Current, tmp6);
			    Current = Current->Next;
			}
			else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
			printf("\n");
			break;

		    default:
			clear();
			printf("\nFor coming back to menu press - \x1b[1;33mm\x1b[0m!\n");
			break;

		}
	    }
	}

	void print_menu()
	{
	    printf(" -----------------------------------\n");
	    printf("|          ~Menu for List~           |\n");
	    printf("|           \x1b[1;33mm\x1b[0m - Show Menu            |\n");
	    printf("|           \x1b[1;33me\x1b[0m - Exit Menu            |\n");
	    printf("|          \x1b[1;33mp\x1b[0m - Print List            |\n");
	    printf("|          \x1b[1;33mo\x1b[0m - Print Head            |\n");
	    printf("|          \x1b[1;33mf\x1b[0m - Print Tail            |\n");
	    printf("|         \x1b[1;33mc\x1b[0m - Print Current          |\n");
	    printf("|        \x1b[1;33mw\x1b[0m - Work with Tree          |\n");
	    printf("|             \x1b[1;33mh\x1b[0m - Go head            |\n");
	    printf("|             \x1b[1;33ml\x1b[0m - Go back            |\n");
	    printf("|           \x1b[1;33mr\x1b[0m - Go forward           |\n");
	    printf("|         \x1b[1;33mb\x1b[0m - Delete previous        |\n");
	    printf("|          \x1b[1;33mn\x1b[0m - Delete next           |\n");
	    printf("|         \x1b[1;33my\x1b[0m - Add before head        |\n");
	    printf("|           \x1b[1;33mx\x1b[0m - Delete List          |\n");
	    printf("|          \x1b[1;33md\x1b[0m - Delete Current        |\n");
	    printf("|          \x1b[1;33mt\x1b[0m - Add previous          |\n");
	    printf("|            \x1b[1;33mz\x1b[0m - Add next            |\n");
	    printf(" -----------------------------------\n");

	}
};

#endif
