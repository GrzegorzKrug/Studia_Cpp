#pragma once
#include "ABCD.h"
#include <utility> 

//class SuperMath : public A
//{
//public:
//	SuperMath() {
//		std::cout << "Creating Super Math";
//	}
//
//	virtual ~SuperMath() {
//		std::cout << "Removing Super Math";
//	}
//
//	SuperMath& operator=(const SuperMath& other) {
//
//	}
//
//	SuperMath& operator+=(const SuperMath& other) {
//
//	}
//};


inline A& A::operator=(const A& other)
{
	//std::cout << "\n Overloading '=' \n";
	this->ax = other.ax;
	this->ay = other.ay;
	return *this;
}

inline A& A::operator+=(const A& other)
{
	//std::cout << "\n Overloading '+=' \n";
	this->ax += (int)other.ax;
	this->ay += (int)other.ay;
}

inline A& A::operator+(const A& other)
{
	//std::cout << "\n Overloading '+' \n";
	A* result = new A();

	result->ax = this->ax + other.ax;
	result->ay = this->ay + other.ay;

	return *result;
}

inline A& A::operator-(const A& other)
{
	A* result = new A();

	result->ax = this->ax - other.ax;
	result->ay = this->ay - other.ay;

	return *result;
}
inline A& A::operator++()
{
	this->ax++;
	this->ay++;


	return *this;
}

inline A& A::operator++(int)
{
	++this->ax;
	++this->ay;

	return *this;
}

inline std::pair<bool, bool> A::operator>(const A& other)
{
	//std::cout << "> overloaded" << std::endl;
	return std::pair<bool, bool>(this->ax > other.ax, this->ay > other.ay);
}

inline std::pair<bool, bool> A::operator<(const A& other)
{
	//std::cout << "> overloaded" << std::endl;
	return std::pair<bool, bool>(this->ax < other.ax, this->ay < other.ay);
}

inline std::pair<bool, bool> A::operator==(const A& other)
{
	//std::cout << "> overloaded" << std::endl;
	return std::pair<bool, bool>(this->ax == other.ax, this->ay == other.ay);
}

inline std::pair<bool, bool> A::operator!=(const A& other)
{
	//std::cout << "> overloaded" << std::endl;
	return std::pair<bool, bool>(this->ax != other.ax, this->ay != other.ay);
}


inline int& A::operator[](size_t index)
{
	if (index > 1 | index < 0)
	{
		//std::cout << "Index error" << std::endl;
		throw std::invalid_argument("Index error, use index from range [0, 1]");
	}
	else if (index == 0)
	{
		return ax;
	}
	else
	{
		return ay;
	}
}

inline int A::operator()(int x)
{
	return ax * x + ay * x;
}

inline int A::operator()(int i, int j)
{
	return ax * i + ay * j;
}

//A& operator()(int ax, int ay);
//A& operator()(int ax);