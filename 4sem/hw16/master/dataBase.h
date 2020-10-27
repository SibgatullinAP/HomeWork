#ifndef DATABASE_H
#define DATABASE_H

#include "list.h"
#include "RedBlackTree.h"

class DataBase
{
    List * Container = nullptr;
    RedBlackTreeName * NameSearch = nullptr;
    Hash * PhoneSearch = nullptr;
    RedBlackTree * GroupSearch = nullptr;
    public:
        DataBase(int HashSize)
	{
	    Container = new List;

	    NameSearch = new RedBlackTreeName;
	    PhoneSearch = new Hash(HashSize);
	    GroupSearch = new RedBlackTree(HashSize);
	}
	DataBase() = default;
	~DataBase()
	{
	    delete NameSearch;
	    delete PhoneSearch;
	    delete GroupSearch;

	    delete Container;
	}

	int read(FILE * inFile);
	void print(FILE * outFile = stdout);
	void deleteDataBase();

	int insertingRequest(char* name, int phone, int group);
	int selectingRequest(Command & current, FILE * outFile = stdout);
	int deletingRequest(Command & current);

	int requestExecute(Command & current, FILE * outputResult = stdout);
	void run(FILE * inputRequest = stdin, FILE *outputResult = stdout);
};

#endif // DATABASE_H
