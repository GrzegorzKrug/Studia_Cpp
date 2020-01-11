#include <iostream>
#include "ABCD.h"
#include "Base.h"
#include "Polimorph.h"
#include "NewMathClass.h"
#include "FuncTemplates.h"


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


void zad3_overload() {
	A a1(5, 3);
	A a2(4, 21);
	//A result = a1 + a2;
	std::cout << "A1    \t" << a1.ValuesToText() << std::endl;
	std::cout << "A2    \t" << a2.ValuesToText() << std::endl;
	std::cout << "a1+a2 \t" << (a1 + a2).ValuesToText() << std::endl;
	std::cout << "++a1  \t" << (++a1).ValuesToText() << std::endl;
	a1 = A(5, 3);
	std::cout << "a1++  \t" << (a1++).ValuesToText() << std::endl;
	a1 = A(5, 3);
	std::cout << "a1-a2 \t" << (a1 - a2).ValuesToText() << std::endl;

	std::cout << "a1<a2 \t(" << std::to_string((a1 < a2).first) << ", " << std::to_string((a1 < a2).second) << ")" << std::endl;
	std::cout << "a1>a2 \t(" << std::to_string((a1 > a2).first) << ", " << std::to_string((a1 > a2).second) << ")" << std::endl;
	std::cout << "a1==a2 \t(" << std::to_string((a1 == a2).first) << ", " << std::to_string((a1 == a2).second) << ")" << std::endl;
	std::cout << "a1!=a2 \t(" << std::to_string((a1 != a2).first) << ", " << std::to_string((a1 != a2).second) << ")" << std::endl;

	std::cout << "a1[0]  \t" << a1[0] << std::endl;

	std::cout << "a1(1)    \t" << a1(1) << std::endl;
	std::cout << "a1(2,3)  \t" << a1(2, 3) << std::endl;
}


void zad4_templates() {
	int numArr[] = { 10, 20, 30, 40, 50 };
	float numArr2[] = { 10, 20, 30, 40, 50 };
	int target = 20;
	int result = search(numArr, target);
	std::cout << "Result Int index: " << result << std::endl;

	result = search(numArr2, (float)30);
	std::cout << "Result Float index: " << result << std::endl;

	char znaki[] = "This is my sample text";
	result = search(znaki, 'e');	
	std::cout << "Result Char index: " << result << std::endl;

	std::string text = "This is my sample text";
	result = search(text, 'e');
	std::cout << "Result Strgin index: " << result << std::endl;
}

int main()
{
	std::cout << "\n\n = = = = Zad1 \n";
	zad1();

	std::cout << "\n\n = = = = Zad1 a \n";
	zad1_diamond();

	std::cout << "\n\n = = = = Zad2 \n";
	zad2();

	std::cout << "\n\n = = = = Zad3 \n";
	zad3_overload();

	std::cout << "\n\n = = = = Zad4 \n";
	zad4_templates();

	return 0;
}

