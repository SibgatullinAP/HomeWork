#ifndef IO_H
#define IO_H

#include "common.h"

class CDS_solver;

std::optional<std::vector<CDS_solver>> parse_dat_file (const std::string &file_name);
bool parse_cmd_line (int argc, const char *argv[]);

#endif // IO_H
