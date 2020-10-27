#include "tree.h"
#include "tree_node.h"
#include "list_node.h"
#include "errors.h"

#define MAX_PRINT_LEVEL 4

tree::~tree(){
	destroy();
	cmp = nullptr;
}

list_node * tree::search(const command &x, data_type cond, int ident) const {
	if(!cmp) return nullptr;

	list_node *prev, *start = nullptr;
	tree_node *curr = root;
	int ret;

	while(curr){
		ret = cmp(x, *curr->data);
		if(!ret) break;

		curr = (ret < 0) ? curr->left : curr->right;
	}

	if(ident){
		while(curr){
			if(x.check_single_cond(curr->data, cond)){
				if(start) prev = prev->next_search = curr->data;
				else prev = start = curr->data;
			}

			curr = curr->next;
		}
	}
	else{
		while(curr){
			if(!x.check_single_cond(curr->data, cond)){
				if(start) prev = prev->next_search = curr->data;
				else prev = start = curr->data;
			}

			curr = curr->next;
		}
	}

	if(start) prev->next_search = nullptr;

	return start;
}

int tree::insert(list_node *x){
	if(!x || !cmp) return ERR_NULL_ARG;

	tree_node *new_node = new tree_node;

	if(!new_node) return ERR_MEMORY;
	new_node->data = x;

	if(!root){
		root = new_node;
		root->color = BLACK;

		return 0;
	}

	int res = recursInsert(root, new_node);
	if(res < 0){
		delete new_node;
		return res;
	}

	if(!res) root->color = BLACK;

	return 0;
}

int tree::recursInsert(tree_node *curr, tree_node *&x){
	int rec_res, cmp_res = cmp(*x->data, *curr->data);
	tree_node *c_tmp;

	if(!cmp_res){
		if(*curr->data == *x->data) return ERR_OVERLAP;

		while(curr->next){
			curr = curr->next;
			if(*curr->data == *x->data) return ERR_OVERLAP;
		}

		curr->next = x;

		return 1;
	}

	if(cmp_res < 0){
		c_tmp = curr->left;

		if(!c_tmp){
			curr->left = x;
			return (curr->color == BLACK);
		}

		rec_res = recursInsert(c_tmp, x);
		if(rec_res) return rec_res;

		if(curr->color == RED) return 0;
		if(c_tmp == x) return 1;

		if(curr->right && curr->right->color == RED){ // 1
			c_tmp->color = curr->right->color = BLACK;
			curr->color = RED;
			x = curr;

			return 0;
		}

		if(c_tmp->right == x){ // 2
			c_tmp->right = x->left;
			x->left = c_tmp;
			c_tmp = curr->left = x;
		}

		swapData(curr, c_tmp); // 3

		curr->left = c_tmp->left;
		c_tmp->left = c_tmp->right;
		c_tmp->right = curr->right;
		curr->right = c_tmp;
	}
	else{
		c_tmp = curr->right;

		if(!c_tmp){
			curr->right = x;
			return (curr->color == BLACK);
		}

		rec_res = recursInsert(c_tmp, x);
		if(rec_res) return rec_res;

		if(curr->color == RED) return 0;
		if(c_tmp == x) return 1;

		if(curr->left && curr->left->color == RED){ // 1
			c_tmp->color = curr->left->color = BLACK;
			curr->color = RED;
			x = curr;

			return 0;
		}

		if(c_tmp->left == x){ // 2
			c_tmp->left = x->right;
			x->right = c_tmp;
			c_tmp = curr->right = x;
		}

		swapData(curr, c_tmp); // 3
		curr->right = c_tmp->right;
		c_tmp->right = c_tmp->left;
		c_tmp->left = curr->left;
		curr->left = c_tmp;
	}

	return 1;
}

int tree::remove(const list_node *x){
	if(!x || !cmp) return ERR_NULL_ARG;
	if(!root) return ERR_NOT_FOUND;

	tree_node *tmp = nullptr;

	int res = recursRemove(root, x, tmp);
	if(res < 0) return res;

	if(tmp){
		delete root;
		root = nullptr;
	}

	return 0;
}

