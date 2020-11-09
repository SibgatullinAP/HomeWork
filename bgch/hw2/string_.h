#ifndef STRING_H
#define STRING_H
#include "constants.h"


class Parse_results
{
public:
  int pattern_len = 0;
  bool is_regexp = false;
  int error = 0;

public:
  Parse_results () = default;
  ~Parse_results () = default;

  void print () { printf ("pattern_len = %d\nis_regexp = %d\nerror = %d\n", pattern_len, is_regexp, error);}
};

int regexp_solve (char *in_file_name, char *out_file_name, char *str_pattern,
                  void (*parse)(char *, char *, Parse_results &),
                  bool (*cmp)(char *, char *, Parse_results &));

void parse_1 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp);
bool cmp_1 (char *str, char *str_pattern, Parse_results &regexp);

void parse_2 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp);
bool cmp_2 (char *str, char *str_pattern, Parse_results &regexp);

void parse_3 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp);
bool cmp_3 (char *str, char *str_pattern, Parse_results &regexp);

void parse_4 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp);
bool cmp_4 (char *str, char *str_pattern, Parse_results &regexp);

void parse_5 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp);
bool cmp_5 (char *str, char *str_pattern, Parse_results &regexp);

void parse_6 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp);
bool cmp_6 (char *str, char *str_pattern, Parse_results &regexp);

void parse_7 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp);
bool cmp_7 (char *str, char *str_pattern, Parse_results &regexp);

void parse_8 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp);
bool cmp_8 (char *str, char *str_pattern, Parse_results &regexp);

void parse_9 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp);
bool cmp_9 (char *str, char *str_pattern, Parse_results &regexp);

#endif
