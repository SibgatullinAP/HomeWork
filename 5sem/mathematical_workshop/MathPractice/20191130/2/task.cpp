#include "common.hpp"
#include "task.hpp"

void
replace (double * prev, double * curr, double * next, size_t len)
{

  double a, b;
  size_t i;

  a = curr[0];
  b = curr[1];

  for (i = 1; i < len - 1; i++)
    {
      curr[i] = a + prev[i] + next[i] + curr[i + 1] - 4 * b;
      prev[i] = b;
      a = b;
      b = curr[i + 1];
    }

  prev[0] = curr[0];
  prev[len - 1] = curr[len - 1];

}