int tree::recursRemove(tree_node *curr, const list_node *x, tree_node *&prev){
	int rec_res, cmp_res;
	tree_node *c_tmp;

	cmp_res = prev ? 1 : cmp(*x, *curr->data);

	if(!cmp_res){
		if(*curr->data != *x){
			c_tmp = curr->next;

			while(c_tmp){
				if(*c_tmp->data == *x){
					curr->next = c_tmp->next;
					delete c_tmp;

					return 1;
				}

				curr = c_tmp;
				c_tmp = c_tmp->next;
			}

			return -1;
		}

		if(curr->next){
			c_tmp = curr->next;
			curr->data = c_tmp->data;
			curr->next = c_tmp->next;
			delete c_tmp;

			return 1;
		}

		prev = curr;

		if(!curr->left){
			if(curr->right){
				curr->data = curr->right->data;
				curr->next = curr->right->next;

				delete curr->right;
				prev = curr->right = nullptr;

				return 1;
			}

			return 0;
		}

		cmp_res = -1;

		// curr == x && !curr->next  (prev)
	}

	if(cmp_res < 0){
		if(!curr->left) return -1;

		rec_res = recursRemove(curr->left, x, prev);
		if(rec_res) return rec_res;

		if(prev){
			prev->data = curr->left->data;
			prev->next = curr->left->next;
			prev = nullptr;

			if(curr->left->color == RED){
				delete curr->left;
				curr->left = nullptr;

				return 1;
			}

			delete curr->left;
			curr->left = nullptr;
		}

		// curr->left is double black;

		c_tmp = curr->right;

		if(c_tmp->color == RED){ // 1
			swapData(curr, c_tmp);

			curr->right = c_tmp->right;
			c_tmp->right = c_tmp->left;
			c_tmp->left = curr->left;
			curr->left = c_tmp;

			curr = c_tmp;
			c_tmp = curr->right;
		}

		if(c_tmp->left && c_tmp->left->color == RED){ // 2
			c_tmp = c_tmp->left;

			swapData(curr, c_tmp);

			curr->right->left = c_tmp->right;
			c_tmp->right = c_tmp->left;
			c_tmp->left = curr->left;
			curr->left = c_tmp;
			c_tmp->color = BLACK;

			return 1;
		}

		if(c_tmp->right && c_tmp->right->color == RED){ // 3
			swapData(curr, c_tmp);

			curr->right = c_tmp->right;
			c_tmp->right = c_tmp->left;
			c_tmp->left = curr->left;
			curr->left = c_tmp;
			c_tmp->color = RED;
		}
		else c_tmp->color = RED; // 4

		if(curr->color == RED){
			curr->color = BLACK;
			return 1;
		}
	}
	else{
		if(!curr->right){
			if(!prev) return -1;
			if(!curr->left) return 0;

			prev->data = curr->data;
			prev->next = curr->next;
			curr->data = curr->left->data;
			curr->next = curr->left->next;

			delete curr->left;
			prev = curr->left = nullptr;

			return 1;
		}

		rec_res = recursRemove(curr->right, x, prev);
		if(rec_res) return rec_res;

		if(prev){
			prev->data = curr->right->data;
			prev->next = curr->right->next;
			prev = nullptr;

			if(curr->right->color == RED){
				delete curr->right;
				curr->right = nullptr;

				return 1;
			}

			delete curr->right;
			curr->right = nullptr;
		}

		// curr->right is double black;

		c_tmp = curr->left;

		if(c_tmp->color == RED){ // 1
			swapData(curr, c_tmp);

			curr->left = c_tmp->left;
			c_tmp->left = c_tmp->right;
			c_tmp->right = curr->right;
			curr->right = c_tmp;

			curr = c_tmp;
			c_tmp = curr->left;
		}

		if(c_tmp->right && c_tmp->right->color == RED){ // 2
			c_tmp = c_tmp->right;

			swapData(curr, c_tmp);

			curr->left->right = c_tmp->left;
			c_tmp->left = c_tmp->right;
			c_tmp->right = curr->right;
			curr->right = c_tmp;
			c_tmp->color = BLACK;

			return 1;
		}

		if(c_tmp->left && c_tmp->left->color == RED){ // 3
			swapData(curr, c_tmp);

			curr->left = c_tmp->left;
			c_tmp->left = c_tmp->right;
			c_tmp->right = curr->right;
			curr->right = c_tmp;
			c_tmp->color = RED;
		}
		else c_tmp->color = RED; // 4

		if(curr->color == RED){
			curr->color = BLACK;
			return 1;
		}
	}

	return 0;
}

