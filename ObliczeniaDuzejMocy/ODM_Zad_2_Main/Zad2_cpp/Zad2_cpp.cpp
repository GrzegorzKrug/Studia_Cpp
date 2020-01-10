#include <iostream>
#include "ABCD.h"
#include "Base.h"
#include "Polimorph.h"


void zad1()
{
	std::cout << "new A: " << std::endl;
	A* a = new A(1, 2);

	std::cout << "\nnew B: " << std::endl;
	B* b = new B(2, 4, 6, 8);

	std::cout << "\nnew C: " << std::endl;
	C* c = new C(3, 6, 9, 12, 15, 18);

	std::cout << "\nnew D: " << std::endl;
	D* d = new D(1, 2, 3, 4, 5, 6, 7, 8);
	
	std::cout << "\ncopy A: " << std::endl;
	A a2(*a);

	std::cout << "\ncopy D: " << std::endl;
	D d2(*d);

	std::cout << "\ndelete A: " << std::endl;
	delete a;

	std::cout << "\ndelete B: " << std::endl;
	delete b;

	std::cout << "\ndelete C: " << std::endl;
	delete c;

	std::cout << "\ndelete D: " << std::endl;
	delete d;

	std::cout << "\ndelete stack variables: " << std::endl;
}

void zad1_diamond()
{
	//SuperDiamond diamond;
	Base* my_diamond = new SuperDiamond();

	my_diamond->PrintName();

	//std::cout << std::endl << "delete my_diamond:" << std::endl;
	delete my_diamond;


}

void zad2() 
{
	std::cout << "new Middle" << std::endl;

	Higher* my_higher = new Higher();
	std::cout << "\n Calling my_higher method Virtual: \n";
	my_higher->VirtualFunc();	
	std::cout << "\n Calling my_higher method Hello: \n";
	my_higher->Hello();	
	std::cout << "\n Calling my_higher method Master: \n";
	my_higher->Master();

	
	Best* my_best = new Best();	
	std::cout << "\n Calling my_best method Virtual: \n";
	my_best->VirtualFunc();
	std::cout << "\n Calling my_best method Hello: \n";
	my_best->Hello();	
	std::cout << "\n Calling my_best method Master: \n";
	my_best->Master();

	
	Abstract* abstract = new Best();
	std::cout << "\n Calling abstract method Hello: \n";
	abstract->Hello();
	
	std::cout << "\n Deleting my_higher: \n";
	delete my_higher;	
	std::cout << "\n Deleting my_best: \n";
	delete my_best;
	std::cout << "\n Deleting abstract: \n";
	delete abstract;
}

int main()
{
	std::cout << "\n\n = = = = Zad1 \n";
	zad1();

	std::cout << "\n\n = = = = Zad1a \n";
	zad1_diamond();

	std::cout << "\n\n = = = = Zad2 \n";
	zad2();

	return 0;
}