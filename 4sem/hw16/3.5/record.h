#ifndef RECORD_H
#define RECORD_H

#include "constants.h"

class Record
{
    private:
        std::unique_ptr <char[]> Name;
	int Group = -1;
	int Phone = -1;
    public:
	Record() = default;
	~Record() = default;

	char* getName() const { return Name.get(); }
	int getGroup() const { return Group; }
	int getPhone() const { return Phone; }

	bool setGroup(char *input)
	{
	    if (sscanf(input, "%d", &Group) != 1)
	    {
		return false;
	    }
	    return true;
	}

	bool setPhone(char *input)
	{
	    if (sscanf(input, "%d", &Phone) != 1)
	    {
		return false;
	    }
	    return true;
	}

	int setName(char* input)
	{
	    Name = std::make_unique<char[]>(strlen(input) + 1);
	    if(Name == nullptr)
	    {
		return ERROR_CANNOT_ALLOCATE_MEMMORY_TO_READ_NAME;
	    }
	    strcpy(Name.get(), input);
	    return 1;
	}


	bool setGroup(int input)
	{
	    Group = input;
	    return true;
	}

	bool setPhone(int input)
	{
	    Phone = input;
	    return true;
	}

	int initialization(const char* string, int group, int phone)
	{
	    this->Name = nullptr;
	    Group = Phone = 0;

	    if(string != nullptr)
	    {
		Name = std::unique_ptr<char[]>(new char[strlen(string) + 1]);
		if(Name == nullptr)
		{
		    return ERROR_CANNOT_ALLOCATE_MEMMORY_TO_READ_NAME;
		}
		strcpy(Name.get(), string);
	    }
	    else
	    {
		Name = nullptr;
	    }
	    Group = group;
	    Phone = phone;

	    return 1;
	}

	void print(FILE* outFile = stdout)
	{
	    fprintf(outFile, "%-20s %-11d %-5d\x1b[0m\n", getName(), getPhone(), getGroup());
	}

};

#endif // RECORD_H
