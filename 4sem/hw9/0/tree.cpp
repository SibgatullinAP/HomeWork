#include "tree.h"

void Tree::menu()
{
    clear();
    print_menu();

    MENU_PROPERTIES key;
    char buff[LEN];
    Current = Root;
    for(;;)
    {
        printf("Enter your choise: ");
	if(!fgets(buff, LEN, stdin)) return;

        key = MENU_PROPERTIES(buff[0]);
        switch(key)
        {
            case MENU:
		clear();
                print_menu();
                break;

            case EXIT:
                return;

            case PRINT_TREE:
		clear();
		if(Root != nullptr) print(Root, 0, stdout);
		else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
                printf("\n");
                break;

	    case PRINT_SUBTREE:
		clear();
		if(Current != nullptr) print(Current, 0, stdout);
		else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
		printf("\n");
		break;

            case PRINT_CURRENT:
		clear();
		if(Current != nullptr) Current->print();
		else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
                printf("\n");
                break;

            case WORK_WITH_QUEUE:
		clear();
		if(Current != nullptr) Current->menu();
		else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
                break;

	    case DELETE_TREE:
		clear();
		delete_tree(Root);
		break;

            case DELETE_CHILD_SUBTREE:
		clear();
		delete_child_tree();
                printf("\n");
                break;

            case DELETE_BROTHER_SUBTREE:
		clear();
		if(Current == Root)
		{
		    printf("Root has no brothers!\n");
		    break;
		}
		delete_brother_tree();
                printf("\n");
		break;

            case GO_TO_BROTHER:
		clear();
		if(Current != nullptr && Current->Brother != nullptr) Current = Current->Brother;
		else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
                printf("\n");
                break;

	    case GO_DOWN:
		clear();
		if(Current != nullptr && Current->Child != nullptr) Current = Current->Child;
		else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
                printf("\n");
                break;

            case GO_ROOT:
		clear();
		if(Root != nullptr) Current = Root;
		else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
                printf("\n");
                break;

            case ADD_ROOT:
		clear();
		addRoot();
                printf("\n");
                break;

            case ADD_BROTHER:
		clear();
		if(Current == Root)
		{
		    printf("Root has no brothers!\n");
		    break;
		}
		if(Current != nullptr)
		{
		    addBrother();
		    Current = Current->Brother;
		}
		else printf ("ATTETNTION: you've just tried to work with an empty element!\n");
                printf("\n");
                break;

            case ADD_CHILD:
		clear();
		if(Current != nullptr)
		{
		    addChild();
		    Current = Current->Child;
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

void Tree::print_menu()
{
    printf(" ------------------------------------\n");
    printf("|          ~Menu for Tree~           |\n");
    printf("|           \x1b[1;33mm\x1b[0m - Show Menu            |\n");
    printf("|           \x1b[1;33me\x1b[0m - Exit Menu            |\n");
    printf("|          \x1b[1;33mp\x1b[0m - Print Tree            |\n");
    printf("|    \x1b[1;33ms\x1b[0m - Print Current's Subtree     |\n");
    printf("|         \x1b[1;33mc\x1b[0m - Print Current          |\n");
    printf("|        \x1b[1;33mw\x1b[0m - Work with Queue         |\n");
    printf("|          \x1b[1;33mx\x1b[0m - Delete Tree           |\n");
    printf("|    \x1b[1;33my\x1b[0m - Delete brother's Subtree    |\n");
    printf("|     \x1b[1;33mz\x1b[0m - Delete child's Subtree     |\n");
    printf("|         \x1b[1;33mb\x1b[0m - Go to brother          |\n");
    printf("|            \x1b[1;33mv\x1b[0m - Go child            |\n");
    printf("|            \x1b[1;33mr\x1b[0m - Go Root             |\n");
    printf("|            \x1b[1;33mh\x1b[0m - Add Root            |\n");
    printf("|           \x1b[1;33ma\x1b[0m - Add brother          |\n");
    printf("|           \x1b[1;33ml\x1b[0m - Add child            |\n");
    printf(" ------------------------------------\n");
}

void Tree::delete_tree(TreeNode *tmp)
{
    if(tmp != nullptr)
    {
        delete_tree(tmp -> Child);
        delete_tree(tmp -> Brother);
    }
    if(tmp == Root)
    {
        Root = nullptr;
    }
    delete tmp;
    Current = Root;
}

void Tree::delete_child_tree()
{
    if(Current != nullptr && Current->Child != nullptr)
    {
	delete_tree(Current->Child);
	Current->Child = nullptr;
    }
}

void Tree::delete_brother_tree()
{
    if(Current != nullptr && Current->Brother != nullptr)
    {
	TreeNode* tmp = Current->Brother;
	if(Current->Brother->Brother != nullptr)
	{
	    Current->Brother = Current->Brother->Brother;
	    tmp->Brother = nullptr;
	    delete_tree(tmp);
	}
	else
	{
	    delete_tree(tmp);
	    Current->Brother = nullptr;
	}
    }
}

int Tree::read(FILE *fp, int size_tree, int size_queue)
{
    delete_tree(Root);

    TreeNode *tmp = nullptr;
    tmp = new TreeNode ();
    if (tmp == nullptr)
    {
        return ERROR_CANNOT_ALLOCATE_MEMMORY;
    }
    int ret = tmp -> read(fp, size_queue);
    if (ret < 0)
    {
        return delete tmp, ret;
    }
    tmp->Brother = nullptr;
    Root = Current = tmp;
    int i = 1;
    for (;;)
    {
        i++;
        if(i > size_tree)
        {
            return 0;
        }
        tmp = new TreeNode ();
        if (tmp == nullptr)
        {
           	return ERROR_CANNOT_ALLOCATE_MEMMORY;
        }
        ret = tmp->read(fp, size_queue);
        if (ret < 0)
        {
            return delete tmp, ret;
        }
        add(Current, tmp);
        tmp = nullptr;
    }
    return 0;
}


void Tree::print(TreeNode *root, int max_print, FILE* out)
{
    if(root == nullptr)
    {
	printf("    Empty tree!\n");
	return;
    }
    if (max_print >= MAX_PRINT_TREE)
    {
        return;
    }
    fprintf(out,"       ");
    for (int i = 0; i < max_print * 3; ++i)
    {
        if (fmod(i,3) == 0)
        {
            fprintf(out,"| ");
        }
        else
        {
           fprintf(out," ");
        }
    }
    root->print(out);
    if (root->Child != nullptr)
    {
        print(root->Child, max_print + 1, out);
    }
    if (root->Brother != nullptr)
    {
        print(root->Brother, max_print, out);
    }
}

void Tree::add(TreeNode *root, TreeNode *tmp)
{
    if (root->Child == nullptr)
    {
        root->Child = tmp;
    }
    else if(root->Child->Brother == nullptr)
    {
        if (*(root->Child) < *root )
        {
            if (!(*tmp < *root))
            {
                root->Child->Brother = tmp; 
            }
            else
            {
                add(root->Child, tmp);
            }
        }
        else if(*(root->Child) > *root)
        {
            if (!(*tmp > *root))
            {
                tmp->Brother = root->Child;
                root->Child = tmp;
            }
            else
            {
                add(root->Child, tmp);
            }
        }
        else
        {
            if (*tmp < *root)
            {
                tmp->Brother = root->Child;
                root->Child = tmp;
            }
            else if(*tmp > *root)
            {
                root->Child->Brother = tmp;
            }
            else
            {
                add(root->Child, tmp);
            }
        }
    }
    else if(root->Child->Brother->Brother == nullptr)
    {
        if (*(root->Child) < *root)
        {
            if (*root < *(root->Child->Brother))
            {
                if (*tmp < *root)
                {
                    add(root->Child, tmp);
                }
                else if (*tmp > *root)
                {
                    add(root->Child->Brother, tmp);
                }
                else
                {
                    tmp->Brother = root->Child->Brother;
                    root->Child->Brother = tmp;
                }
            }
            else
            {
                if (*tmp < *root)
                {
                    add(root->Child, tmp);
                }
                else if(*tmp > *(root->Child))
                {
                    root->Child->Brother->Brother = tmp;
                }
                else
                {
                    add(root->Child->Brother, tmp);
                }
            }
        }
        else
        {
            if (*tmp < *root)
            {
                tmp->Brother = root->Child;
                root->Child = tmp;
            }
            else if (*tmp > *root)
            {
                add(root->Child->Brother, tmp);
            }
            else
            {
                add(root->Child, tmp);
            }
        }
    }
    else
    {
        if (*tmp < *root)
        {
            add(root->Child, tmp);
        }
        else if (*tmp > *root)
        {
            add(root->Child->Brother->Brother, tmp);
        }
        else
        {
            add(root->Child->Brother, tmp);
        }
    }
}

void Tree::addRoot()
{
    TreeNode* tmp = new TreeNode;
    if(Root == nullptr)
    {
        Root = Current = tmp;
    }
    else
    {
        tmp->Child = Root;
        Root = Current = tmp;
    }
}

void Tree::addChild()
{
    if(Current != nullptr)
    {
	TreeNode *tmp = new TreeNode;
	if(Current->Child != nullptr)
	{
	    tmp->Child = Current->Child;
	    tmp->Brother = nullptr;
	    Current->Child = tmp;
	}
	else
	{
	    Current->Child = tmp;
	    tmp->Child = nullptr;
	}
    }
}

void Tree::addBrother()
{
    if(Current != nullptr)
    {
	TreeNode *tmp = new TreeNode;
	if(Current->Brother != nullptr)
	{
	    tmp->Brother = Current->Brother;
	    tmp->Child = nullptr;
	    Current->Brother = tmp;
	}
	else
	{
	    Current->Brother = tmp;
	    tmp->Brother = nullptr;
	}
    }
}

TreeNode* Tree::get_root() const
{
    return Root;
}


TreeNode* Tree::del_sub_level()
{
    delete_tree(Current -> Brother );
    return Root;
}

TreeNode* Tree::del_sub_tree()
{
    delete_tree(Current -> Child);
    return Root;
}

