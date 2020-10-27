#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <memory>
#include "const.h"

class  Student 
{
	private:
	        std::unique_ptr <char [ ]> name = nullptr;
		int value = 0;
                enum MENU_PROPERTIES
                {
                    MENU = 'm',
                    EXIT = 'e',
                    PRINT = 'p',
		    REWRWITE = 'r',
		    DESTROY = 'd'
                };
	public:
                Student() = default;
                Student(const Student& x);
                Student(Student&& x);
		~Student() = default;

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
                void change_student();

                void menu();
                void print_menu();
};

void clear();
#endif //STUDENT_H
