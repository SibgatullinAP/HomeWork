#ifndef TREE_H
#define TREE_H

#include "tree_node.h"

template <class T>
class tree
{
private:
  tree_node<T> * root = nullptr;
public:
  tree () = default;
  ~tree ()
  {
    destroy (root);
  }

  void destroy (tree_node<T> *root_)
  {
    if (root_ != nullptr)
      {
        destroy (root_->left);
        destroy (root_->right);
      }
    if (root_ == root)
      root = nullptr;

    delete root_;
  }


  tree_node<T> * add (tree_node<T> *tmp, tree_node<T> *root_)
  {
    if (root_ == nullptr)
      {
        root_ = tmp;
        return root_;
      }
    else
      {
        if ((*tmp) < (*root))
          {
            tmp = add (tmp, root_->left);
            if (tmp != nullptr)
              root_->left = tmp;
            else
              return nullptr;
          }
        else
          {
            tmp = add (tmp, root_->right);
            if (tmp != nullptr)
              root_->right = tmp;
            else
              return nullptr;
          }
      }
    return root_;
  }

  int read (const char * filename)
  {
    FILE *file_in = fopen (filename, "r");
    if (file_in == nullptr)
      return ERROR_CANNOT_OPEN_FILE;

    destroy (root);

    tree_node<T> * tmp = nullptr;
    tmp = new tree_node<T>;
    int ret = tmp->read (file_in);
    if (ret < 0)
      {
        delete tmp;
        fclose (file_in);
        return ret;
      }

    root = tmp;

    while (true)
      {
        tmp = new tree_node<T>;
        int ret = tmp->read (file_in);
        if (ret != SUCCESS)
          {
            delete tmp;
            fclose (file_in);
            return ret;
          }

        if (add (tmp, root) == nullptr)
          {
            delete tmp;
            fclose (file_in);
            return ERROR_INTERNAL_ERROR_TREE;
          }

        tmp = nullptr;
      }

    fclose (file_in);
    return SUCCESS;
  }

  void print_recursive (tree_node<T> *root , int level, int max_print_counter, int max_print ) const
  {
    if(root == nullptr)
      return;

    max_print_counter ++;
    root->print();
    level ++;

    if(max_print_counter < max_print && root -> left)
      {
        for (int i = 0; i < level ; ++i)
          printf ("%c",' ');

        printf ("L: ");
        print_recursive (root->left, ++level, max_print_counter, max_print);
      }
    if(max_print_counter < max_print && root->right)
      {
        for (int i = 0; i < level - 1; ++i)
          printf ("%c", ' ');

        printf ("R: ");
        print_recursive (root->right, ++level, max_print_counter, max_print);
      }
  }

  void print (int r) const
  {
    print_recursive (root, 0, 0, r);
  }

  tree_node<T> * get_root ()
  {
    return root;
  }

  int task_1 () const
  {
    return task_1_recursive (root);
  }

  int task_1_recursive (tree_node<T> * root_) const
  {
    int count = 0;

    if (root_->left)
      count += task_1_recursive (root_->left);

    if (root_->right)
      count += task_1_recursive (root_->right);

    if (root_->left == nullptr && root_->right == nullptr)
      count += root_->get_length ();

    return count;
  }

  int task_2 ()
  {
    return 1;
  }
  int task_3 ()
  {
    return 1;
  }
  int task_4 ()
  {
    return 1;
  }

  int task_5 () const
  {
    return task_5_recursive (root);
  }

  int task_5_recursive (tree_node<T> *root_) const
  {
    int count = 0;

    if ((root_->left && !(root_->right))
        || (root_->right && !(root_->left)))
      count += root_->get_length ();

    if (root_->left)
      count += task_5_recursive (root_->left);

    if (root_->right)
      count += task_5_recursive (root_->right);

    return count;
  }
};

#endif // TREE_H
