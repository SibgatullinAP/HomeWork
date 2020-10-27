#include "RedBlackTreeName.h"

RedBlackTreeName::RedBlackTreeName()
{
    NILL->Color = BLACK;
    Root = NILL;
}

/*ListNode * RedBlackTreeName::search(const Command & current, int flagType, int flag)
{
    if(Root == NILL)
    {
	return nullptr;
    }

    ListNode *begin = nullptr;
    ListNode *previous = nullptr;
    RedBlackTreeNameNode * tmp = Root;

    while (tmp != NILL)
    {
	if(*tmp == current)
	{
	    break;
	}
	else if( *tmp > current)
	{
	    tmp = tmp->RightChild;
	}
	else
	{
	    tmp = tmp->LeftChild;
	}
    }

    if(flag)
    {
	while (tmp) {

	}
    }

}*/

RedBlackTreeName::~RedBlackTreeName()
{
    deleteRedBlackTreeName(Root);
    delete NILL;
}

RedBlackTreeNameNode * RedBlackTreeName::getRoot()
{
    return Root;
}

void RedBlackTreeName::print(RedBlackTreeNameNode *root , int level, int maxPrint)
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
    for(RedBlackTreeNameNode * tmp = root->Next; tmp != NILL ; tmp = tmp->Next)
    {
	tmp->Data->print();
    }
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

void RedBlackTreeName::deleteRedBlackTreeName(RedBlackTreeNameNode *tmp)
{
    if(tmp != NILL)
    {
	deleteRedBlackTreeName(tmp -> LeftChild);
	deleteRedBlackTreeName(tmp -> RightChild);

	RedBlackTreeNameNode * current = tmp;
	while (tmp != NILL)
	{
	    current = tmp->Next;
	    delete tmp;
	    tmp = current;
	}
    }
}

void RedBlackTreeName::rotateLeft(RedBlackTreeNameNode *&root, RedBlackTreeNameNode *&tmp)
{
    RedBlackTreeNameNode *tmpRight = tmp->RightChild;

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

void RedBlackTreeName::rotateRight(RedBlackTreeNameNode *&root, RedBlackTreeNameNode *&tmp)
{
    RedBlackTreeNameNode *tmpLeft = tmp->LeftChild;

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

RedBlackTreeNameNode *RedBlackTreeName::minValue(RedBlackTreeNameNode *root)
{
    RedBlackTreeNameNode *ptr = root;
    while (ptr != NILL && ptr->LeftChild != NILL)
    {
	ptr = ptr->LeftChild;
    }

    return ptr;
}

RedBlackTreeNameNode * RedBlackTreeName::searchDeletion(ListNode * reference)
{
    RedBlackTreeNameNode *tmp = Root;
    while (tmp != NILL)
    {
	if(*tmp == *reference)
	{

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

bool RedBlackTreeName::isContain(ListNode * reference)
{
    //reference->print();
    RedBlackTreeNameNode *tmp = Root;
    while (tmp != NILL)
    {
	if(*tmp == *reference)
	{
	    RedBlackTreeNameNode * curr = tmp;
	    while (curr != NILL)
	    {
		if(curr->Data->getGroup() == reference->getGroup()
		    && curr->Data->getPhone() == reference->getPhone())
		{
		    return true;
		}
		curr = curr->Next;
	    }
	    return false;
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

bool RedBlackTreeName::insert(ListNode *data)
{
    if(!isContain(data))
    {
	RedBlackTreeNameNode * tmp = new RedBlackTreeNameNode;
	tmp->Data = data;
	tmp->Next = tmp->Parent = tmp->LeftChild = tmp->RightChild = NILL;

	Root = binaryInsertion(Root, tmp);
	balanceInsert(Root,tmp);

	return true;
    }
    return false;
}

RedBlackTreeNameNode* RedBlackTreeName::binaryInsertion(RedBlackTreeNameNode* root, RedBlackTreeNameNode *tmp)
{
    if (root == NILL)
    {
	return tmp;
    }

    if (*tmp < *root->Data)
    {
        root->LeftChild  = binaryInsertion(root->LeftChild, tmp);
	root->LeftChild->Parent = root;
    }
    else if (*tmp > *root->Data)
    {
        root->RightChild = binaryInsertion(root->RightChild, tmp);
	root->RightChild->Parent = root;
    }
    else
    {
	RedBlackTreeNameNode * buff = root;
	while (buff->Next != NILL)
	{
	    buff = buff->Next;
	}
	buff->Next = tmp;
    }

    return root;
}

void RedBlackTreeName::balanceInsert(RedBlackTreeNameNode *&root, RedBlackTreeNameNode *&tmp)
{
    RedBlackTreeNameNode *parentTmp = NILL;
    RedBlackTreeNameNode *grandParentTmp = NILL;
    RedBlackTreeNameNode *uncleTmp;

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

void RedBlackTreeName::deleteValue(ListNode *reference)
{
    RedBlackTreeNameNode * found = searchDeletion(reference);
    if(found != NILL)
    {
	RedBlackTreeNameNode * buff = binaryDeletion(found);
	delete buff;
    }
}

RedBlackTreeNameNode * RedBlackTreeName::binaryDeletion(RedBlackTreeNameNode *found)
{
    RedBlackTreeNameNode *foundBuff = NILL;
    RedBlackTreeNameNode *supposedLeft = NILL;

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
	found->Data = foundBuff->Data;
	found->Next = foundBuff->Next;
    }

    if(foundBuff->Color == BLACK)
    {
	balanceDelete(supposedLeft);
    }

    return foundBuff;
}

RedBlackTreeNameNode * RedBlackTreeName::child(RedBlackTreeNameNode *tmp)
{
    if(tmp->RightChild != NILL)
    {
	return minValue(tmp->RightChild);
    }

    RedBlackTreeNameNode * par = tmp->Parent;
    while(par != NILL && tmp == par->RightChild)
    {
	tmp = par;
	par = par->Parent;
    }

    return par;
}

void RedBlackTreeName::balanceDelete(RedBlackTreeNameNode *tmp)
{
    RedBlackTreeNameNode *buff;
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
