#include "list.h"
#include "list_node.h"
#include "command.h"
#include "errors.h"

#define MAX_PRINT 10

list::~list(){
	destroy();
}

list_node * list::search(const command &x){
	list_node *curr, *start, *last;

	for(curr = head; curr; curr = curr->next){
		if(x.check_cond(curr)) break;
	}
	if(!curr) return nullptr;

	start = last = curr;
	for(curr = curr->next; curr; curr = curr->next){
		if(x.check_cond(curr)){
			last = last->next_search = curr;
		}
	}
	last->next_search = nullptr;

	return start;
}

int list::insert(list_node *curr){
	if(!curr) return ERR_NULL_ARG;

	/*
	for(list_node *tmp = head; tmp; tmp = tmp->next){
		if(*tmp == *curr) return 0;
	}
	*/

	curr->next = head;
	curr->prev = nullptr;
	if(head) head->prev = curr;
	head = curr;

	return 0;
}

int list::remove(list_node *curr){
	if(!curr) return 0;

	if(curr == head){
		head = head->next;
		if(head) head->prev = nullptr;
		delete curr;
	}
	else{
		curr->prev->next = curr->next;
		if(curr->next) curr->next->prev = curr->prev;
		delete curr;
	}

	return 0;
}

void list::destroy(){
	list_node *curr;

	while(head){
		curr = head->next;
		delete head;
		head = curr;
	}
}

int list::isCorrect() const {
	if(!head) return 1;
	if(head->prev) return 0;

	for(list_node *curr = head; curr->next; curr = curr->next){
		if(curr->next->prev != curr) return 0;
	}

	return 1;
}

void list::print(FILE *fp) const {
	list_node *curr = head;

	if(fp == stdout){
		for(int i = 0; i < MAX_PRINT; i++){
			if(!curr) break;
			curr->print();
			curr = curr->next;
		}
	}
	else{
		while(curr){
			curr->print(fp);
			curr = curr->next;
		}
	}
}
