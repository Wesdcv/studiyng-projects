#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include "TXlib.h"


int depth = 0;


class Depth {

public:
	Depth()
	{
		depth++;
	}

	~Depth()
	{
		depth--;
	}
};


class Number {
public:
	double value_;

	static int* count_obj (const int deltha = 0) {
		static int count_current = 0;
		static int count_max = 0;
		count_current += deltha;
		if (deltha == 1)
			count_max++;
		static int counter[2];
		counter[0] = count_current;
		counter[1] = count_max;
		return counter;
	}


	friend Number operator +  (const Number& x, const Number& y);
	friend Number operator -  (const Number& x, const Number& y);
	friend Number operator *  (const Number& x, const Number& y);
	friend Number operator /  (const Number& x, const Number& y);
	friend bool   operator <  (const Number& x, const Number& y);
	friend bool   operator <= (const Number& x, const Number& y);
	friend bool   operator >  (const Number& x, const Number& y);
	friend bool   operator >= (const Number& x, const Number& y);
	friend bool   operator == (const Number& x, const Number& y);
	friend bool   operator != (const Number& x, const Number& y);
	friend Number operator && (const Number& x, const Number& y);
	friend Number operator || (const Number& x, const Number& y);
	friend Number operator !  (const Number& x);
	friend Number operator ++ (Number& x);
	friend Number operator ++ (Number& x, int);
	friend Number operator -- (Number& x);
	friend Number operator -- (Number& x, int);


	void operator += (Number x) {
		Depth dep;
		printf("%s", "unary addition\n\n");
		printf("%*s", depth * 10, "");
		printf("%s", "{\n\n");
		printf("%*s", depth * 10, "");
		printf("%s", "}\n\n");

		(*this).value_ = (*this).value_ + x.value_;
	}

	void operator -= (Number x) {
		Depth dep;
		printf("%s", "unary subtraction\n\n");
		printf("%*s", depth * 10, "");
		printf("%s", "{\n\n");
		printf("%*s", depth * 10, "");
		printf("%s", "}\n\n");

		(*this).value_ = (*this).value_ - x.value_;
	}

	void operator *= (Number x) {
		Depth dep;
		printf("%s", "unary multiplication\n\n");
		printf("%*s", depth * 10, "");
		printf("%s", "{\n\n");
		printf("%*s", depth * 10, "");
		printf("%s", "}\n\n");

		(*this).value_ = (*this).value_ * x.value_;
	}

	void operator /= (Number x) {
		Depth dep;
		printf("%s", "unary division\n\n");
		printf("%*s", depth * 10, "");
		printf("%s", "{\n\n");
		printf("%*s", depth * 10, "");
		printf("%s", "}\n\n");

		(*this).value_ = (*this).value_ / x.value_;
	}

	void operator =  (Number x) {
		Depth dep;
		printf("%s", "assignment\n\n");
		printf("%*s", depth * 10, "");
		printf("%s", "{\n\n");
		printf("%*s", depth * 10, "");
		printf("%s", "}\n\n");

		(*this).value_ = x.value_;
	}

	Number(double value) :
		value_(value)
	{
		Depth dep;
        count_obj(1);
        txSetConsoleAttr(size_t(this) & 0xFF);
        printf("%*s", depth * 10, "");
        printf("[%p] %s %d%s%.2f\n\n", this, "constructor with parameters, current number of objects :", count_obj()[0], ", value == ", value_);
        txSetConsoleAttr(7);
	}

	Number(const Number& num) :
        value_(num.value_)
    {
		Depth dep;
		count_obj(1);
		txSetConsoleAttr(size_t(this) & 0xFF);
		printf("%*s", depth * 10, "");
		printf("[%p] %s %d%s%.2f\n\n", this, "           copy constructor, current number of objects :" , count_obj()[0], ", value == ", value_);
		txSetConsoleAttr(7);

    }

	Number():
		value_(NULL)
	{
		Depth dep;
		count_obj(1);
		txSetConsoleAttr(size_t(this) & 0xFF);
		printf("%*s", depth * 10, "");
		printf("[%p] %s %d%s%.2f\n\n", this, "        default constructor, current number of objects :", count_obj()[0], ", value == ", value_);
		txSetConsoleAttr(7);
	}

	~Number() {
		Depth dep;
		count_obj(-1);
		txSetConsoleAttr(size_t(this) & 0xFF);
		printf("%*s", depth * 10, "");
		printf("[%p] %s %d%s%.2f\n\n", this, "                 destructor, current number of objects :", count_obj()[0], ", value == ", value_);
		txSetConsoleAttr(7);

		value_ = NULL;
	}
};


Number ret_same(const Number& x);


int main() {
	Depth dep;
    printf("%s", "main\n\n");
    printf("%*s", depth * 10, "");
    printf("%s", "{\n\n");


	Number a = 7;
	Number c = ret_same(a + 10);


	printf("%s%d\n\n", "max number of objects: ", Number::count_obj()[1]);
	printf("%*s", depth * 10, "");
    printf("%s", "}\n\n");
}


Number ret_same(const Number& x) {
	Depth dep;
	printf("%s", "ret_same\n\n");
    printf("%*s", depth * 10, "");
    printf("%s", "{\n\n");

	Number A (x);

	printf("%*s", depth * 10, "");
    printf("%s", "}\n\n");

	return A;
}


