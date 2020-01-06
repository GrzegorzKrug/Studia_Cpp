// ODM_Zad_2_Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <tbb/tbb.h>
#include <string.h>

using namespace std;

int main()
{
	using namespace tbb;
	//std::cout << "Hello World!\n";
	tick_count time0 = tick_count::now();
	tbb::parallel_invoke(
		[]() {std::cout << "Hello TBB!"; },
		[]() {std::cout << "Hello TBB!"; }
	);

	tick_count time_end = tick_count::now();
	std::cout << "\nTime elapsed: " << (time_end - time0).seconds()/1000 << " ms";


}



//class ClassA
//{
//public:
//	string name = "Klasa_A";
//	int a = 5;
//	int b = 10;
//
//};


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file