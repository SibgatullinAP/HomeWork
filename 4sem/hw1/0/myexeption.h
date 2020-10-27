#ifndef MYEXEPTION_H
#define MYEXEPTION_H 

#define MessageLenght 300

class MyExeption {

	private:
		int id;
		char message[MessageLenght];

	public:
		MyExeption(int k, const char *msg);
		~MyExeption();
		const char *GetMessage ();
		int GetId ();
	
};

void MyAssert (bool, int, const char *);

#endif

