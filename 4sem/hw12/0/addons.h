#ifndef ADDONS_H
#define ADDONS_H

#include "list.h"

#include <stdlib.h>
#include <signal.h>

int read(const char* name, List <Student, Queue, Tree> & a, int size_list, int size_tree, int size_queue);

int logo1(bool selector = false, const char* inputfile = "art.txt");
int logo2(bool selector = false, const char* inputfile = "sad.txt");
void posix_death_signal(int signum);
void fall();

#endif // ADDONS_H
