#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include "redblacktree_node.h"


template <class T>
class RBTree
{
private:
	RBTree_node <T> *root = nullptr;
	int M = 1000;
	int print_tree_(FILE *fp, RBTree_node <T> *run, int deep = 0)
	{
		if (deep == MAX_DEEP)
			return 0;
		if (!run)
			return 0;
		print_tree_(fp, run->right, deep + 1);
		for (int i = 0; i < deep-1; fprintf(fp,"    "), i++);
		if (deep)
			fprintf(fp," |--");
		RBTree_node <T> *nuxt = run;
		for (;;)
		{
			print_record(nuxt, fp);
			fprintf(fp," ");
			if (!nuxt->next)
				break;
			nuxt->next->color = nuxt->color;
			nuxt = nuxt->next;
		}
		fprintf(fp,"\n");
		print_tree_(fp, run->left, deep + 1);
		return 0;
	}

	int insert_ (list_node *run, ratio (*comp)(list_node *, RBTree_node <T> *), int (*total_comp)(list_node *, RBTree_node <T> *))
	{
		if (!root)
		{
			//root->print_location(); printf("Nu privet\n\n");
			root = new RBTree_node <T>;
			root->init(run, M);
			root->color = BLACK;
			//root->print_location(); printf("Nu privetik\n\n");
			return MAKE_ROOT;
		}
		int res;
		RBTree_node <T> *Rrun;
		//printf("run = "); run->print_record(); printf("\n");
		Rrun = add_node(run, comp, total_comp, res);
		//printf("Rrun = "); Rrun->print_record(); printf("\n");
		if (res == HASH_EQUALITY)
			return HASH_EQUALITY;
		if (res == EQUALITY)
			return EQUALITY;
		balance(Rrun);
		return WORK_DONE;
	}
	friend class database;
	friend class megabase;
	void making_list_(RBTree_node<T> *run, list_node *nhead) //nhead != nullptr, else it will fall
	{
		if (!run)
			return;
		nhead = run->create_list(nhead);
		making_list_(run->left, nhead);
		making_list_(run->right, nhead);
	}
public:
	RBTree() = default;
	RBTree(int m) {M = m;}
	~RBTree() {delete_all();}

	void delete_all()
	{
		delete_tree(root);
		root = nullptr;
	}

	int print_record (RBTree_node <T> *buf, FILE *fp = stdout)
	{
		(buf->color == BLACK ? fprintf(fp, "\x1b[30;47m") : fprintf(fp, "\x1b[37;41m"));
		buf->get_key()->print_record(fp);
		fprintf(fp, "\x1b[0m");
		return 1;
	}


