#include "student.h"
#define LEN 1234

using namespace std;

int student::init(const char* n, int v) //конструктор с аргументами
{
    value = v;
    if(n)
    {
        name = new char[strlen(n) + 1];
        if(!name) return -1;
        strcpy(name, n);
    }
    else name = 0;
    return 0;
}

void student::destroy() //очищение памяти
{
    if(name){delete [] name; name = nullptr;}
    value = 0;
}

student::student(const student& x) {init(x.name, x.value);} //конструктор копирования

student::student(student&& x) //конструктор копирования временного объекта
{
    value = x.value; //даем новому объекту выделенную память для временного
    name = x.name;
    x.value = 0;     //чтобы деструктор временного объекта не уничтожил память которую мы уже передали
    x.name = nullptr; //обнуляем указатели временного объекта
}

student& student::operator=(const student& x) //оператор присваивания
{
    destroy(); //удаляем изначальный объект, чтобы не потерять его исходный указатель и не вызвать утечку памяти
    init(x.name, x.value);
    return *this;  // *this - это объект с которым работает данный метод (невидимый аргумент)
}

student& student::operator=(student&& x)
{
    destroy();
    value = x.value;
    name = x.name;
    x.value = 0;
    x.name = nullptr;
    return *this;
}

student::~student(){destroy();}

int student::read(FILE *fp)
{
    char buf[LEN];
    destroy();
    if(fscanf(fp, "%s %d", buf, &value) != 2)
    {
        if(feof(fp)) return 1;
        return -1;
    }
    if(init(buf, value)) return -2;
    return 0;
}

void student::print()
{
    cout << '['<< name << ' ' << value << ']';
}

int student::operator<(const student& x) const
{
    int res;
    if(!name && !x.name) return value < x.value;
    if(!name) return 1;
    if(!x.name) return 0;
    res = strcmp(name, x.name);
    if(res < 0) return 1;
    if(res > 0) return 0;
    return value < x.value;
}

int student::operator>(const student& x) const
{
    int res;
    if(!name && !x.name) return value > x.value;
    if(!name) return 0;
    if(!x.name) return 1;
    res = strcmp(name, x.name);
    if(res < 0) return 0;
    if(res > 0) return 1;
    return value > x.value;
}

int student::operator==(const student& x) const
{
    int res;
    if(!name && !x.name) return value == x.value;
    if(!name || !x.name) return 0;
    res = strcmp(name, x.name);
    if(res == 0) return value == x.value;
    return 0;
}

void student::swap(student& x)
{
    int vsave;
    char* save;
    save = x.name; x.name = name; name = save;
    vsave = x.value; x.value = value; value = vsave;
}

void student::moveto(student& x) //опасна утечка памяти, если потерять x.name
{
    x.name = name; x.value = value;
}

void student::reset()
{
    value = 0; name = nullptr;
}
