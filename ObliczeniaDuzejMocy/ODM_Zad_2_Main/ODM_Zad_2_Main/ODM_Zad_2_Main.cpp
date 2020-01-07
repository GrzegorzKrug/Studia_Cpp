// ODM_Zad_2_Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <tbb/tbb.h>
#include <string.h>

using namespace std;
using namespace tbb;

float run_10_times(float (*ptr)())
{	
	const int N = 10;
	float sum_times = 0;
	float last;
	for (int i = 0; i < N; i++) {
		last = (*ptr)();
		sum_times += last;
		
	}	
	return sum_times / N;
}

float zad1_lambda()
{
	tick_count time0 = tick_count::now();
	tbb::parallel_invoke(
		[]() {
			for (int i = 0; i < 8; i++) {
				string text = "Hello TBB " + to_string(i) + "! ";
				std::cout << text;
			};
		},
		[]() {
			for (int i = 0; i < 8; i++) {
				string text = "Hello TBB " + to_string(i + 8) + "! ";
				std::cout << text;
			};
		}
		);
	tick_count time_end = tick_count::now();
	float duration = (time_end - time0).seconds();
	return duration;
}

//class PrintHello
//{
//public:
//	void operator() ()
//	{
//		for (int i = 0; i < 8; i++) {
//			string text = "Hello TBB " + to_string(i + 8) + "! ";
//			std::cout << text;
//		};
//	}
//
//};

int main()
{
	float(*ptr_zad1)() = &zad1_lambda;
	float time1_a = run_10_times(ptr_zad1);




}


