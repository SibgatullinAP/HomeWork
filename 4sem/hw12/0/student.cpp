#include "student.h"

void clear()
{
    for(int i = 0; i < ENTER_QUANTITY; i++) printf("\n");
}

void Student::menu()
{
    clear();
    print_menu();

    MENU_PROPERTIES key;
    char buff[LEN];
    for(;;)
    {
	clear();
	printf("\nEnter your choise: ");
	if(!fgets(buff, LEN, stdin)) return;

        key = MENU_PROPERTIES(buff[0]);
        switch(key)
        {
            case MENU:
		clear();
                print_menu();
		break;

	    case EXIT:
		return;

            case PRINT:
		clear();
		printf("Choosen Student: ");
                print();
		printf("\n");
		break;

            case REWRWITE:
		change_student();
		break;

	    case DESTROY:
		this->name = nullptr;
		value = 0;
		break;

	    default:
		clear();
		printf("\nFor coming back to menu press - \x1b[1;33mm\x1b[0m!\n");
		break;
        }
    }
}

void Student::print_menu()
{
    printf(" ---------------------\n");
    printf("|  ~Menu for Student~ |\n");
    printf("|    \x1b[1;33mm\x1b[0m - Show menu    |\n");
    printf("|    \x1b[1;33me\x1b[0m - Exit menu    |\n");
    printf("|  \x1b[1;33mp\x1b[0m - Print Student  |\n");
    printf("| \x1b[1;33mr\x1b[0m - Rewrite Student |\n");
    printf("| \x1b[1;33md\x1b[0m - Destroy Student |\n");
    printf(" ---------------------\n");
}

void Student::change_student()
{
    printf("Let's initialize student!\nFor empty student just press [ENTER].\nEnter [student's name] [value] : \n");

    char buff[LEN];
    fgets(buff, LEN, stdin);

    int val = 0;
    char buff_student[LEN];
    if(sscanf(buff, "%s %d", buff_student, &val) != 2)
    {
	printf("Incorrect input values!\nStudent was initialized as empty!\n");
	return;
    }

    this->name = nullptr;
    value = 0;

    if(init(buff_student, val) < 0)
    {
	printf("Error! The name is too long\n");
    }
    printf("New student ");
    print();
    printf(" has been added!\n");
}

int Student::init (const char* n, int v)
{
    this->name = nullptr;
    value = 0;

    value = v;

    if (n)
    {
	name = std::unique_ptr <char [ ]> (new char [strlen (n) + 1]);
	if (name == nullptr)
	{
	    return ERROR_CANNOT_INITIALIZE_STUDENT_NAME;
	}
	strcpy (name.get(), n);
    }
    else
    {
	name = nullptr;
    }

    return 0;
}

Student::Student (const Student& x)
{
    init(x.name.get(), x.value);
}

Student::Student (Student&& x)
{
    value = x.value;
    name  = std::move (x.name);

    x.value = 0;
    x.name = nullptr;
}

Student& Student::operator= (const Student& x)
{
    this->~Student();

    init(x.name.get(), x.value);

    return *this;
}

Student& Student::operator= (Student&& x)
{
    this->~Student();

    value = x.value;
    name = std::move(x.name);

    x.value = 0;
    x.name = nullptr;

    return *this;
}

int Student::read(FILE* fp)
{
    char buff[LEN];

    this->~Student();

    if( fscanf(fp, "%s %d", buff, &value) != 2 )
    {
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
    if(!this->name.get() && !x.name.get())
    {
	return value < x.value;
    }

    if(!this->name.get()) return 1;
    if(!x.name.get()) return 0;

    int res = strcmp(this->name.get(), x.name.get());
    if (res < 0) return 1;
    if (res > 0) return 0;

    return value < x.value;
}

int Student::operator>(const Student& x)
{
    if(!this->name.get() && !x.name.get())
    {
	return value > x.value;
    }

    if(!this->name.get()) return 0;
    if(!x.name.get()) return 1;

    int res = strcmp(this->name.get(), x.name.get());
    if (res < 0) return 0;
    if (res > 0) return 1;

    return value > x.value;
}	

void Student::swap(Student& x)
{
    int tmp = value;
    value = x.value;
    x.value = tmp;

    name.swap(x.name);
}

void Student::print(FILE* out)
{
    fprintf(out, "(\x1b[1;34m%s: %d\x1b[0m)", this->name.get(), value);
}


int Student::get_value() const 
{
    return value;
}
