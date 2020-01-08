

#include <iostream>
#include <tbb/tbb.h>
#include <string.h>

#include "zad1.cpp"
//#include "obiekty.cpp"

using namespace std;
using namespace tbb;

//float run_10_times(float (*ptr)())
//{
//	const int N = 10;
//	float sum_times = 0;
//	float last;
//	for (int i = 0; i < N; i++) {
//		last = (*ptr)();
//		sum_times += last;
//
//	}
//	return sum_times / N;
//}
//
//
//
//float zad2_parallel_foreach()
//{
//	//void (*fun_ptr)() = &function_hello;
//
//	tick_count time0 = tick_count::now();
//	/*tbb::parallel_invoke(
//		,
//		
//	);*/
//	tick_count time_end = tick_count::now();
//
//	float duration = (time_end - time0).seconds();
//	return duration;
//}

int main()
{
	//PrintHello pr1;
	//pr1();
	//zad1_lambda();

	//float(*ptr_zad1_a)() = &zad1_lambda;
	//float time1_a = run_10_times(ptr_zad1_a);
	float time1_a = zad1_lambda();

	//float(*ptr_zad1_b)() = &zad1_klasa;	
	//float time1_a = run_10_times(ptr_zad1_b); // To nie dzia³a
	//float time1_b = zad1_klasa();
	

	//float time1_c = zad1_pointer_to_function();



}


