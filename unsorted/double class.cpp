#include <math.h>
#include <stdio.h>
#include <iostream>

int g_count = 0;
int g_maxcount = 0;

class number
{
	private:
		double num;

	public:

		number& operator++();
		number& operator--();

		number operator+ (const number& sec);
		number operator- (const number& sec);
		number operator* (const number& sec);
		number operator/ (const number& sec);

		number& operator+= (const number& sec);
		number& operator-= (const number& sec);
		number& operator*= (const number& sec);
		number& operator/= (const number& sec);

		number& operator= (const number& sec);

		bool operator< (const number& sec);
		bool operator<= (const number& sec);
		bool operator> (const number& sec);
		bool operator>= (const number& sec);
		bool operator== (const number& sec);
		bool operator!= (const number& sec);


		number (double a) : num (a)
		{
			printf ("%p \n %s", this, "был вызван конструктор с параметром \n");
			g_count++;
		}

		number() : num (0)
		{
			printf ("%p \n %s", this, "был вызван базовый конструктор \n");
			g_count++;
		}

		number (const number& sec) : num (sec.num)
		{
			printf ("%p \n %s", this, "был вызван конструктор копирования \n");
			g_count++;
		}

		~ number()
		{
			printf ("%p \n %s", this, "был вызван деструктор \n");

			if (g_count > g_maxcount)
			{
				g_maxcount = g_count;
			}

			g_count--;
		}
};




number number::operator+ (const number& sec)
{
	printf ("%s", "был вызван оператор сложения для объекта класса \n");
	return number (num + sec.num);
}

number number::operator- (const number& sec)
{
	printf ("%s", "был вызван оператор вычитания для объекта класса \n");
	return number (num - sec.num);
}

number number::operator* (const number& sec)
{
	printf ("%s", "был вызван оператор умножения для объекта класса \n");
	return number (num * sec.num);
}

number number::operator/ (const number& sec)
{
	printf ("%s", "был вызван оператор деления для объекта класса \n");
	return number (num + sec.num);
}





number& number::operator+= (const number& sec)
{
	printf ("%s", "был вызван оператор сложения-равно для объекта класса \n");
	(*this).num = sec.num + (*this).num;
	return *this;
}

number& number::operator-= (const number& sec)
{
	printf ("%s", "был вызван оператор вычитания-равно для объекта класса \n");
	(*this).num = sec.num + (*this).num;
	return *this;
}

number& number::operator*= (const number& sec)
{
	printf ("%s", "был вызван оператор умножения-равно для объекта класса \n");
	(*this).num = sec.num + (*this).num;
	return *this;
}

number& number::operator/= (const number& sec)
{
	printf ("%s", "был вызван оператор деления-равно для объекта класса \n");
	(*this).num = sec.num + (*this).num;
	return *this;
}



number& number::operator++ ()
{
	printf ("%s", "был вызван оператор инкремент для объекта класса \n");
	(*this).num++;
	return *this;
}

number& number::operator-- ()
{
	printf ("%s", "был вызван оператор декремент для объекта класса \n");
	(*this).num--;
	return *this;
}



number& number::operator= (const number& sec)
{
	printf ("%s", "был вызван оператор присваивания для объекта класса \n");
	(*this).num = sec.num;
	return *this;
}


bool number:: operator< (const number& sec)
{
    printf ("%s", "был вызван оператор сравнения < для объекта класса \n");
    return (num < sec.num);
}

bool number:: operator> (const number& sec)
{
    printf ("%s", "был вызван оператор сравнения > для объекта класса \n");
    return (num > sec.num);
}

bool number:: operator>= (const number& sec)
{
    printf ("%s", "был вызван оператор сравнения >= для объекта класса \n");
    return (num >= sec.num);
}

bool number:: operator<= (const number& sec)
{
    printf ("%s", "был вызван оператор сравнения <= для объекта класса \n");
    return (num <= sec.num);
}

bool number:: operator== (const number& sec)
{
    printf ("%s", "был вызван оператор сравнения == для объекта класса \n");
    return (num == sec.num);
}

bool number:: operator!= (const number& sec)
{
    printf ("%s", "был вызван оператор сравнения != для объекта класса \n");
    return (num != sec.num);
}


int main()
{
    setlocale(LC_ALL, "Russian");

    number a;
    number b = a + 3;

    number c = a / b + 8.5;

    printf ("%d \n%d \n", g_count, g_maxcount);

	return 0;
}
