#include <stdio.h>
#include "const.h"
#ifndef STRING_H
#define STRING_H

class  String
{
        private:
                char* name = nullptr;
        public:
                String() = default;
                String(const String& x);
                String(String&& x);
                ~String ();

                String& operator= (const String& x);
                String& operator= (String&& x);
                int operator< (const String& x);
                int operator> (const String& x);

                const char* get_name () const;
                int read(FILE *fp);
                void print(FILE* out = stdout);

                int init(const char* n);
                void destroy();

                bool comp(const char* x);
};
#endif //STRING_H