void tree::destroy(){
	recursDestroy(root);
	root = nullptr;
}

void tree::recursDestroy(tree_node *root){
	if(!root) return;

	recursDestroy(root->left);
	recursDestroy(root->right);

	tree_node *curr = root;

	while(root){
		curr = root->next;
		delete root;
		root = curr;
	}
}

int tree::isCorrect() const {
	if(!root) return 1;
	if(!cmp || root->color != BLACK || !root->data) return 0;

	return (recursCorrect(root) >= 0);
}

int tree::recursCorrect(tree_node *curr) const {
	if(!curr) return 0;

	for(tree_node *tmp = curr->next; tmp; tmp = tmp->next){
		if(!tmp->data || tmp->left || tmp->right
			|| tmp->color == BLACK || cmp(*tmp->data, *curr->data)) return -1;
	}

	if(curr->color == RED){
		if((curr->left && curr->left->color == RED)
		   || (curr->right && curr->right->color == RED)){
			return -1;
		}
	}

	if(curr->left){
		if(!curr->left->data || cmp(*curr->left->data, *curr->data) >= 0) return -1;
	}
	if(curr->right){
		if(!curr->right->data || cmp(*curr->right->data, *curr->data) <= 0) return -1;
	}

	int l = recursCorrect(curr->left);
	int r = recursCorrect(curr->right);

	if(l < 0 || r < 0 || l != r) return -1;


	return (curr->color == BLACK)? l + 1 : l;
}

void tree::print(FILE *fp) const {
	int arr[MAX_PRINT_LEVEL] = {0};

	if(root) recursPrint(root, arr, fp, 0);
	else fprintf(fp, "tree is empty\n");
}

void tree::recursPrint(tree_node *root, int *arr, FILE *fp, int lvl){
	if(fp == stdout){
		if(lvl == MAX_PRINT_LEVEL) return;
		for(int i = 0; i < lvl - 1; i++){
			if(arr[i]) printf("    ");
			else printf("│   ");
		}

		if(lvl){
			if(arr[lvl - 1]) printf("└── ");
			else printf("├── ");
		}
		if(root->color == RED) printf("\033[41m \033[0m");
		else printf("\033[47m \033[0m");
		root->data->print();

		for(tree_node *tmp = root->next; tmp; tmp = tmp->next){
			for(int i = 0; i < lvl - 1; i++){
				if(arr[i]) printf("    ");
				else printf("│   ");
			}

			if(lvl){
				if(arr[lvl - 1]) printf("    ");
				else printf("│   ");
			}
			printf("│");
			tmp->data->print();
		}

		if(root->left){
			if(!root->right) arr[lvl] = 1;
			else arr[lvl] = 0;
			recursPrint(root->left, arr, fp, lvl + 1);
		}

		if(root->right){
			arr[lvl] = 1;
			recursPrint(root->right, arr, fp, lvl + 1);
		}
	}
	else{
		root->data->print(fp);
		if(root->right) recursPrint(root->right, arr, fp, lvl + 1);
		if(root->left) recursPrint(root->left, arr, fp, lvl + 1);
	}
}

int tree::blackDepth() const {
	int depth = 0;

	for(tree_node *curr = root; curr; curr = curr->left){
		if(curr->color == BLACK) depth++;
	}

	return depth;
}

void tree::swapData(tree_node *n1, tree_node *n2){
	list_node *data_tmp = n1->data;
	tree_node *next_tmp = n1->next;

	n1->data = n2->data;
	n1->next = n2->next;

	n2->data = data_tmp;
	n2->next = next_tmp;
}
