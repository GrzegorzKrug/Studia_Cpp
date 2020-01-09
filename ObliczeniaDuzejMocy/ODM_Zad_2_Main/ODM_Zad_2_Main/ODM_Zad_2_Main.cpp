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
			string text = "TBB2 For each: " + to_string(i) + "\n";
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
	parallel_for(2, 101, 2,
		[&](int& i) {
			string text = "TBB3 For: " + to_string(i) + "\n";
			std::cout << text;
		});
	tick_count time_end = tick_count::now();

	float duration = (time_end - time0).seconds();
	return duration;
}


bool is_prime(int n) {
	if (n < 2) {
		return false;
	}

	int i = 2;
	while (i * i <= n) {
		if (n % i == 0) {
			return false;
		}
		i += 1;
	}
	return true;
}

static float zad4_parallel_do()
{
	list<pair<int, bool>> my_list;
	list<int> good_vec;

	for (int i = 0; i < 100; i++)
		my_list.push_back(pair<int, bool>(rand(), false));

	tick_count time0 = tick_count::now();
	parallel_do(my_list,
		[](list<pair<int, bool>> ::reference element) {
			if (is_prime(element.first)) {
				//string text = "Prime:     " + to_string(element.first) + "\n";
				//cout << text;
				element.second = true;
			};
		}
	);
	tick_count time_end = tick_count::now();

	for (pair<int, bool>element : my_list) {
		if (element.second == true) {
			good_vec.push_back(element.first);
			//string text = "Prime:     " + to_string(element.first) + "\n";
			//cout << text;
		}
	}

	good_vec.sort();

	for (int element : good_vec) {
		cout << "TBB4 Sorted prime: " << to_string(element) << "\n";
	}

	float duration = (time_end - time0).seconds();
	return duration;
}

static float zad5_parallel_reduce()
{
	vector<int> my_list;
	int sum = 0;

	for (int i = 0; i < 100; i++)
		my_list.push_back(rand());

	tick_count time0 = tick_count::now();
	typedef blocked_range<vector<int>::iterator> range_type;

	sum = parallel_reduce(range_type(my_list.begin(), my_list.end()), 0,
		[](range_type const& r, int init) {
			//return accumulate(r.begin(), r.end(), init);
			string text = "reduce: " + to_string(init) + "\n";
			cout << text;
			/*for (int i = r.begin(); i < r.end(); ++i)
			{
				running_total += values[i];
			}*/
			return init;
		},
		plus<int>());
	tick_count time_end = tick_count::now();
	cout << "\nSum: " << to_string(sum);
	float duration = (time_end - time0).seconds();
	return duration;
}

int main()
{
	//PrintHello pr1;
	//pr1();
	//float(*ptr_zad1_a)() = &zad1_lambda;
	//float time1_a = run_10_times(ptr_zad1_a);

	float time1_a = zad1_lambda();

	float time1_b = zad1_klasa();

	float time1_c = zad1_pointer_to_function();
	float time2 = zad2_parallel_foreach();
	float time3 = zad3_parallel_for();
	float time4 = zad4_parallel_do();
	float time5 = zad5_parallel_reduce();

	cout << "\n\n" << " - - - - " << "\n\n";

	cout << "Time 1a: " << time1_a << endl;
	cout << "Time 1b: " << time1_b << endl;
	cout << "Time 1c: " << time1_c << endl;
	cout << "Time 2:  " << time2 << endl;
	cout << "Time 3:  " << time3 << endl;
	cout << "Time 4:  " << time4 << endl;
	cout << "Time 5:  " << time5 << endl;

	cout << "\n\n" << "End...";

	return 0;
}


