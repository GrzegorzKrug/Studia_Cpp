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

};


class Higher : Abstract
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
		std::cout << "Final function in middle class" << std::endl;
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

	void Hello() override
	{
		std::cout << "Hello Final" << std::endl;
	}

};