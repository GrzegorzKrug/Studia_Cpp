#include <iostream>
#include <tbb/tbb.h>
#include <string.h>
#include <random>
#include "Matrix.h"
#include <fstream>
//#include <locale>
//#include "zad1.pp"

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
	vector<int> my_vector;
	int min = 90000, max = 0, sum = 0;

	for (int i = 0; i < 100; i++)
		my_vector.push_back(rand());

	tick_count time0 = tick_count::now();
	//typedef blocked_range<vector<int>::iterator> range_type;

	sum = tbb::parallel_reduce(
		tbb::blocked_range<int>(0, (int)my_vector.size()),
		0,
		[&](tbb::blocked_range<int> r, int total)
		{
			for (int i = r.begin(); i < r.end(); i++)
			{
				if (min > my_vector[i])
					min = my_vector[i];

				if (max < my_vector[i])
					max = my_vector[i];
				//string text = "\nval: " + to_string(my_vector[i]);
				//cout << text;
				total += my_vector[i];
			}
			return total;
		},
		std::plus<int>());
	tick_count time_end = tick_count::now();

	cout << "\nSum: " << to_string(sum);
	cout << "\nMin: " << to_string(min);
	cout << "\nMax: " << to_string(max);
	float duration = (time_end - time0).seconds();
	return duration;
}

void multiply_for1(const Matrix& A, const Matrix& B, Matrix& Result, int threads_num)
{
	int row_A = 0,
		col_B = 0,
		element = 0,
		res = 0;


	for (row_A = 0; row_A < A.get_n(); row_A++)
	{
		for (col_B = 0; col_B < B.get_m(); col_B++)
		{
			res = 0;
			for (element = 0; element < A.get_m(); element++)
			{
				res += A.get_val(row_A, element) * B.get_val(element, col_B);
			}
			Result.set_val(row_A,
				col_B,
				res
			);
		}
	}
}

static float zad6_parallel_for()
{
	int size = 100;
	Matrix* A = new Matrix(size, size);
	Matrix* B = new Matrix(size, size);
	Matrix* Res = new Matrix(A->get_n(), B->get_m());

	A = new Matrix("matrices\\M" + std::to_string(size) + "_a");
	B = new Matrix("matrices\\M" + std::to_string(size) + "_a");

	tick_count time0 = tick_count::now();
	parallel_for(0, A->get_m(), 1,
		[&](int& row_A) {
			//string text = "\nrow: " + to_string(row_A);
			//cout << text;
			for (int col_B = 0; col_B < B->get_m(); col_B++)
			{
				int res = 0;
				for (int element = 0; element < A->get_m(); element++)
				{
					res += A->get_val(row_A, element) * B->get_val(element, col_B);
				}
				Res->set_val(row_A,
					col_B,
					res
				);
			}
		});
	tick_count time_end = tick_count::now();

	Res->writeToFile("tbb_test_result");
	float duration = (time_end - time0).seconds();
	return duration;
}

static float zad7_parallel_pipeline()
{
	//setlocale(LC_ALL, "polish.UTF-8");
	setlocale(LC_ALL, "polish");
	//locale::global(std::locale("polish"));
	string line;

	// Sequence 
	std::ifstream input_file;
	input_file.open("texts\\input.txt");

	std::ofstream sequence_OutputFile;
	sequence_OutputFile.open("texts\\SequenceResult.txt");


	while (getline(input_file, line))
	{
		size_t n = line.size() - 1;
		for (size_t i = 0; i < line.size() / 2; i++, n--)
			std::swap(line[i], line[n]);

		sequence_OutputFile << line << std::endl;
	}
	input_file.close();
	sequence_OutputFile.close();

	// TBB Parallel	
	input_file.open("texts\\input.txt");

	std::ofstream tbb_OutputFile;
	tbb_OutputFile.open("texts\\Tbb.txt");


	tick_count time0 = tick_count::now();

	parallel_pipeline(
		8,
		tbb::make_filter<void, std::string>(
			tbb::filter::serial_in_order,
			[&](tbb::flow_control& fc) -> std::string {
				if (!input_file)
					fc.stop();

				std::string input;
				std::getline(input_file, input);

				return input;
			}
			) &
		tbb::make_filter<std::string, std::string>(
			tbb::filter::parallel,
			[](std::string input) -> std::string {
				size_t n = input.size() - 1;
				for (size_t i = 0; i < input.size() / 2; i++, n--)
				{
					std::swap(input[i], input[n]);
				}
				return input;
			}
			) &
				tbb::make_filter<std::string, void>(
					tbb::filter::serial_in_order,
					[&](std::string input) -> void {
						tbb_OutputFile << input << std::endl;
					}
					)
				);

	tick_count time_end = tick_count::now();
	input_file.close();
	tbb_OutputFile.close();

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
	float time6 = zad6_parallel_for();
	float time7 = zad7_parallel_pipeline();
	cout << "\n\n" << " - - - - " << "\n\n";

	cout << "Time 1a: " << time1_a << endl;
	cout << "Time 1b: " << time1_b << endl;
	cout << "Time 1c: " << time1_c << endl;
	cout << "Time 2 : " << time2 << endl;
	cout << "Time 3 : " << time3 << endl;
	cout << "Time 4 : " << time4 << endl;
	cout << "Time 5 : " << time5 << endl;
	cout << "Time 6 : " << time6 << endl;
	cout << "Time 7 : " << time7 << endl;

	cout << "\n\n" << "End...";

	return 0;
}