	int insert(list_node *x, ratio (*comp)(list_node * , RBTree_node <T> *), int (*total_comp)(list_node *, RBTree_node <T> *))
	{
		if (insert_(x, comp, total_comp) == EQUALITY)
			return EQUALITY;
		return WORK_DONE;
	}
	void delete_tree(RBTree_node <T> *run)
	{
		if (!run)
			return;
		delete_tree(run->left);
		delete_tree(run->right);
		RBTree_node <T> *nuxt = run;
		while ((run = nuxt->next))
		{
			delete nuxt;
			nuxt = run;
		}
		delete nuxt;
	}
	int print_tree(FILE *fp = stdout)
	{
		fprintf(fp, "\n\tTree is:\n");
		print_tree_(fp, root);
		return 1;

	}
	int balance (RBTree_node <T> *run)
	{
		RBTree_node <T> *dad, *granny, *uncle;
		//printf("\n\n\tStarting balance \n");
		while (run) //в начале цикла run должен быть RED
		{
		/*
			//тест
			print_tree();
			printf("run:\n");
			run->print_record();
			printf("\n");
			//тест
		*/

			dad = run->parent;
			if (!dad)
			{
				run->color = BLACK;
				root = run;
				return WORK_DONE;
			}
			granny = dad->parent;
			if (dad->color == BLACK)
				return WORK_DONE;
			else	//у красного отца вроде бы всегда есть дед и он вроде бы всегда чёрный => далее всегда есть дед, батя и сын
			{
				(granny->left == dad ? uncle = granny->right : uncle = granny->left);
				if (!uncle || uncle->color == BLACK)
				{
					/*
					//тесты
					printf("\n\n\tOPERATION BLACK UNCLE\nbefore\n");
					print_tree();
					printf("run: ");
					run->print_record();
					printf("\n");
					printf("dad: ");
					dad->print_record();
					printf("\n");
					printf("granny: ");
					granny->print_record();
					printf("\n");
					//тесты
					*/

					RBTree_node <T> *pragranny = granny->parent;
					if (dad == granny->left) // сценарий 1
					{
						if (run == dad->right)			//сценарий 1.1 LR
						{

							granny->left = run;
							run->parent = granny;

							if ((dad->right = run->left))
								run->left->parent = dad;

							run->left = dad;
							dad->parent = run;
														//повернул LR в LL
							dad = granny->left;
							run = dad->left;
														//сценарий 1.1 перерос в 1.2
						}
														//сценарий 1.2 LL
						/*
						printf("\tсценарий 1.2 LL\n");
						print_tree();
						printf("run: ");
						run->print_record();
						printf("\n");
						printf("dad: ");
						dad->print_record();
						printf("\n");
						printf("granny: ");
						granny->print_record();
						printf("\n");
						*/
						if ((granny->left = dad->right))
							granny->left->parent = granny;

						dad->right = granny;
						granny->parent = dad;

						if (pragranny)
							(pragranny->left == granny ? pragranny->left = dad : pragranny->right = dad);
						else
							root = dad;

						dad->parent = pragranny;
						granny->color = RED;
						dad->color = BLACK;
						break;
					}
					else
					{
						if (run == dad->left)			//сценарий 2.1 RL
						{

							granny->right = run;
							run->parent = granny;

							if ((dad->left = run->right))
								run->right->parent = dad;

							run->right = dad;
							dad->parent = run;
														//повернул RL в RR
							dad = granny->right;
							run = dad->right;
														//сценарий 2.1 перерос в 2.2
						}
														//сценарий 2.2 RR

						if ((granny->right = dad->left))
							granny->right->parent = granny;

						dad->left = granny;
						granny->parent = dad;

						if (pragranny)
							(pragranny->left == granny ? pragranny->left = dad : pragranny->right = dad);
						else
							root = dad;
						dad->parent = pragranny;

						granny->color = RED;
						dad->color = BLACK;
						break;

					}
					//тесты
					//printf("\n\tOPERATION COMPLITE\nafter\n");
					//print_tree();
					//if (!scanf("\n"))
						//printf("WOW\n");
					//тесты
					//ПОВОРОТ ДЕДА В ДЯДЮ, БАТЮ В ДЕДА
				}
				else
				{
					dad->color = uncle->color = BLACK;
					granny->color = RED;
					run = granny;
					continue;
				}
			}
		}
		return WORK_DONE;
	}
	RBTree_node <T> * add_node (list_node *nuxt,  ratio (*comp)(list_node *, RBTree_node <T> *), int (*total_comp)(list_node *, RBTree_node <T> *), int &ret)
	{
		RBTree_node <T> *run = root, *dad = root;
		//printf("run = "); run->print_record(); printf("\n");
		//printf("nuxt = "); nuxt->print_record(); printf("\n");
		ratio res = LESS;
		int rus;
		while (run)
		{
			res = (*comp)(nuxt, run);
			/*
			if (nuxt->value == 16)
				printf("nuxt = %d, run = %d, res = %d\n", nuxt->value, run->value, res);
				*/
			switch(res)
			{
			case LESS:
				dad = run;
				run = run->left;
				break;
			case MORE:
				dad = run;
				run = run->right;
				break;
			case EQUAL:
				if (run->check() == LISTNODE)
				{
					rus = (*total_comp)(nuxt, run);
					if (rus == EQUALITY)
					{
						ret = EQUALITY;
						return nullptr;
					}
					while (run->next)
					{
						run = run->next;
						rus = (*total_comp)(nuxt, run);
						if (rus == EQUALITY)
						{
							ret = EQUALITY;
							return nullptr;
						}
					}
					run->next = new RBTree_node<T>;
					run->next->init(nuxt, M);
					run->next->prev = run;
					ret = HASH_EQUALITY;
					return nullptr;
				}
				else
				{
					 ret = run->init(nuxt, M);
					 return run;
				}

			}
		}
		RBTree_node <T> *buxt;
		buxt = new RBTree_node <T>;
		buxt->init(nuxt, M);
		(res == LESS ? dad->left = buxt : dad->right = buxt);
		buxt->parent = dad;
		if (dad->color == BLACK)
		{
			ret = BLACK;
			return buxt;
		}
		ret = WORK_DONE;
		return buxt;
	}
	int check_RB(RBTree_node <T> *run)
	{
		if (!run)
			return 1;
		int L, R;
		if (!(L = check_RB(run->left)))
			return 0;
		if (!(R = check_RB(run->right)))
			return 0;

		if (L == R)
		{
			if (run->color == BLACK)
				L++;
			return L;
		}
		return 0;
	}
	int check_order(RBTree_node <T> *run, ratio (*comp)(list_node *, RBTree_node <T>*))
	{
		if (!run)
			return 1;
		if (run->left)
			if (!((*comp)(run->left->get_key(), run) == LESS))
				return 0;
		if (run->right)
			if (!((*comp)(run->right->get_key(), run) == MORE))
				return 0;
		if (!(check_order(run->left, comp) && check_order(run->right, comp)))
			return 0;
		return 1;
	}
	RBTree_node <T> * get_root () {return root;}
	list_node *search_eq(list_node *x, ratio (*comp)(list_node *, RBTree_node<T> *), list_node *nhead = nullptr)
	{
		//printf("TUT 4\n");
		RBTree_node <T> *run = root;
		int res;
		while (run)
		{
			res = comp(x, run);
			switch(res)
			{
			case LESS:
				run = run->left;
				break;
			case MORE:
				run = run->right;
				break;
			case EQUAL:
			{
				return run->create_list(nhead);
				/*
				if (run->check() == LISTNODE)
				{
					nrun = nhead = run->get_list();
					while ((run = run->next))
					{
						nrun->put_nnext(run->get_list());
						nrun = run->get_list();
					}
					return nhead;
				}
				else
				{
					return run->get_list();
				}
				*/
			}
			}
		}
		return nhead; //=nullptr
	}

