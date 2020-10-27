#include "AVLTree.h"

int AVLTree::read(FILE *inFile)
{
    deleteAVLTree(Root);

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
	delete tmp->Data;
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

void AVLTree::insert(char *Name, int Phone, int Group)
{
    Record * data = new Record;
    data->setName(Name);
    data->setPhone(Phone);
    data->setGroup(Group);

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
    if(*source < *root)
    {
	root->LeftChild = binaryInsertion(root->LeftChild, source);
    }
    else
    {
	root->RightChild = binaryInsertion(root->RightChild, source);
    }
    return balance(root);
}



void AVLTree::deleteValue(char *Name, int Phone, int Group)
{
    Record * reference = nullptr;
    reference = new Record;
    reference->setName(Name);
    reference->setPhone(Phone);
    reference->setGroup(Group);

    AVLTreeNode * tmp = new AVLTreeNode;
    tmp->Data = reference;


    Root = binaryDeletion(Root, tmp);

    delete tmp->Data;
    delete tmp;
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

AVLTreeNode * AVLTree::binaryDeletion(AVLTreeNode *root, AVLTreeNode *reference)
{
    if(root == nullptr)
    {
	return nullptr;
    }

    if(*reference < *root)
    {
	root->LeftChild = binaryDeletion(root->LeftChild, reference);

    }
    else
    {
	if(*reference > *root)
	{
	    root->RightChild = binaryDeletion(root->RightChild, reference);
	}
	else if( *reference == *root)
	{
	    AVLTreeNode * left = root->LeftChild;
	    AVLTreeNode * right = root->RightChild;

	    delete root->Data;
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
