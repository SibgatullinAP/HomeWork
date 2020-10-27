#include "tree.h"


TreeNode * Tree::getRoot()
{
    return Root;
}

Tree::~Tree()
{
    deleteTree(Root);
}

int Tree::read(FILE *inFile)
{
    deleteTree(Root);

    char buff[BUFF_LEN];
    char name[BUFF_LEN];
    int phone = 0, group = 0;

    while (fgets(buff, BUFF_LEN, inFile))
    {

	if(sscanf(buff,"%s %d %d", name, &phone, &group) != 3)
	{
	    return ERROR_CANNOT_READ_INPUT_FILE;
	}
	insert(name, phone, group);
    }
    return 0;
}

\

void Tree::deleteTree(TreeNode *tmp)
{
    if(tmp != nullptr)
    {
	deleteTree(tmp -> LeftChild);
	deleteTree(tmp -> RightChild);
    }
    if(tmp == Root)
    {
	Root = nullptr;
    }
    delete tmp;
}

void Tree::insert(char *Name, int Phone, int Group)
{
    TreeNode *tmp = new TreeNode;

    tmp->setName(Name);
    tmp->setPhone(Phone);
    tmp->setGroup(Group);

    Root = binaryInsertion(Root, tmp);
    balanceInsert(Root, tmp);
}

TreeNode* Tree::binaryInsertion(TreeNode* root, TreeNode *tmp)
{
    if (root == nullptr)
       return tmp;

    if (*tmp < *root)
    {
        root->LeftChild  = binaryInsertion(root->LeftChild, tmp);
	root->LeftChild->Parent = root;
    }
    else if (*tmp > *root)
    {
        root->RightChild = binaryInsertion(root->RightChild, tmp);
	root->RightChild->Parent = root;
    }

    return root;
}

void Tree::deleteValue(char *Name, int Phone, int Group)
{
    Record * reference = nullptr;
    reference = new Record;
    reference->setName(Name);
    reference->setPhone(Phone);
    reference->setGroup(Group);

    TreeNode *node = binaryDeletion(Root, reference);
    node->print();
    balanceDelete(node);
}


TreeNode* Tree::binaryDeletion(TreeNode *root, Record *reference) {
    if (root == nullptr)
	return root;

    if (*reference < *root)
    {
	return binaryDeletion(root->LeftChild, reference);
    }

    if (*reference > *root)
    {
	return binaryDeletion(root->RightChild, reference);
    }

    if (root->LeftChild == nullptr || root->RightChild == nullptr)
    {
	return root;
    }

    TreeNode *tmp = minValue(root->RightChild);
    root->setName(tmp->getName());
    root->setPhone(tmp->getPhone());
    root->setGroup(tmp->getGroup());

    return binaryDeletion(root->RightChild, tmp);
}

TreeNode *Tree::minValue(TreeNode *root)
{
    TreeNode *ptr = root;
    while (ptr->LeftChild != nullptr)
    {
	ptr = ptr->LeftChild;
    }

    return ptr;
}

TreeNode *Tree::maxValue(TreeNode *root)
{
    TreeNode *ptr = root;
    while (ptr->RightChild != nullptr)
    {
	ptr = ptr->RightChild;
    }

    return ptr;
}


void Tree::balanceDelete(TreeNode *tmp)
{
    if(tmp == nullptr)
    {
	return;
    }

    if(tmp == Root)
    {
	Root = nullptr;
	return;
    }

    if(tmp->Color == RED || tmp->LeftChild->Color == RED || tmp->RightChild->Color == RED)
    {
	TreeNode *child = tmp->LeftChild != nullptr ? tmp->LeftChild : tmp->RightChild;

	if(tmp == tmp->Parent->LeftChild)
	{
	    tmp->Parent->LeftChild = child;
	    if(child != nullptr)
	    {
		child->Parent = tmp->Parent;
	    }
	    child->Color = BLACK;
	    delete (tmp);
	}
	else
	{
	    tmp->Parent->RightChild = child;
	    if(child != nullptr)
	    {
		child->Parent = tmp->Parent;
	    }
	    child->Color = BLACK;
	    delete (tmp);
	}
    }
    else
    {
	TreeNode *brother = nullptr;
	TreeNode *parent = nullptr;
	TreeNode *ptr = tmp;
	ptr->Color = DOUBLE_BLACK;
	while(ptr != Root && ptr->Color == DOUBLE_BLACK)
	{
	    parent = ptr->Parent;
	    if(ptr == parent->LeftChild)
	    {
		brother = parent->RightChild;
		if(brother->Color == RED)
		{
		    brother->Color = BLACK;
		    parent->Color = RED;
		    rotateLeft(Root, parent);
		}
		else
		{
		    if(brother->LeftChild->Color == BLACK && brother->RightChild->Color == BLACK)
		    {
			brother->Color = RED;
			if(parent->Color == RED)
			{
			    parent->Color = BLACK;
			}
			else
			{
			    parent->Color = DOUBLE_BLACK;
			}
			ptr = parent;
		    }
		    else
		    {
			if(brother->RightChild->Color == BLACK)
			{
			    brother->LeftChild->Color = BLACK;
			    brother->Color = RED;
			    rotateRight(Root, brother);
			    brother = parent->RightChild;
			}
			brother->Color = parent->Color;
			parent->Color = BLACK;
			brother->RightChild->Color = BLACK;
			rotateLeft(Root, parent);
			break;
		    }
		}
	    }
	    else
	    {
		brother = parent->LeftChild;
		if(brother->Color == RED)
		{
		    brother->Color = BLACK;
		    parent->Color = RED;
		    rotateRight(Root, parent);
		}
		else
		{
		    if(brother->LeftChild->Color == BLACK && brother->RightChild->Color == BLACK)
		    {
			brother->Color = RED;
			if(parent->Color == RED)
			{
			    parent->Color = BLACK;
			}
			else
			{
			    parent->Color = DOUBLE_BLACK;
			}
			ptr = parent;
		    }
		    else
		    {
			if(brother->LeftChild->Color == BLACK)
			{
			    brother->RightChild->Color = BLACK;
			    brother->Color = RED;
			    rotateLeft(Root, brother);
			    brother = parent->LeftChild;
			}
			brother->Color = parent->Color;
			parent->Color = BLACK;
			brother->LeftChild->Color = BLACK;
			rotateRight(Root, parent);
			break;
		    }
		}
	    }
	}
	if (tmp == tmp->Parent->LeftChild)
	{
	    tmp->Parent->LeftChild = nullptr;
	}
	else
	{
	    tmp->Parent->RightChild = nullptr;
	}
	delete(tmp);
	Root->Color = BLACK;
    }
}



