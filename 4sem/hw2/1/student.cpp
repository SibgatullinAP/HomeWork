#include "student.h"
#include "addons.h"


#include <stdio.h>
#include <string.h>
#include <iostream>

#define LEN 1234

int Student::init (const char* n, int v)
{
	value = v;

	if (n)
	{
		name = new char[strlen(n) + 1];
        if (name == nullptr)
		{
			return ERROR_CANNOT_INITIALIZE_STUDENT_NAME;
		}
		strcpy (name, n);
	}
	else
	{
        name = nullptr;
	}

	return 0;
}

void Student::destroy ()
{
	if(name)
	{
            delete [] name;
            name = nullptr;
	}

	value = 0;
}

Student::Student (const Student& x)
{
	init(x.name, x.value);
}

Student::Student (Student&& x)
{
	value = x.value;
	name  = x.name;

	x.value = 0;
	x.name = nullptr;
}

Student& Student::operator= (const Student& x)
{
	destroy();

	init(x.name, x.value);

	return *this;
}

Student& Student::operator= (Student&& x)
{
	destroy();

	value = x.value;
	name = x.name;

	x.value = 0;
	x.name = nullptr;

	return *this;
}

Student::~Student()
{
	destroy();
}

int Student::read(FILE* fp)
{
	char buff[LEN];

	destroy();
	
        if( fscanf(fp, "%s %d", buff, &value) != 2 )
        {
            if(feof(fp))
            {
                return NOT_ERROR_END_OF_INPUT;
            }
            return ERROR_CANNOT_READ_INPUT_FILE;
        }

        if(init(buff, value))
        {
                return ERROR_CANNOT_INITIALIZE_STUDENT_NAME;
        }

	return 0;
}

int Student::operator<(const Student& x)
{
	if(!name && !x.name)
	{
		return value < x.value;
	}

	if(!name) return 1;
	if(!x.name) return 0;

        int res = strcmp(name, x.name);
	if (res < 0) return 1;
	if (res > 0) return 0;

	return value < x.value;
}

int Student::operator>(const Student& x)
{
	if(!name && !x.name)
	{
		return value > x.value;
	}

	if(!name) return 0;
	if(!x.name) return 1;

        int res = strcmp(name, x.name);
	if (res < 0) return 0;
	if (res > 0) return 1;

	return value > x.value;
}

int Student::operator==(const Student& x)
{
	if(value == x.value && !strcmp(name,x.name))
	{
		return 1;
	}
	return 0;
}


void Student::copy(const Student& x){
    value = x.value;
    name = x.name;
}

void Student::swap(Student& x)
{
	int tmp = value;
	value = x.value;
	x.value = tmp;

	char* buff = name;
	name = x.name;
        x.name = buff;
}

void Student::print(FILE* out)
{
	fprintf(out, "%s %d\n", name, value);
}

const char* Student::get_name() const 
{
    return (const char* )name;
}

int Student::get_value() const 
{
	return value;
}
