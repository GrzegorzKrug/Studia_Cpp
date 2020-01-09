#include <iostream>
#include <tbb/tbb.h>
#include <string.h>
#include <random>

//#include "zad1.cpp"

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

class PrintHello
{
public:
	void operator() () const
	{
		for (int i = 0; i < 8; i++) {
			string text = "Hello TBB " + to_string(i + 8) + "! ";
			std::cout << text;
		};
	}

};

static float zad1_lambda()
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


static float zad1_klasa()
{
	PrintHello app1;
	tick_count time0 = tick_count::now();
	tbb::parallel_invoke(
		app1,
		app1
	);
	tick_count time_end = tick_count::now();

	float duration = (time_end - time0).seconds();
	return duration;
}


static void function_hello()
{
	for (int i = 0; i < 8; i++) {
		string text = "Hello TBB " + to_string(i + 8) + "! ";
		std::cout << text;
	};
}


static float zad1_pointer_to_function()
{
	void (*fun_ptr)() = &function_hello;

	tick_count time0 = tick_count::now();
	tbb::parallel_invoke(
		fun_ptr,
		fun_ptr
	);
	tick_count time_end = tick_count::now();

	float duration = (time_end - time0).seconds();
	return duration;
}


static float zad2_parallel_foreach()
{
	vector<int> my_vec;
	for (int i = 0; i < 100; i++)
		my_vec.push_back(rand());

	tick_count time0 = tick_count::now();
	parallel_for_each(my_vec.begin(), my_vec.end(),
		[&](int& i) {
			string text = "For each: " + to_string(i) + "\n";
			std::cout << text;
		});
	tick_count time_end = tick_count::now();

	float duration = (time_end - time0).seconds();
	return duration;
}


static float zad3_parallel_for()
{
	vector<int> my_vec;
	for (int i = 0; i < 100; i++)
		my_vec.push_back(rand());

	tick_count time0 = tick_count::now();

	tick_count time_end = tick_count::now();

	float duration = (time_end - time0).seconds();
	return duration;
}

void main()
{
	PrintHello pr1;
	pr1();
	//float(*ptr_zad1_a)() = &zad1_lambda;
	//float time1_a = run_10_times(ptr_zad1_a);

	float time1_a = zad1_lambda();

	float time1_b = zad1_klasa();

	float time1_c = zad1_pointer_to_function();
	float time2 = zad2_parallel_foreach();
	float time3 = zad3_parallel_for();


	cout << "\n\n" << "...";

	cout << "\n\n" << "End...";
}


