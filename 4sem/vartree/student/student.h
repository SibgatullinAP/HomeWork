#ifndef STUDENT_H
#define STUDENT_H

#include <cstdlib>
#include <iostream>
#include <cstring>

class student
{
private:
    char* name = nullptr;
    int value = 0;
public:
    student() = default;
    student(const student& x); //конструктор копирования
    student(student&& x);
    student& operator=(const student& x);
    student& operator=(student&& x);
    int init(const char* n, int v);
    void destroy();
    ~student();
    int read(FILE *fp);
    int operator<(const student& x) const;
    int operator>(const student& x) const;
    int operator==(const student& x) const;
    void print();
    void swap(student& x);
    void moveto(student& x);
    void reset();
};

#endif
