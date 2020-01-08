#include "zad1.h"
#include <iostream>
#include <tbb/tbb.h>
#include <string.h>

using namespace std;
using namespace tbb;

inline PrintHello& PrintHello::operator() ()
{
	for (int i = 0; i < 8; i++) {
		string text = "Hello TBB " + to_string(i + 8) + "! ";
		std::cout << text;
		//cout << i << endl;
	};
	return *this;
}

//float zad1_lambda()
//{
//	tick_count time0 = tick_count::now();
//	tbb::parallel_invoke(
//		[]() {
//			for (int i = 0; i < 8; i++) {
//				string text = "Hello TBB " + to_string(i) + "! ";
//				std::cout << text;
//			};
//		},
//		[]() {
//			for (int i = 0; i < 8; i++) {
//				string text = "Hello TBB " + to_string(i + 8) + "! ";
//				std::cout << text;
//			};
//		}
//		);
//	tick_count time_end = tick_count::now();
//
//	float duration = (time_end - time0).seconds();
//	return duration;
//}
//
//
//float zad1_klasa()
//{
//	PrintHello app1;
//	tick_count time0 = tick_count::now();
//	tbb::parallel_invoke(
//		app1,
//		app1
//	);
//	tick_count time_end = tick_count::now();
//
//	float duration = (time_end - time0).seconds();
//	return duration;
//}
//
//void function_hello()
//{
//	for (int i = 0; i < 8; i++) {
//		string text = "Hello TBB " + to_string(i + 8) + "! ";
//		std::cout << text;
//	};
//}
//
//float zad1_pointer_to_function()
//{
//	void (*fun_ptr)() = &function_hello;
//
//	tick_count time0 = tick_count::now();
//	tbb::parallel_invoke(
//		fun_ptr,
//		fun_ptr
//	);
//	tick_count time_end = tick_count::now();
//
//	float duration = (time_end - time0).seconds();
//	return duration;
//}