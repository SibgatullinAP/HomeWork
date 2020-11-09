#include "common.hpp"

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

double
get_time ()
{
  struct timeval tm;
  gettimeofday (&tm, nullptr);
  return (double) (tm.tv_sec + tm.tv_usec / 1e6);
}

double
get_cpu_time ()
{
  struct rusage tm;
  getrusage (RUSAGE_THREAD, &tm);
  return (double) (tm.ru_utime.tv_sec + tm.ru_utime.tv_usec / 1e6);
}
