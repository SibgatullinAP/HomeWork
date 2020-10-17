#ifndef SEQUENCES_H
#define SEQUENCES_H

#include "constants.h"

int rebuild_sequnce (const char *file_name, int k);
int check (const char *file_name_1, const char *file_name_2);
int rms_deviation (const char *file_name, double *answer);
int type_of_sequence (const char *file_name);

#endif //SEQUENCES_H
