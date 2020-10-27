#include "tree.h"

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

void Tree::print(TreeNode *root , int level, int maxPrint)
{
        maxPrint ++;
	printf(" (%d) ", getBalance(root));
	root -> print();
	level ++;
	if(maxPrint < MAX_PRINT_TREE && root -> LeftChild)
	{
	    for (int i = 0; i < level ; ++i)
	    {
		printf("%c",' ');
	    }
	    printf("L: ");
	    print(root -> LeftChild, ++level, maxPrint);
	}
	if(maxPrint < MAX_PRINT_TREE && root -> RightChild)
	{
	    for (int i = 0; i < level - 1; ++i)
	    {
		printf("%c", ' ');
	    }
	    printf("R: ");
	    print(root -> RightChild, ++level, maxPrint);
	}
}

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

TreeNode* Tree::rotateLeft(TreeNode *center)
{
    TreeNode* tmp = center->RightChild;
    center->RightChild = tmp->LeftChild;
    tmp->LeftChild = center;

    fixHeight(tmp);
    fixHeight(center);

    return tmp;
}

TreeNode* Tree::rotateRight(TreeNode *center)
{
    TreeNode* tmp = center->LeftChild;
    center->LeftChild = tmp->RightChild;
    tmp->RightChild = center;

    fixHeight(tmp);
    fixHeight(center);

    return tmp;
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

TreeNode * Tree::balance(TreeNode * tmp)
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

void Tree::insert(char *Name, int Phone, int Group)
{
    TreeNode *tmp = new TreeNode;

    tmp->setName(Name);
    tmp->setPhone(Phone);
    tmp->setGroup(Group);

    Root = binaryInsertion(Root, tmp);
}

TreeNode * Tree::binaryInsertion(TreeNode *root, TreeNode *source)
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



void Tree::deleteValue(char *Name, int Phone, int Group)
{
    Record * reference = nullptr;
    reference = new Record;
    reference->setName(Name);
    reference->setPhone(Phone);
    reference->setGroup(Group);

    //TreeNode *node = binaryDeletion(Root, reference);
    Root = binaryDeletion(Root, reference);

    delete reference;
}

TreeNode * Tree::deleteMinValue(TreeNode *min)
{
    if(min->LeftChild == nullptr)
    {
	return min->RightChild;
    }
    min->LeftChild = deleteMinValue(min->LeftChild);

    return balance(min);
}

TreeNode * Tree::binaryDeletion(TreeNode *root, Record *reference)
{
    printf("ffff\n"); reference -> print();
    if(root == nullptr)
    {
	return nullptr;
    }

    if(*reference < *root)
    {
	printf("<");
	root->LeftChild = binaryDeletion(root->LeftChild, reference);

    }
    else
    {
	if(*reference > *root)
	{
	    printf(">");
	    root->RightChild = binaryDeletion(root->RightChild, reference);
	}
	else
	{
	    printf("==");
	    TreeNode * left = root->LeftChild;
	    TreeNode * right = root->RightChild;
	    delete root;
	    printf("dddddd\n");

	    if(right == nullptr)
	    {
		return left;
	    }
	    TreeNode * min = minValue(right);
	    min->RightChild = deleteMinValue(right);
	    min->LeftChild = left;

	    return balance(min);
	}
    }
    return balance(root);
}
