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

		char* getName() {return Name.get();}
		int getGroup() {return Group;}
		int getPhone() {return Phone;}

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

			return 0;
		}


};

#endif // RECORD_H
