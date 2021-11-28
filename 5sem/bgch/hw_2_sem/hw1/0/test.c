#include <string.h>
#include "test.h"
int test_str(const char *in, const char *s){
	return !!strstr(in, s);
}