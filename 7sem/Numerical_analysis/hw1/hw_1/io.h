#ifndef IO_H
#define IO_H

#include <optional>
#include <string>
#include <vector>

class CDS_solver;

std::optional<std::vector<CDS_solver>> parse_dat_file (const std::string &file_name);

#endif // IO_H
