#ifndef TREE_H
#define TREE_H 

#include "treeNode.h"
#include <math.h>

class TreeNode;
class Tree
{
	private:
            TreeNode *Root = nullptr;
            TreeNode *Current = nullptr;
            enum MENU_PROPERTIES
            {
                MENU = 'm',
                EXIT = 'e',
                PRINT_TREE = 'p',
		PRINT_SUBTREE = 's',
                PRINT_CURRENT = 'c',
                WORK_WITH_QUEUE = 'w',
		DELETE_TREE = 'x',
                DELETE_BROTHER_SUBTREE = 'y',
		DELETE_CHILD_SUBTREE = 'z',
                GO_TO_BROTHER = 'b',
                GO_DOWN = 'v',
                GO_ROOT = 'r',
                ADD_ROOT = 'h',
                ADD_BROTHER = 'a',
                ADD_CHILD = 'l',
            };
	public:
            Tree() = default;
            ~Tree()
            {
                delete_tree(Root);
            }

            void delete_tree(TreeNode *root);
	    void delete_child_tree();
	    void delete_brother_tree();
            int read(FILE *fp,  int size_tree, int size_queue);
            void print(TreeNode *Root, int max_print, FILE* out);

            void add(TreeNode *tmp, TreeNode *Root);
            TreeNode* get_root() const;

            TreeNode* set_left();
            TreeNode* set_right();
            TreeNode* set_root();

            TreeNode* del_left();
            TreeNode* del_right();
            TreeNode* del_root();
            void addRoot();
            void addBrother();
            void addChild();

            TreeNode* del_sub_level();
            TreeNode* del_sub_tree();
            void menu();
            void print_menu();
};

#endif