	list_node *search_lt (list_node *x, ratio (*comp)(list_node *, RBTree_node<T> *), list_node *nhead = nullptr)
	{
		RBTree_node <T> *run = root;
		int res;
		while (run)
		{
			//printf("\nTuta\n"); printf("x = "); x->print_record(); printf("\n run = "); run->print_record(); printf("\n");
			res = comp(x, run);
			switch(res)
			{
			case LESS:
				//printf("MORE\n\n");
				run = run->left;
				break;
			case MORE:
				//printf("LESS\n\n");
				nhead = run->create_list(nhead);
				if (run->left)
					nhead = making_list(run->left, nhead);
				run = run->right;
				break;
			case EQUAL:
			{
				//printf("EQUAL\n\n");
				run = run->left;
				break;
			}
			}
		}
		return nhead; //=nullptr
	}

	list_node *search_le (list_node *x, ratio (*comp)(list_node *, RBTree_node<T> *), list_node *nhead = nullptr)
	{
		RBTree_node <T> *run = root;
		int res;
		while (run)
		{
			//printf("\nTuta\n"); printf("x = "); x->print_record(); printf("\n run = "); run->print_record(); printf("\n");
			res = comp(x, run);
			switch(res)
			{
			case LESS:
				//printf("MORE\n\n");
				run = run->left;
				break;
			case MORE:
				//printf("LESS\n\n");
				nhead = run->create_list(nhead);
				if (run->left)
					nhead = making_list(run->left, nhead);
				run = run->right;
				break;
			case EQUAL:
			{
				//printf("EQUAL\n\n");
				nhead = run->create_list(nhead);
				if (run->left)
					nhead = making_list(run->left, nhead);
				run = run->right;
				return nhead;
			}
			}
		}
		return nhead; //=nullptr
	}


	list_node *search_gt (list_node *x, ratio (*comp)(list_node *, RBTree_node<T> *), list_node *nhead = nullptr)
	{
		RBTree_node <T> *run = root;
		int res;
		while (run)
		{
			//printf("\nTuta\n"); printf("x = "); x->print_record(); printf("\n run = "); run->print_record(); printf("\n");
			res = comp(x, run);
			switch(res)
			{
			case LESS:
				//printf("MORE\n\n");
				nhead = run->create_list(nhead);
				if (run->right)
					nhead = making_list(run->right, nhead);
				run = run->left;
				break;
			case MORE:
				//printf("LESS\n\n");
				run = run->right;
				break;
			case EQUAL:
			{
				//printf("EQUAL\n\n");
				run = run->right;
				break;
			}
			}
		}
		return nhead; //=nullptr
	}