Number operator + (const Number& x, const Number& y) {
	Depth dep;
	printf("%s", "addition\n\n");
    printf("%*s", depth * 10, "");
    printf("%s", "{\n\n");

	Number sum (x.value_ + y.value_);

	printf("%*s", depth * 10, "");
    printf("%s", "}\n\n");
	return sum;
}


Number operator - (const Number& x, const Number& y) {
	Depth dep;
	printf("%s", "subtraction\n\n");
    printf("%*s", depth * 10, "");
    printf("%s", "{\n\n");

	Number a (x.value_ - y.value_);

	printf("%*s", depth * 10, "");
    printf("%s", "}\n\n");
	return a;
}


Number operator * (const Number& x, const Number& y) {
	Depth dep;
	printf("%s", "multiplication\n\n");
    printf("%*s", depth * 10, "");
    printf("%s", "{\n\n");

	Number a (x.value_ * y.value_);

	printf("%*s", depth * 10, "");
    printf("%s", "}\n\n");
	return a;
}


Number operator / (const Number& x, const Number& y) {
	Depth dep;
	printf("%s", "division\n\n");
    printf("%*s", depth * 10, "");
    printf("%s", "{\n\n");

	Number a (x.value_ / y.value_);

	printf("%*s", depth * 10, "");
    printf("%s", "}\n\n");
	return a;
}


bool operator < (const Number& x, const Number& y) {
	Depth dep;
	printf("%s", "less\n\n");
    printf("%*s", depth * 10, "");
    printf("%s", "{\n\n");
	printf("%*s", depth * 10, "");
    printf("%s", "}\n\n");

	return x.value_ < y.value_ ? true : false;
}


bool operator <= (const Number& x, const Number& y) {
	Depth dep;
	printf("%s", "less or equal\n\n");
    printf("%*s", depth * 10, "");
    printf("%s", "{\n\n");
	printf("%*s", depth * 10, "");
    printf("%s", "}\n\n");

	return x.value_ <= y.value_ ? true : false;
}


bool operator > (const Number& x, const Number& y) {
	Depth dep;
	printf("%s", "more\n\n");
    printf("%*s", depth * 10, "");
    printf("%s", "{\n\n");
	printf("%*s", depth * 10, "");
    printf("%s", "}\n\n");

	return x.value_ > y.value_ ? true : false;
}


bool operator >= (const Number& x, const Number& y) {
	Depth dep;
	printf("%s", "more or equal\n\n");
    printf("%*s", depth * 10, "");
    printf("%s", "{\n\n");
	printf("%*s", depth * 10, "");
    printf("%s", "}\n\n");

	return x.value_ >= y.value_ ? true : false;
}


bool operator == (const Number& x, const Number& y) {
	Depth dep;
	printf("%s", "equal\n\n");
    printf("%*s", depth * 10, "");
    printf("%s", "{\n\n");
	printf("%*s", depth * 10, "");
    printf("%s", "}\n\n");

	return x.value_ == y.value_ ? true : false;
}


bool operator != (const Number& x, const Number& y) {
	Depth dep;
	printf("%s", "not equal\n\n");
    printf("%*s", depth * 10, "");
    printf("%s", "{\n\n");
	printf("%*s", depth * 10, "");
    printf("%s", "}\n\n");

	return x.value_ != y.value_ ? true : false;
}


Number operator && (const Number& x, const Number& y) {
	Depth dep;
	printf("%s", "logical and\n\n");
    printf("%*s", depth * 10, "");
    printf("%s", "{\n\n");

	Number a (x.value_ && y.value_);

	printf("%*s", depth * 10, "");
    printf("%s", "}\n\n");
	return a;
}


Number operator || (const Number& x, const Number& y) {
	Depth dep;
	printf("%s", "logical or\n\n");
    printf("%*s", depth * 10, "");
    printf("%s", "{\n\n");

	Number a (x.value_ || y.value_);

	printf("%*s", depth * 10, "");
    printf("%s", "}\n\n");
	return a;
}


Number operator ! (const Number& x) {
	Depth dep;
	printf("%s", "logical or\n\n");
    printf("%*s", depth * 10, "");
    printf("%s", "{\n\n");

	Number a (!x.value_);

	printf("%*s", depth * 10, "");
    printf("%s", "}\n\n");
	return a;
}


Number operator ++ (Number& x) {
	Depth dep;
	printf("%s", "prefix increment\n\n");
    printf("%*s", depth * 10, "");
    printf("%s", "{\n\n");
	printf("%*s", depth * 10, "");
    printf("%s", "}\n\n");

	x.value_++;
	return x;
}


Number operator ++ (Number& x, int) {
	Depth dep;
	printf("%s", "postfix increment\n\n");
    printf("%*s", depth * 10, "");
    printf("%s", "{\n\n");

	Number old_value(x.value_);
	x.value_++;

	printf("%*s", depth * 10, "");
    printf("%s", "}\n\n");
	return old_value;
}


Number operator -- (Number& x) {
	Depth dep;
	printf("%s", "prefix decrement\n\n");
    printf("%*s", depth * 10, "");
    printf("%s", "{\n\n");
	printf("%*s", depth * 10, "");
    printf("%s", "}\n\n");

	x.value_--;
	return x;
}


Number operator -- (Number& x, int) {
	Depth dep;
	printf("%s", "postfix decrement\n\n");
    printf("%*s", depth * 10, "");
    printf("%s", "{\n\n");

	Number old_value(x.value_);
	x.value_--;

	printf("%*s", depth * 10, "");
    printf("%s", "}\n\n");
	return old_value;
}
