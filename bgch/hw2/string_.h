#ifndef STRING_H
#define STRING_H
#include "constants.h"

int regexp (char *in_file_name, char *out_file_name, char *str_pattern,
            int (*parse)(char *, char *),
            bool (*cmp)(char *, char *, int ));

int parse_1 (char *str_pattern, char *str_pattern_copy);
bool cmp_1 (char *str, char *str_pattern, int is_begin);

int parse_2 (char *str_pattern, char *str_pattern_copy);
bool cmp_2 (char *str, char *str_pattern, int is_begin);
#endif