	list_node *search_ge (list_node *x, ratio (*comp)(list_node *, RBTree_node<T> *), list_node *nhead = nullptr)
	{
		RBTree_node <T> *run = root;
		int res;
		//printf("x = "); x->print_record(); printf("\n");
		//printf("run = "); run->print_record(); printf("\n");
		while (run)
		{
			//printf("\nTuta\n"); printf("x = "); x->print_record(); printf("\n run = "); run->print_record(); printf("\n");
			res = comp(x, run);
			switch(res)
			{
			case LESS:
				//printf("LESS\n\n");
				nhead = run->create_list(nhead);
				if (run->right)
					nhead = making_list(run->right, nhead);
				run = run->left;
				break;
			case MORE:
				//printf("MORE\n\n");
				run = run->right;
				break;
			case EQUAL:
			{
				//printf("EQUAL\n\n");
				nhead = run->create_list(nhead);
				if (run->right)
					nhead = making_list(run->right, nhead);
				run = run->left;
				return nhead;
			}
			}
		}
		return nhead; //=nullptr
	}


	list_node *making_list (RBTree_node <T> *run, list_node *nhead = nullptr)
	{
		if (!run) return nhead;
		nhead = run->create_list(nhead);
		if (!nhead)
		{
			list_node * buc;
			buc = new list_node;
			making_list_(run->right, buc);
			making_list_(run->left, buc);
			nhead = buc->get_nnext();
			delete buc;
			return nhead;
		}
		making_list_(run->right, nhead);
		making_list_(run->left, nhead);
		return nhead;
	}

