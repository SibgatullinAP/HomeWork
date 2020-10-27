#include "RedBlackTree.h"

RedBlackTree::RedBlackTree()
{
    NILL->Color = BLACK;
    Root = NILL;
}

RedBlackTree::~RedBlackTree()
{
    deleteRedBlackTree(Root);
    delete NILL;
}

RedBlackTreeNode * RedBlackTree::getRoot()
{
    return Root;
}

int RedBlackTree::read(FILE *inFile)
{
    //deleteRedBlackTree(Root);

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

void RedBlackTree::print(RedBlackTreeNode *root , int level, int maxPrint)
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
	root->Data->print();
	level ++;
	if(maxPrint < MAX_PRINT_TREE && root -> LeftChild != NILL)
	{
	    for (int i = 0; i < level ; ++i)
	    {
		printf("%c",' ');
	    }
	    printf("L: ");
	    print(root -> LeftChild, ++level, maxPrint);
	}
	if(maxPrint < MAX_PRINT_TREE && root -> RightChild != NILL)
	{
	    for (int i = 0; i < level - 1; ++i)
	    {
		printf("%c", ' ');
	    }
	    printf("R: ");
	    print(root -> RightChild, ++level, maxPrint);
	}
}

void RedBlackTree::deleteRedBlackTree(RedBlackTreeNode *tmp)
{
    if(tmp != NILL)
    {
	deleteRedBlackTree(tmp -> LeftChild);
	deleteRedBlackTree(tmp -> RightChild);
	delete tmp->Data;
	delete tmp;
    }
}

