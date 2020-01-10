#pragma once
#include <iostream>


class Abstract {
public:
	Abstract() {
		std::cout << "Abstract created\n";
	}

	virtual ~Abstract() {
		std::cout << "Abstract removed\n";
	}

	virtual void VirtualFunc() = 0;
	virtual void Master() = 0;
	virtual void Hello() = 0;
};


class Higher : public Abstract
{

public:
	Higher()
	{
		std::cout << "Higher created" << std::endl;
	}

	virtual ~Higher()
	{
		std::cout << "Higher deleted" << std::endl;
	}

	void VirtualFunc() override
	{
		std::cout << "Higher virtual function" << std::endl;
	}

	virtual void Hello()
	{
		std::cout << "Hello virtual function" << std::endl;
	}

	void Master() final override
	{
		std::cout << "Final function in Higher class" << std::endl;
	}
};


class Best final : public Higher
{
public:
	Best()
	{
		std::cout << "Final created" << std::endl;
	}

	virtual ~Best()
	{
		std::cout << "Final deleted" << std::endl;
	}

	void Hello() final override
	{
		std::cout << "Hello from Best Final class" << std::endl;
	}

};