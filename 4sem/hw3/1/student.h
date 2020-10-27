#include <stdio.h>

#ifndef STUDENT_H
#define STUDENT_H

class  Student 
{
	private:
		char* name = nullptr;
		int value = 0;
	public:
                Student() = default;
                Student(const Student& x);
                Student(Student&& x);
                ~Student ();

                Student& operator= (const Student& x);
                Student& operator= (Student&& x);
                int operator< (const Student& x);
                int operator> (const Student& x);

		const char* get_name () const;
		int get_value () const;
                int read(FILE *fp);
                void print(FILE* out = stdout);
                void swap(Student& x);
                void copy(const Student& x);

                int init(const char* n, int v);
                void destroy();
};
#endif //STUDENT_H
