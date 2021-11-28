#include "io.h"

bool parse_cmd_line (int argc, const char */*argv*/[])
{
  std::string usage =
      "./cds X T N0 M0 k_dr n_max m_max (LGR_factor)\n"
" X - [0; X]";
  if (argc != 10)
    {
      (void) 0;
    }

  return true;
}

