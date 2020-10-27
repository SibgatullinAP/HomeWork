#include "string.h"
#include "addons.h"
#include "const.h"

#include <stdio.h>
#include <string.h>
#include <iostream>

bool String::comp(const char *x)
{
       if(strspn(name, x) < strlen(name))
       {
           return false;
       }
       else
       {
           return true;
       }
}

int String::init (const char* n)
{
	if (n)
	{
            name = new char[strlen(n) + 1];
            if (name == nullptr)
            {
                return ERROR_CANNOT_INITIALIZE_STRING_NAME;
            }
            strcpy (name, n);

	}
	else
	{
            name = nullptr;
	}
	return 0;
}

void String::destroy ()
{
	if(name)
	{
            delete [] name;
            name = nullptr;
	}
}

String::String (const String& x)
{
        init(x.name);
}

String::String (String&& x)
{
	name  = x.name;

	x.name = nullptr;
}

String& String::operator= (const String& x)
{
	destroy();
        init(x.name);
	return *this;
}

String& String::operator= (String&& x)
{
	destroy();

	name = x.name;
	x.name = nullptr;

	return *this;
}

String::~String()
{
	destroy();
}

int String::read(FILE* fp)
{
        char buff[LEN];

        destroy();

        if( fscanf(fp, "%s", buff) != 1)
        {
            if(feof(fp))
            {
                return NOT_ERROR_END_OF_INPUT;
            }
            return ERROR_CANNOT_READ_INPUT_FILE;
        }

        if(init(buff))
        {
                return ERROR_CANNOT_INITIALIZE_STRING_NAME;
        }

        return 0;
}

int String::operator<(const String& x)
{
	if(!name) return 1;
	if(!x.name) return 0;

        int res = strcmp(name, x.name);
	if (res < 0) return 1;
	if (res > 0) return 0;

        return 0;
}

int String::operator>(const String& x)
{
	if(!name) return 0;
	if(!x.name) return 1;

        int res = strcmp(name, x.name);
	if (res < 0) return 0;
	if (res > 0) return 1;

        return 0;
}	

void String::print(FILE* out)
{
        fprintf(out, "%s\n", name);
}

const char* String::get_name() const
{
    return (const char* )name;
}
