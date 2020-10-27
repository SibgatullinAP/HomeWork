void Tree::balanceDelete(TreeNode *tmp)
{
    if(tmp == nullptr)
    {
    	return;
    }

    if(tmp == Root) 
    {
		root = nullptr;
		return;
    }

    if(tmp->Colod == RED || tmp->LeftChild->Color == RED || tmp->RightChild-> == RED) 
    {
		Node *child = tmp->LeftChild != nullptr ? tmp->LeftChild : tmp->RightChild;

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
		Node *brother = nullptr;
		Node *parent = nullptr;
		Node *ptr = tmp;
		ptr->Color = DOUBLE_BLACK;
		while(ptr != Root && ptr->Color == DOUBLE_BLACK) 
		{
		    parent = ptr->Parent;
		    if(ptr == parent->LeftChild)
		    {
				brother = parent->RightChild;
				if(getColor(brother) == RED) 
				{
				    brother->Color = BLACK;
				    parent->Color = RED;
				    rotateLeft(parent);
				} 
				else 
				{
				    if(brother->LeftChild->Color == BLACK && brother->RightChild->Color == BLACK) 
				    {
						brother->Color = RED;
						if(parent->Color == RED)
						{
							Parent->Color = BLACK;
						}
						else
						{
							Parent->Color = DOUBLE_BLACK;
						}
						ptr = Parent;
				    } 
				    else
				    {
						if(brother->RightChild->Color == BLACK) 
						{
						    brother->LeftChild->Color = BLACK;
						    brother->Color = RED;
						    rotateRight(brother);
						    brother = parent->RightChild;
						}
						brother->Color = parent->Color;
						parent->Color = BLACK;
						brother->RightChild->Color = BLACK;
						rotateLeft(parent);
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
				    rotateRight(parent);
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
						    rotateLeft(brother);
						    brother = parent->LeftChild;
						}
						brother->Color = parent->Color;
						parent->Color = BLACK;
						brother->LeftChild->Color = BLACK;
						rotateRight(parent);
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