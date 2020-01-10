#pragma once

#include <iostream>

class Base
{
public:
	Base()
	{
		std::cout << "Base created" << std::endl;
	}

	virtual ~Base()
	{
		std::cout << "Base deleted" << std::endl;
	}

	virtual void PrintName()
	{
		std::cout << "Base method" << std::endl;
	}
};

class Derived1 : public virtual Base
{
public:
	Derived1()
	{
		std::cout << "Derived 1 created" << std::endl;
	}

	virtual ~Derived1()
	{
		std::cout << "Derived 1 deleted" << std::endl;
	}
};


class Derived2 : public virtual Base
{
public:
	Derived2()
	{
		std::cout << "Derived 2 created" << std::endl;
	}

	virtual ~Derived2()
	{
		std::cout << "Derived 2 deleted" << std::endl;
	}
};


class SuperDiamond : public Derived1, Derived2
{
public:
	SuperDiamond()
	{
		std::cout << "SuperDiamond created" << std::endl;
	}

	virtual ~SuperDiamond()
	{
		std::cout << "SuperDiamond deleted" << std::endl;
	}

	void PrintName() override
	{
		std::cout << "SuperDiamond print method" << std::endl;
	}
};
