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
};

int regexp_solve (char *in_file_name, char *out_file_name, char *str_pattern,
                  void (*parse)(char *, char *, Parse_results &),
                  bool (*cmp)(char *, char *, Parse_results &));

void parse_1 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp);
bool cmp_1 (char *str, char *str_pattern, Parse_results &regexp);

void parse_2 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp);
bool cmp_2 (char *str, char *str_pattern, Parse_results &regexp);
#endif