	int delete_node_in_tree(RBTree_node <T> *buf) //если программа зашла в if, она должна закончить работу в нём, если в нём нет else
	{
		if (!buf) return 0;
		//printf("\n\n\n\n\nTree\n"); print_tree_(stdout, buf); printf("buf "); buf->print_record(); printf("\n");
		//списочные сценарии
		if (buf->next) //удаление элемента, когда у него есть брат
		{
			RBTree_node <T> *nuxt = buf->next;
			if (!buf->prev) //когда он первый из братьев, то есть он входит в дерево.
			{
				//printf("\n\nwas here?1\n"); printf("buf "); buf->print_record(); printf("\n");
				//printf("\nFIRST DELETING2\n\n");
				nuxt->parent = buf->parent;
				nuxt->right = buf->right;
				if (buf->right)
					buf->right->parent = nuxt;
				nuxt->left = buf->left;
				if (buf->left)
					buf->left->parent = nuxt;
				nuxt->color = buf->color;
				nuxt->prev = nullptr;
				if (buf == root) //когда он еще и корень
					root = nuxt;
				else
				{
					(buf->parent->right == buf ? buf->parent->right = nuxt : buf->parent->left = nuxt);
				}
				//printf("buf parent left= "); print_node(buf->parent->left);
				delete buf;
				return WORK_DONE;
			}
			//когда он не первый из братьев <==> удаление из двунаправленного списка

			//printf("\n\nwas here?2\n"); printf("buf "); buf->print_record(); printf("\n"); printf("buf->prev "); buf->prev->print_record(); printf("\n");
			buf->prev->next = nuxt;
			nuxt->prev = buf->prev;
			delete buf;
			return WORK_DONE;
		}
		if (buf->prev) //когда надо удалить самый дальний из братьев
		{
			//printf("Privet\n");
			buf->prev->next = nullptr;
			delete buf;
			return WORK_DONE;
		}
		//древесные сценарии, если дошел до сюда, то удалять надо точно те элементы, которые узлы дерева, то есть первые из братье, если вообще братья есть
		if (buf->right && buf->left)//сделать так, чтобы buf имел одного потомка
		{
			//printf("tut est' AAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
			RBTree_node <T> *run = buf->right;
			while(run->left)
				run = run->left;


			change_node(buf, run); //ГДЕ-ТО ТУТ ОШИБКА!!!!!
			buf = run;
			//printf("\nbuf"); print_node(buf);
		}
		//printf("\nTUT buf = ");buf->print_record(); printf("\n"); print_tree();
		//на этом этапе buf имеет либо одного либо 0 потомков!
		//printf("\nbuf"); print_node(buf);
		if (buf->color == RED) //цвет удаляемого узла красный, легкий случай, также стоит отметить, что корень черный всегда, поэтому в этом случае корня не будет!
		{
			RBTree_node <T> *dad = buf->parent, *grandson = buf->right ? buf->right: buf->left;
			//printf("dad "); dad->print_record(); printf("\n");
			if (dad->right == buf)
				dad->right = grandson;
			else
			{
				dad->left = grandson;
				//printf("VOT TUT\n");
			}
			if (grandson)
				grandson->parent = dad;
			delete buf;
			//printf("\ndad"); print_node(dad);
			//if (!dad->right) printf("All good\n");
			return WORK_DONE;
		}
		//далее цвет удаляемого узла черный
		if (buf == root)
		{
			root = buf->right ? buf->right : buf->left;
			if (root)
			{
				root->parent = nullptr;
				root->color = BLACK;
			}
			delete buf;
			return WORK_DONE;
		}
		//далее buf не корень!, а значит есть buf->parent
		RBTree_node <T> *dad = buf->parent, *son = (buf->right ? buf->right: buf->left), *grandad, *bro, *lneph, *rneph;
		if (dad->right == buf)
			dad->right = son;
		else
			dad->left = son;
		if (son)
			son->parent = dad;
		delete buf;
		while (dad) //dad != nullpt; son возможно nullptr их двоих надо обязательно задавать!
		{
			//printf("\ndad in while"); print_node(dad);
			//if (!son) printf("\nEMTY\n"); else {printf("\nson "); print_node(son);}
			if (son) //
				if (son->color == RED)
				{
					son->color = BLACK;
					return WORK_DONE;
				}
			//дарее son черный, и он либо есть, либо его нет (вообще его не должно быть)
			if (dad->left == son) //son слева, bro справа, оба мб нулевые, это неизвестно!
			{
				bro = dad->right;
				//printf("\nbro "); print_node(bro);
				if (bro) //bro не нулевой
				{
					if (bro->color == RED)
					{
						dad->right = bro->left;
						if (bro->left)
							bro->left->parent = dad;
						bro->left = dad;
						if (dad == root)
							root = bro;
						else
						{
							grandad = dad->parent;
							if (grandad->right == dad)
								grandad->right = bro;
							else
								grandad->left = bro;
							bro->parent = grandad;
						}
						dad->parent = bro;
						bro->color = BLACK;
						dad->color = RED;
						continue;
					}
					else //bro->color = BLACK;
					{
						lneph = bro->left;
						rneph = bro->right;
						if (rneph)
						{
							if(rneph->color == RED) //правый племянник - красный
							{
								dad->right = lneph;
								if (lneph)
									lneph->parent = dad; //?
								bro->left = dad;
								if (dad == root)
									root = bro;
								else
								{
									grandad = dad->parent;
									if (grandad->right == dad)
										grandad->right = bro;
									else
										grandad->left = bro;
									bro->parent = grandad;
								}
								dad->parent = bro;
								bro->color = dad->color;
								dad->color = BLACK;
								rneph->color = BLACK;
								return WORK_DONE;
							}
							else //если правый племянник существует и он не красный, то левый тоже обязательно существует
							{
								if(lneph->color == RED)
								{
									bro->left = lneph->right;
									if (lneph->right)
										lneph->right->parent = bro;
									dad->right = lneph;
									lneph->parent = dad;
									lneph->right = bro;
									bro->parent = lneph;
									lneph->color = BLACK;
									bro->color = RED;
									continue;
								}
								else //племяши оба черные
								{
									if (dad->color == RED)
									{
										bro->color = RED;
										dad->color = BLACK;
										return WORK_DONE;
									}
									else
									{
										bro->color = RED;
										son = dad;
										if (dad == root)
											return WORK_DONE;
										dad = son->parent;
										continue;
									}
								}
							}
						}
						else //оба племяша нулевые, и черные, bro черный, son черный, смотрит, на цвет dad
						{
							if (dad->color == RED)
							{
								bro->color = RED;
								dad->color = BLACK;
								return WORK_DONE;
							}
							else
							{
								bro->color = RED;
								son = dad;
								if (dad == root)
									return WORK_DONE;
								dad = son->parent;
								continue;
							}
						}
					}
				}
				else	//bro нулевой (есть подозрение, что в таком случае dad обязательно Красный) ((в 7 утра появились подозрения, что такого случая точно не будет)) :D
				{
					printf("Hmmm1\n");
				}
			}
			else //son справа, bro, слева, оба мб нулевые ЗЕРКАЛЬНАЯ СИТУАЦИЯ ВСЕМУ ПРЕДЫДУЩЕМУ
			{

				bro = dad->left;
				//printf("\nbro "); print_node(bro);
				if (bro) //bro != nullptr
				{
					//printf("\n\nhrum1\n\n");
					if(bro->color == RED)
					{
						dad->left = bro->right;
						if (bro->right)
							bro->right->parent = dad;
						bro->right = dad;
						if (dad == root)
							root = bro;
						else
						{
							grandad = dad->parent;
							if (grandad->right == dad)
								grandad->right = bro;
							else
								grandad->left = bro;
							bro->parent = grandad;
						}
						dad->parent = bro;
						bro->color = BLACK;
						dad->color = RED;
						continue;
					}
					else //bro->color = BLACK
					{
						lneph = bro->left;
						rneph = bro->right;
						if (lneph)
						{
							if (lneph->color == RED) //левый племяш красный
							{
								//printf("\ndad in while"); print_node(dad);
								//if (!son) printf("\nEMTY\n"); else {printf("\nson "); print_node(son);}
								//printf("\nbro "); print_node(bro);
								//printf("\n\nhrum2\n\n");
								dad->left = rneph;
								if (rneph)
									rneph->parent = dad;
								bro->right = dad;
								if (dad == root)
									root = bro;
								else
								{
									grandad = dad->parent;
									if (grandad->right == dad)
										grandad->right = bro;
									else
										grandad->left = bro;
									bro->parent = grandad;
								}
								dad->parent = bro;
								bro->color = dad->color;
								dad->color = BLACK;
								lneph->color = BLACK;
								//printf("DEREVO\n");
								//print_tree();
								return WORK_DONE;
							}
							else
							{
								if (rneph->color == RED)
								{
									bro->right = rneph->left;
									if (rneph->left)
										rneph->left->parent = bro;
									dad->left = rneph;
									rneph->parent = dad;
									rneph->left = bro;
									bro->parent = rneph;
									rneph->color = BLACK;
									bro->color = RED;
									continue;
								}
								else //оба племяша - черные
								{
									if (dad->color == RED)
									{
										bro->color = RED;
										dad->color = BLACK;
										return WORK_DONE;
									}
									else
									{
										bro->color = RED;
										son = dad;
										if (dad == root)
											return WORK_DONE;
										dad = son->parent;
										continue;
									}
								}
							}
						}
						else
						{
							if (dad->color == RED)
							{
								bro->color = RED;
								dad->color = BLACK;
								return WORK_DONE;
							}
							else
							{
								bro->color = RED;
								son = dad;
								if (dad == root)
									return WORK_DONE;
								dad = son->parent;
								continue;
							}

						}
					}
				}
				else  // bro == nullptr
				{
					printf("Hmmm2\n");
					//while (scanf("\n"));
				}
			}
		}
		return 0;
	}


