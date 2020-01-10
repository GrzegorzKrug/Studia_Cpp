#pragma once
#include <iostream>
#include <cmath>

class A
{
public:
	int ax;
protected:
	int ay;

public:
	int Add() { return ax + ay; }
	int Multiply() { return ax * ay; }

public:
	A()
	{
		ax = 0;
		ay = 0;

		std::cout << "A created" << std::endl;
	}

	A(int x, int y)
	{
		ax = x;
		ay = y;

		std::cout << "A created" << std::endl;
	}

	virtual ~A()
	{
		std::cout << "A deleted" << std::endl;
	}

	A(const A& a)
	{
		ax = a.ax;
		ay = a.ay;

		std::cout << "A copied" << std::endl;
	}
};


class B : public A
{
public:
	int bx;
protected:
	int by;

public:
	int Substract() { return bx - by; }
	int Divide() { return bx / by; }

public:
	B()
	{
		bx = 0;
		by = 0;

		std::cout << "B created" << std::endl;
	}

	B(int ax, int ay, int x, int y) : A(ax, ay)
	{
		bx = x;
		by = y;

		std::cout << "B created" << std::endl;
	}

	virtual ~B()
	{
		std::cout << "B deleted" << std::endl;
	}

	B(const B& b) : A(b)
	{
		bx = b.bx;
		by = b.by;

		std::cout << "B copied" << std::endl;
	}
};


class C : protected B
{
public:
	int cx;
protected:
	int cy;

public:
	int Mod() { return cx % cy; }
	int Square() { return cx * cx; }

public:
	C()
	{
		cx = 0;
		cy = 0;

		std::cout << "C created" << std::endl;
	}

	C(int ax, int ay, int bx, int by, int x, int y) : B(ax, ay, bx, by)
	{
		cx = x;
		cy = y;

		std::cout << "C created" << std::endl;
	}

	virtual ~C()
	{
		std::cout << "C deleted" << std::endl;
	}

	C(const C& c) : B(c)
	{
		cx = c.cx;
		cy = c.cy;

		std::cout << "C copied" << std::endl;
	}
};


class D : private C
{
public:
	int dx;
private:
	int dy;
	int* tab;

public:
	int Avg() { return (ax + ay + bx + by + cx + cy) / 6; }
	int Sqrt() { return (int)sqrt(dx); }

public:
	D()
	{
		dx = 0;
		dy = 0;
		tab = new int[10];

		std::cout << "D created" << std::endl;
	}

	D(int ax, int ay, int bx, int by, int cx, int cy, int x, int y)
		: C(ax, ay, bx, by, cx, cy)
	{
		dx = x;
		dy = y;
		tab = new int[10];

		std::cout << "D created" << std::endl;
	}

	~D()
	{
		std::cout << "D deleted" << std::endl;
	}

	D(const D& d) : C(d)
	{
		dx = d.dx;
		dy = d.dy;
		delete tab;

		std::cout << "D copied" << std::endl;
	}
};

