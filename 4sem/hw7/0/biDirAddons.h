#ifndef ADDONS_H
#define ADDONS_H

#include "student.h"
#include "biDirList.h"
#include "biDirListNode.h"
#include "const.h"

#include <stdlib.h>
#include <signal.h>

bool compareMore(ListNode*, ListNode*);
bool compareLess(ListNode*, ListNode*);

int read_list(const char* name, List & a);
bool checkSort(List* a, bool (*comp)(ListNode*, ListNode*));

int logo1(bool selector = false, const char* inputfile = "art.txt");
int logo2(bool selector = false, const char* inputfile = "sad.txt");
void posix_death_signal(int signum);
void fall();

#endif // ADDONS_H