	void change_node(RBTree_node <T> *a, RBTree_node <T> *b) //оба узла существуют!
	{
		a->change_node(b);
		if (a->next || b->next)
		{
			//printf("\n\nWWWWWWWWWAAAAAASSS HERE?\n");
			RBTree_node <T> *t = a->next;
			a->next = b->next;
			if (b->next)
				b->next->prev = a;
			b->next = t;
			if (t)
				t->prev = b;


		}
	}
	void delete_node(list_node *nuxt,  ratio (*comp)(list_node *, RBTree_node <T> *), int (*total_comp)(list_node *, RBTree_node <T> *))
	{
		RBTree_node <T> *run = root;
		ratio res;
		int rus;
		while (run)
		{
			res = (*comp)(nuxt, run);
			/*
			if (nuxt->value == 16)
				printf("nuxt = %d, run = %d, res = %d\n", nuxt->value, run->value, res);
				*/
			switch(res)
			{
			case LESS:
				run = run->left;
				break;
			case MORE:
				run = run->right;
				break;
			case EQUAL:
				if (run->check() == LISTNODE)
				{
					rus = (*total_comp)(nuxt, run);
					if (rus == EQUALITY)
					{
						delete_node_in_tree(run);
						return;
					}
					while (run->next)
					{
						run = run->next;
						rus = (*total_comp)(nuxt, run);
						if (rus == EQUALITY)
						{
							delete_node_in_tree(run);
							return;
						}
					}
					return;
				}
				else
				{
					 run->delete_key(nuxt);
					 return;
				}
			}
		}
	}
};


#endif // REDBLACKTREE_H
