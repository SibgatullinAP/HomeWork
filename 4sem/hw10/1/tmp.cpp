student* Tree::insert(student *value, TreeNode *current, TreeNode **p_left, TreeNode **p_right)
{
    if(Root == nullptr)
    {
        Root = new TreeNode(2 * Order);
    }
    if(current == nullptr)
    {
        current = Root;
    }

    int tmp = current -> findIsert(value);
    if(current->Children[0])
    {
        student * res = insert(value, cuzrrent -> Children[tmp], p_left, p_right);
        if(res =! nullptr)
        {
            res = insertTreeNode(res, current, p_left, p_right);
        }
        return res;
    }
    else
    {
        if(current -> Size < 2 * Order)
        {
          for(int i = current -> Size - 1; i >= tmp; i--)
          {
              current -> Values[i + 1] = current -> Values[i];
          }
          current -> Values[tmp] = value; 
          current -> Size++;
          return 0;
        }
        else
        {
            TreeNode * right = new TreeNode(2 * Order);
            student * median = 0;
            if(tmp < Order)
            {
                median = current -> Values[Order - 1];
            }
            else if(tmp == Order)
            {
                median = value;
            }
            else
            {
                median = current -> Values[Order];
            }
            if(tmp <= Order)
            {
                for(int i = 0; i < Order; i++)
                {
                    right -> Values[i] = current -> Values[i + Order];
                    current -> Values[i + Order] = 0;
                }
            }
            else
            {
                int i = 0;
                for(i = 0; i < tmp - Order - 1; i++)
                {
                    right -> Values[i] = current -> Values[i + Order + 1];
                    current -> Values[i + Order + 1] = 0;
                }
                right -> Values[i] = value; i++;
                for(; i < Order; i++)
                {
                    right -> Values[i] = current -> Values[i + Order];
                    current -> Values[i + Order] = 0;
                }
            }

            if(tmp < Order)
            {
                for(int i = Order - 1; i >= tmp; i--)
                {
                    current -> Values[i + 1] = current -> Values[i];
                }
                current -> Values[tmp] = value; current -> Size++;
            }
            for(int i = Order; i < 2 * Order; i++)
            {
                current -> Values[i] = nullptr;
                right -> Values[i] = nullptr;
            }
            right -> Size = Order;
            current -> Size = Order;
            *p_right = right;
            *p_left = current;
            return median;
        }
    }
}