void RedBlackTree::rotateLeft(RedBlackTreeNode *&root, RedBlackTreeNode *&tmp)
{
    RedBlackTreeNode *tmpRight = tmp->RightChild;

    tmp->RightChild = tmpRight->LeftChild;

    if (tmp->RightChild != NILL)
    {
	tmp->RightChild->Parent = tmp;
    }

    tmpRight->Parent = tmp->Parent;

    if (tmp->Parent == NILL)
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

void RedBlackTree::rotateRight(RedBlackTreeNode *&root, RedBlackTreeNode *&tmp)
{
    RedBlackTreeNode *tmpLeft = tmp->LeftChild;

    tmp->LeftChild = tmpLeft->RightChild;

    if (tmp->LeftChild != NILL)
    tmp->LeftChild->Parent = tmp;

    tmpLeft->Parent = tmp->Parent;

    if (tmp->Parent == NILL)
    root = tmpLeft;

    else if (tmp == tmp->Parent->LeftChild)
    tmp->Parent->LeftChild = tmpLeft;

    else
    tmp->Parent->RightChild = tmpLeft;

    tmpLeft->RightChild = tmp;
    tmp->Parent = tmpLeft;
}

RedBlackTreeNode *RedBlackTree::minValue(RedBlackTreeNode *root)
{
    RedBlackTreeNode *ptr = root;
    while (ptr != NILL && ptr->LeftChild != NILL)
    {
	ptr = ptr->LeftChild;
    }

    return ptr;
}

RedBlackTreeNode * RedBlackTree::search(RedBlackTreeNode * reference)
{
    RedBlackTreeNode *tmp = Root;
    while (tmp != NILL)
    {
	if(*reference == *tmp)
	{
	    return tmp;
	}

	if(*reference < *tmp)
	{
	    tmp = tmp->LeftChild;
	}
	else
	{
	    tmp = tmp->RightChild;
	}
    }

    return tmp;
}

void RedBlackTree::insert(char *Name, int Phone, int Group)
{
    Record * data = new Record;
    data->setName(Name);
    data->setPhone(Phone);
    data->setGroup(Group);

    RedBlackTreeNode * tmp = new RedBlackTreeNode;
    tmp->Data = data;
    tmp->Parent = tmp->LeftChild = tmp->RightChild = NILL;

    Root = binaryInsertion(Root, tmp);
    balanceInsert(Root,tmp);
}

RedBlackTreeNode* RedBlackTree::binaryInsertion(RedBlackTreeNode* root, RedBlackTreeNode *tmp)
{
    if (root == NILL)
    {
	return tmp;
    }

    if (*tmp < *root)
    {
        root->LeftChild  = binaryInsertion(root->LeftChild, tmp);
	root->LeftChild->Parent = root;
    }
    else
    {
        root->RightChild = binaryInsertion(root->RightChild, tmp);
	root->RightChild->Parent = root;
    }

    return root;
}

void RedBlackTree::balanceInsert(RedBlackTreeNode *&root, RedBlackTreeNode *&tmp)
{
    RedBlackTreeNode *parentTmp = NILL;
    RedBlackTreeNode *grandParentTmp = NILL;
    RedBlackTreeNode *uncleTmp;

    while ((tmp != root) && (tmp->Color == RED) && (tmp->Parent->Color == RED))
    {

	parentTmp = tmp->Parent;
	grandParentTmp = parentTmp->Parent;

	if (parentTmp == grandParentTmp->LeftChild)
	{

	    uncleTmp = grandParentTmp->RightChild;

	    if (uncleTmp->Color == RED)
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
	    uncleTmp = grandParentTmp->LeftChild;

	    if ((uncleTmp->Color == RED))
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

void RedBlackTree::deleteValue(char *Name, int Phone, int Group)
{
    Record * reference = nullptr;
    reference = new Record;
    reference->setName(Name);
    reference->setPhone(Phone);
    reference->setGroup(Group);

    RedBlackTreeNode * tmp = new RedBlackTreeNode;
    tmp->Data = reference;

    RedBlackTreeNode * found = search(tmp);
    if(found != NILL)
    {
	RedBlackTreeNode * buff = binaryDeletion(Root, found);
	//delete buff->Data;
	delete buff;
    }
    else
    {
	printf("NotFound\n");
    }

    delete tmp->Data;
    delete tmp;
}

RedBlackTreeNode * RedBlackTree::binaryDeletion(RedBlackTreeNode *root, RedBlackTreeNode *found)
{
    RedBlackTreeNode *foundBuff = NILL;
    RedBlackTreeNode *supposedLeft = NILL;

    if(found->LeftChild == NILL || found->RightChild == NILL)
    {
	foundBuff = found;
    }
    else
    {
	foundBuff = child(found);
    }

    if(foundBuff->LeftChild != NILL)
    {
	supposedLeft = foundBuff->LeftChild;
    }
    else
    {
	supposedLeft = foundBuff->RightChild;
    }

    supposedLeft->Parent = foundBuff->Parent;

    if(foundBuff->Parent == NILL)
    {
	root = supposedLeft;
    }
    else if(foundBuff->Parent->LeftChild == foundBuff)
    {
	foundBuff->Parent->LeftChild = supposedLeft;
    }
    else
    {
	foundBuff->Parent->RightChild = supposedLeft;
    }

    if(foundBuff != found)
    {
	found->Data = foundBuff->Data;
    }

    if(foundBuff->Color == BLACK)
    {
	balanceDelete(supposedLeft);
    }

    return foundBuff;
}

RedBlackTreeNode * RedBlackTree::child(RedBlackTreeNode *tmp)
{
    if(tmp->RightChild != NILL)
    {
	return minValue(tmp->RightChild);
    }

    RedBlackTreeNode * par = tmp->Parent;
    while(par != NILL && tmp == par->RightChild)
    {
	tmp = par;
	par = par->Parent;
    }

    return par;
}

void RedBlackTree::balanceDelete(RedBlackTreeNode *tmp)
{
    RedBlackTreeNode *buff;
    while (tmp != Root && tmp->Color == BLACK)
    {
	if (tmp == tmp->Parent->LeftChild)
	{
	    buff = tmp->Parent->RightChild;
	    if (buff->Color == RED)
	    {
		buff->Color = BLACK;
		tmp->Parent->Color = RED;
		rotateLeft(Root, tmp->Parent);
		buff = tmp->Parent->RightChild;
	    }

	    if (buff->LeftChild->Color == BLACK && buff->RightChild->Color == BLACK)
	    {
		buff->Color = RED;
		tmp = tmp->Parent;
	    }
	    else
	    {
		if (buff->RightChild->Color == BLACK)
		{
		    buff->LeftChild->Color = BLACK;
		    buff->Color = RED;
		    rotateRight(Root, buff);
		    buff = tmp->Parent->RightChild;
		}

		buff->Color = tmp->Parent->Color;
		tmp->Parent->Color = BLACK;
		buff->RightChild->Color = BLACK;
		rotateLeft(Root, tmp->Parent);
		tmp = Root;
	    }
	}
	else
	{
	    buff = tmp->Parent->LeftChild;
	    if (buff->Color == RED)
	    {
		buff->Color = BLACK;
		tmp->Parent->Color = RED;
		rotateRight(Root, tmp->Parent);
		buff = tmp->Parent->LeftChild;
	    }

	    if (buff->RightChild->Color == BLACK && buff->RightChild->Color == BLACK)
	    {
		buff->Color = RED;
		tmp = tmp->Parent;
	    }
	    else
	    {
		if (buff->LeftChild->Color == BLACK)
		{
		    buff->RightChild->Color = BLACK;
		    buff->Color = RED;
		    rotateLeft(Root, buff);
		    buff = tmp->Parent->LeftChild;
		}

		buff->Color = tmp->Parent->Color;
		tmp->Parent->Color = BLACK;
		buff->LeftChild->Color = BLACK;
		rotateRight(Root, tmp->Parent);
		tmp = Root;
	    }
	}
    }
    tmp->Color = BLACK;
}