void Tree::rotateLeft(TreeNode *&root, TreeNode *&tmp)
{
    TreeNode *tmpRight = tmp->RightChild;

    tmp->RightChild = tmpRight->LeftChild;

    if (tmp->RightChild != nullptr)
    {
	tmp->RightChild->Parent = tmp;
    }

    tmpRight->Parent = tmp->Parent;

    if (tmp->Parent == nullptr)
    {
	root = tmpRight;
    }
    else if (tmp == tmp->Parent->LeftChild)
    {
        tmp->Parent->LeftChild = tmpRight;
    }
    else
    {
	tmp->Parent->RightChild = tmpRight;
    }

    tmpRight->LeftChild = tmp;
    tmp->Parent = tmpRight;
}

void Tree::rotateRight(TreeNode *&root, TreeNode *&tmp)
{
    TreeNode *tmpLeft = tmp->LeftChild;

    tmp->LeftChild = tmpLeft->RightChild;

    if (tmp->LeftChild != nullptr)
    tmp->LeftChild->Parent = tmp;

    tmpLeft->Parent = tmp->Parent;

    if (tmp->Parent == nullptr)
    root = tmpLeft;

    else if (tmp == tmp->Parent->LeftChild)
    tmp->Parent->LeftChild = tmpLeft;

    else
    tmp->Parent->RightChild = tmpLeft;

    tmpLeft->RightChild = tmp;
    tmp->Parent = tmpLeft;
}

void Tree::balanceInsert(TreeNode *&root, TreeNode *&tmp)
{
    TreeNode *parentTmp = nullptr;
    TreeNode *grandParentTmp = nullptr;

    while ((tmp != root) && (tmp->Color != BLACK) &&
           (tmp->Parent->Color == RED))
    {

	parentTmp = tmp->Parent;
	grandParentTmp = tmp->Parent->Parent;

	if (parentTmp == grandParentTmp->LeftChild)
	{

	    TreeNode *uncleTmp = grandParentTmp->RightChild;

	    if (uncleTmp != nullptr && uncleTmp->Color == RED)
	    {
		grandParentTmp->Color = RED;
		parentTmp->Color = BLACK;
		uncleTmp->Color = BLACK;
		tmp = grandParentTmp;
	    }
	    else
	    {
		if (tmp == parentTmp->RightChild)
		{
		    rotateLeft(root, parentTmp);
		    tmp = parentTmp;
		    parentTmp = tmp->Parent;
		}

		rotateRight(root, grandParentTmp);

                color swap = parentTmp->Color;
		parentTmp->Color = grandParentTmp->Color;
                grandParentTmp->Color = swap;

		tmp = parentTmp;
	    }
	}

	else
	{
	    TreeNode *uncleTmp = grandParentTmp->LeftChild;

	    if ((uncleTmp != nullptr) && (uncleTmp->Color == RED))
	    {
		grandParentTmp->Color = RED;
		parentTmp->Color = BLACK;
		uncleTmp->Color = BLACK;
		tmp = grandParentTmp;
	    }
	    else
	    {
		if (tmp == parentTmp->LeftChild)
		{
		    rotateRight(root, parentTmp);
		    tmp = parentTmp;
		    parentTmp = tmp->Parent;
		}

		rotateLeft(root, grandParentTmp);

                color swap = parentTmp->Color;
		parentTmp->Color = grandParentTmp->Color;
		grandParentTmp->Color = swap;

		tmp = parentTmp;
	    }
	}
    }
    root->Color = BLACK;
}

void Tree::print(TreeNode *root , int level, int maxPrint)
{
        maxPrint ++;
	if(root->Color == RED)
	{
	    printf("\x1b[41m");
	}
	else
	{
	    printf("\x1b[40m");
	}
	root -> print();
	level ++;
	if(maxPrint < MAX_PRINT_TREE && root -> LeftChild)
	{
	    for (int i = 0; i < level ; ++i)
	    {
		printf("%c",' ');
	    }
	    print(root -> LeftChild, ++level, maxPrint);
	}
	if(maxPrint < MAX_PRINT_TREE && root -> RightChild)
	{
	    for (int i = 0; i < level - 1; ++i)
	    {
		printf("%c", ' ');
	    }
	    print(root -> RightChild, ++level, maxPrint);
	}
}


