#include "hash.h"
#include "list_node.h"
#include "errors.h"

int hash::h_func(const record &x) const {
	int res = 0;
	char *str = x.get_name();

	for(int i = 0; str[i]; i++){
		res += (unsigned int)str[i];
	}

	return (res % size);
}

hash::~hash(){
	delete[] arr;
	size = 0;
}

int hash::setSize(int size){
	if(arr) delete[] arr;

	this->size = size;

	arr = new tree[size];
	if(!arr) return ERR_MEMORY;

	for(int i = 0; i < size; i++){
		arr[i].setCmp(&record::name_cmp);
	}

	return 0;
}

list_node * hash::search(const command &x, data_type cond, int ident) const {
	return arr ? arr[h_func(x)].search(x, cond, ident) : nullptr;
}

int hash::insert(list_node *x){
	if(!x) return ERR_NULL_ARG;

	return arr ? arr[h_func(*x)].insert(x) : ERR_NULL_ARG;
}

int hash::remove(const list_node *x){
	if(!x) return ERR_NULL_ARG;

	return arr ? arr[h_func(*x)].remove(x) : ERR_NULL_ARG;
}

void hash::destroy(){
	if(arr){
		for(int i = 0; i < size; i++){
			arr[i].destroy();
		}
	}
}

int hash::isCorrect() const {
	if(!arr) return 1;

	for(int i = 0; i < size; i++){
		if(!arr[i].isCorrect()) return 0;
	}

	return 1;
}

void hash::print(FILE *fp) const {
	if(fp == stdout){
		if(arr){
			for(int i = 0; i < size; i++){
				printf("arr[%d] = {\n", i);
				arr[i].print();
				printf("}\n");
			}
		}
		else printf("no array\n");
	}
	else{
		for(int i = 0; i < size; i++) arr[i].print(fp);
	}
}
