#include <string.h>

#include "myexeption.h"

int MyExeption::GetId ()
{
	return id;
}

const char * MyExeption::GetMessage()
{
	return message;
}

MyExeption::MyExeption (int k, const char *msg)
{
	id = k;
	strncpy(message, msg, MessageLenght);
}

void MyAssert (bool v, int id, const char *s)
{
	if(!v)
	{
		throw new MyExeption(id,s);
	}
}