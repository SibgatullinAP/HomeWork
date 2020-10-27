#include "RedBlackTree.h"

RedBlackTree::RedBlackTree(int HashSize)
{
    HashChar = HashSize;
    NILL = new RedBlackTreeNode;
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
    root->print();
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

RedBlackTreeNode * RedBlackTree::search(ListNode * reference)
{
    RedBlackTreeNode *tmp = Root;
    while (tmp != NILL)
    {
	if(*tmp == *reference)
	{
	    return tmp;
	}

	if(*tmp > *reference)
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

bool RedBlackTree::isContain(ListNode * reference)
{
    RedBlackTreeNode *tmp = Root;
    while (tmp != NILL)
    {
	if(*tmp == *reference)
	{
	    return true;
	}

	if(*tmp > *reference)
	{
	    tmp = tmp->LeftChild;
	}
	else
	{
	    tmp = tmp->RightChild;
	}
    }

    return false;
}

bool RedBlackTree::insert(ListNode *data)
{
    if(!isContain(data))
    {
	RedBlackTreeNode * tmp = new RedBlackTreeNode(HashChar);
	tmp->Parent = tmp->LeftChild = tmp->RightChild = NILL;
	tmp->Group = data->getGroup();

	tmp->NameSearch->insert(data);
	tmp->PhoneSearch->insert(data);

	Root = binaryInsertion(Root, tmp);
	balanceInsert(Root,tmp);

	return true;
    }
    else
    {
	RedBlackTreeNode * tmp = search(data);

	tmp->NameSearch->insert(data);
	tmp->PhoneSearch->insert(data);

	return true;
    }
    return false;
}

RedBlackTreeNode* RedBlackTree::binaryInsertion(RedBlackTreeNode* root, RedBlackTreeNode *tmp)
{
    if (root == NILL)
    {
	return tmp;
    }

    if (*root > *tmp)
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

void RedBlackTree::deleteValue(ListNode * reference)
{
    RedBlackTreeNode * found = search(reference);
    if(found != NILL)
    {
	if(found->NameSearch->Root->LeftChild != found->NameSearch->NILL && found->NameSearch->Root->RightChild == found->NameSearch->NILL)
	{
	    found->NameSearch->deleteValue(reference);
	    found->PhoneSearch->deleteValue(reference);
	}
	else if(found->NameSearch->Root->LeftChild == found->NameSearch->NILL && found->NameSearch->Root->RightChild == found->NameSearch->NILL && (* found->NameSearch->Root == *reference))
	{
	    found->NameSearch->Root = found->NameSearch->NILL;
	    found->PhoneSearch->~Hash();
	    found->PhoneSearch = new Hash(HashChar);

	}
	else
	{
	    found->NameSearch->deleteValue(reference);
	    found->PhoneSearch->deleteValue(reference);
	}
    }
}

RedBlackTreeNode * RedBlackTree::binaryDeletion(RedBlackTreeNode *found)
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
	Root = supposedLeft;
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
	found->NameSearch = foundBuff->NameSearch;
	found->PhoneSearch = foundBuff->PhoneSearch;
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
