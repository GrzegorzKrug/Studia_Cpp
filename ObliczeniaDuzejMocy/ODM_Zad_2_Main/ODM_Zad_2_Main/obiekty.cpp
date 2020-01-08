#pragma once
#include <iostream>
#include <tbb/tbb.h>
#include <string.h>

#include "obiekty.h"

using namespace std;
using namespace tbb;

inline PrintHello& PrintHello::operator()() const
{
	for (int i = 0; i < 8; i++) {
		string text = "Hello TBB " + to_string(i + 8) + "! ";
		std::cout << text;
		//cout << i << endl;
	};
	//auto temp = this;
	//return this;
}


//inline void function_hello()
//{
//	for (int i = 0; i < 8; i++) {
//		string text = "Hello TBB " + to_string(i + 8) + "! ";
//		std::cout << text;
//	};
//}
