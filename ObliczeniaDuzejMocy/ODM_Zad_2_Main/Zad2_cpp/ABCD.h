#pragma once
#include <iostream>
#include <cmath>

class A {
public:
	int ax;
protected:
	int ay;

public:
	int Add() {
		return ax + ay;
	}
	int Multiply() {
		return ax * ay;
	}

	A() {
		ax = 0;
		ay = 0;
		std::cout << "Created A empty" << std::endl;
	}

	A(int x, int y) {
		ax = x;
		ay = y;
		std::cout << "Created A" << std::endl;
	}

	virtual ~A() {
		std::cout << "A deleted\n";
	}

	A(const A& a) {
		ax = a.ax;
		ay = a.ay;
	}
};

class B : public A {
public:
	int bx;
protected:
	int by;

public:
	int Substract() {
		return bx - by;
	}
	int Divide() {
		return bx / by;
	}

	B()
	{
		bx = 0;
		by = 0;

		std::cout << "Created B empty" << std::endl;
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

class C : protected B {
public:
	int cx;
protected:
	int cy;

public:
	bool IsBigger() {
		return cx > cy;
	}
	bool IsSmaller() {
		return cx < cy;
	}

	C() {
		cx = 0;
		cy = 0;
		std::cout << "Created C empty" << std::endl;
	}

	C(int ax, int ay, int bx, int by, int x, int y) : B(ax, ay, bx, by)
	{
		cx = x;
		cy = y;

		std::cout << "C created" << std::endl;
	}

	virtual ~C() {

	}

	C(const C& c) : B(c) {
		cx = c.cx;
		cy = c.cy;
	}

};

class D : private C {
public:
	int dx;
protected:
	int dy;

public:
	int Sum() {
		return ax + ay + bx + by + cx + cy + dx + dy;
	}
	int MultiplyAll() {
		return ax * ay * bx * by * cx * cy * dx * dy;
	}

	D() {
		dx = 0;
		dy = 0;
		std::cout << "Created D empty" << std::endl;
	}

	D(int ax, int ay, int bx, int by, int cx, int cy, int x, int y)
		: C(ax, ay, bx, by, cx, cy)
	{
		dx = x;
		dy = y;
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

		std::cout << "D copied" << std::endl;
	}
};