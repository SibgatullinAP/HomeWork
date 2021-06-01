#include "data_bus.h"
const char *enum_to_string (status state)
{
  switch (state)
    {
    case status::FREE:
      return "Nothing to do";
    case status::COMPUTING:
      return "Computing";
    case status::DONE:
      return "Transfering data";
    case status::COUNT:
      return "Invalid status";
    }
  return "";
}
