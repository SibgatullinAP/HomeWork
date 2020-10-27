#include "AVLTree.h"

ListNode * AVLTree::search(Command & command, int flagType, int flag, ListNode *& begin)
{
    (void)flag;
    (void)flagType;

    AVLTreeNode * tmp = Root;
    while (tmp != nullptr)
    {
	if(tmp->Data->getPhone() == command.getPhone())
	{
	    break;
	}
	else if(tmp->Data->getPhone() < command.getPhone())
	{
	    tmp = tmp->RightChild;
	}
	else
	{
	    tmp = tmp->LeftChild;
	}
    }

    if (tmp == nullptr)
    {
	return nullptr;
    }

    if(command.check(tmp->Data))
    {
	begin = tmp->Data;
	begin->NextSelect = nullptr;
    }

    traverse(command, tmp->RightChild, begin, flagType);
    traverse(command, tmp->LeftChild, begin, flagType);

    return begin;
}

void AVLTree::traverse(Command &command, AVLTreeNode *tmp, ListNode *& begin, int flagType)
{
    if (tmp == nullptr)
    {
	return;
    }

    traverse(command, tmp->LeftChild, begin,flagType);
    traverse(command, tmp->RightChild, begin,flagType);

    if(tmp->Data->getPhone() == command.getPhone())
    {
	if(command.isOk(tmp->Data, flagType))
	{
	    tmp->Data->NextSelect = begin;
	    begin = tmp->Data;
	    return;
	}
    }
    return;
}



void AVLTree::print(AVLTreeNode *root , int level, int maxPrint)
{
    if(root == nullptr)
    {
	return;
    }
    maxPrint ++;
    printf(" (%d) ", getBalance(root));
    root->Data->print();
    level ++;
    if(maxPrint < MAX_PRINT_TREE && root -> LeftChild)
    {
	for (int i = 0; i < level ; ++i)
	{
	    printf("%c",' ');
	}
	printf("L: ");
	print(root->LeftChild, ++level, maxPrint);
    }
    if(maxPrint < MAX_PRINT_TREE && root->RightChild)
    {
	for (int i = 0; i < level - 1; ++i)
	{
	    printf("%c", ' ');
	}
	printf("R: ");
	print(root->RightChild, ++level, maxPrint);
    }
}

void AVLTree::deleteAVLTree(AVLTreeNode *tmp)
{
    if(tmp != nullptr)
    {
	deleteAVLTree(tmp -> LeftChild);
	deleteAVLTree(tmp -> RightChild);
    }
    if(tmp == Root)
    {
	Root = nullptr;
    }
    delete tmp;
}

AVLTreeNode* AVLTree::rotateLeft(AVLTreeNode *center)
{
    AVLTreeNode* tmp = center->RightChild;
    center->RightChild = tmp->LeftChild;
    tmp->LeftChild = center;

    fixHeight(center);
    fixHeight(tmp);

    return tmp;
}

AVLTreeNode* AVLTree::rotateRight(AVLTreeNode *center)
{
    AVLTreeNode* tmp = center->LeftChild;
    center->LeftChild = tmp->RightChild;
    tmp->RightChild = center;

    fixHeight(center);
    fixHeight(tmp);

    return tmp;
}

AVLTreeNode *AVLTree::minValue(AVLTreeNode *root)
{
    AVLTreeNode *ptr = root;
    while (ptr->LeftChild != nullptr)
    {
	ptr = ptr->LeftChild;
    }

    return ptr;
}


AVLTreeNode *AVLTree::maxValue(AVLTreeNode *root)
{
    AVLTreeNode *ptr = root;
    while (ptr->RightChild != nullptr)
    {
	ptr = ptr->RightChild;
    }

    return ptr;
}

AVLTreeNode * AVLTree::balance(AVLTreeNode * tmp)
{
    fixHeight(tmp);

    if(getBalance(tmp) == 2)
    {
	if(getBalance(tmp->RightChild) < 0)
	{
	    tmp->RightChild = rotateRight(tmp->RightChild);
	}
	return rotateLeft(tmp);
    }
    if(getBalance(tmp) == -2)
    {
	if(getBalance(tmp->LeftChild) > 0)
	{
	    tmp->LeftChild = rotateLeft(tmp->LeftChild);
	}
	return rotateRight(tmp);
    }
    return tmp;
}

void AVLTree::insert(ListNode * data)
{
    AVLTreeNode * tmp = new AVLTreeNode;
    tmp->Data = data;

    Root = binaryInsertion(Root, tmp);
}

AVLTreeNode * AVLTree::binaryInsertion(AVLTreeNode *root, AVLTreeNode *source)
{
    if(root == nullptr)
    {
	return source;
    }
    if(*root > *(source->Data))
    {
	root->LeftChild = binaryInsertion(root->LeftChild, source);
    }
    else
    {
	root->RightChild = binaryInsertion(root->RightChild, source);
    }
    return balance(root);
}



void AVLTree::deleteValue(ListNode * referene)
{
    Root = binaryDeletion(Root, referene);
}

AVLTreeNode * AVLTree::deleteMinValue(AVLTreeNode *min)
{
    if(min->LeftChild == nullptr)
    {
	return min->RightChild;
    }
    min->LeftChild = deleteMinValue(min->LeftChild);

    return balance(min);
}

AVLTreeNode * AVLTree::binaryDeletion(AVLTreeNode *root, ListNode *reference)
{
    if(root == nullptr)
    {
	return nullptr;
    }

    if(*root > *reference)
    {
	root->LeftChild = binaryDeletion(root->LeftChild, reference);

    }
    else
    {
	if(*root < *reference)
	{
	    root->RightChild = binaryDeletion(root->RightChild, reference);
	}
	else if( *root == *reference)
	{
	    AVLTreeNode * left = root->LeftChild;
	    AVLTreeNode * right = root->RightChild;

	    delete root;

	    if(right == nullptr)
	    {
		return left;
	    }
	    AVLTreeNode * min = minValue(right);
	    min->RightChild = deleteMinValue(right);
	    min->LeftChild = left;

	    return balance(min);
	}
    }
    return balance(root);
}
