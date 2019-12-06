// ODM_L2_DuzaMoc_Macierze.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.

#include <iostream>
#include <sstream>
#include <fstream>
//#include <vector>
#include <conio.h>
#include "Matrix.h"
#include <ctime>
#include <omp.h>
//#include "Lab2Classes.h"

double multiply_seq(const Matrix& A, const Matrix& B, Matrix& result);
double multiply_for1(const Matrix& A, const Matrix& B, Matrix& result, int threads_num);
double multiply_for2(const Matrix& A, const Matrix& B, Matrix& result, int threads_num);
double multiply_for3(const Matrix& A, const Matrix& B, Matrix& result, int threads_num);
bool check_arrays(const Matrix& C, Matrix& Res);
using namespace std;

int main()
{
	//CSVReader reader;
	//std::vector<std::vector<float>> matrixA = reader.getData("M100_a");
	//std::vector<std::vector<float>> matrixB = reader.getData("M100_b");
	clock_t time0 = clock();
	Matrix* A = new Matrix("matrices\\M100_a");
	Matrix* B = new Matrix("matrices\\M100_b");
	Matrix* C = new Matrix(A->get_n(), B->get_m());
	Matrix* Res = new Matrix(A->get_n(), B->get_m());
	clock_t load_time = clock();
	std::cout << "Matrices loaded in " << load_time - time0 << " ms" << endl << endl;

	int ths_nums = 4;
	// -------------------------- Calculation Loop
	if (A->get_m() == B->get_n())
	{
		multiply_seq(*A, *B, *Res);
		multiply_for1(*A, *B, *C, ths_nums);

		check_arrays(*C, *Res);
		multiply_for2(*A, *B, *C, ths_nums);

		check_arrays(*C, *Res);

		multiply_for3(*A, *B, *C, ths_nums);
		check_arrays(*C, *Res);



		//multiply_for2(*A, *B, *C, ths_nums);
		//multiply_for3(*A, *B, *C, ths_nums);
		//C->writeToFile();
		Res->writeToFile();
	}
	else
	{
		std::cout << "You can not multiply this" << std::endl;
	}

	std::cout << "End of excecution...";
	//_getch();
	return 0;
}

bool check_arrays(const Matrix& C, Matrix& Res)
{
	for (int row = 0; row < Res.get_n(); row++)
	{
		for (int col = 0; col < Res.get_m(); col++)
		{
			if (!(C.get_val(row, col) == Res.get_val(row, col)))
			{
				std::cout << "\t" << C.get_val(row, col) << " != " << Res.get_val(row, col) << endl;
				return false;
			}
		}
	}
	std::cout << "\tGood" << endl;
	return true;
}

double multiply_seq(const Matrix& A, const Matrix& B, Matrix& result)
{
	int row_A = 0,
		col_B = 0,
		element = 0,
		res = 0;
	clock_t begin_time = clock();
	for (row_A = 0; row_A < A.get_n(); row_A++)
	{
		for (col_B = 0; col_B < B.get_m(); col_B++)
		{
			res = 0;
			for (element = 0; element < A.get_m(); element++)
			{
				res += A.get_val(row_A, element) * B.get_val(element, col_B);
			}
			result.set_val(row_A,
				col_B,
				res
			);
		}
	}
	clock_t end_time = clock();
	cout << "Sequential Multiply of " << A.get_m() << " x " << A.get_n()
		<< "\n\tThreads: " << "1"
		<< "\n\tTime elapsed: " << (double)(end_time - begin_time) / 1000 << " s" << endl;
	return end_time - begin_time;
}


double multiply_for1(const Matrix& A, const Matrix& B, Matrix& Result, int threads_num)
{
	int row_A = 0,
		col_B = 0,
		element = 0,
		res = 0;
	clock_t begin_time = clock();
	//omp_set_num_threads(threads_num);

	omp_set_num_threads(threads_num);
#pragma omp parallel shared(A, B, Result) private(row_A, col_B, element, res)
	{

#pragma omp for
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

	clock_t end_time = clock();
	cout << "First loop. Size: " << A.get_m() << " x " << A.get_n()
		<< "\n\tThreads: " << std::to_string(threads_num)
		<< "\n\tTime elapsed: " << (double)(end_time - begin_time) / 1000 << " s" << endl;
	return end_time - begin_time;
}

double multiply_for2(const Matrix& A, const Matrix& B, Matrix& Result, int threads_num)
{
	int row_A = 0,
		col_B = 0,
		element = 0,
		res = 0;
	clock_t begin_time = clock();
	omp_set_num_threads(threads_num);

	for (row_A = 0; row_A < A.get_n(); row_A++)
	{
#pragma omp parallel shared(A, B, row_A, Result) private(col_B, element, res)
		{
#pragma omp for
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

	clock_t end_time = clock();
	cout << "Second loop. Size: " << A.get_m() << " x " << A.get_n()
		<< "\n\tThreads: " << std::to_string(threads_num)
		<< "\n\tTime elapsed: " << (double)(end_time - begin_time) / 1000 << " s" << endl;
	return end_time - begin_time;
}

double multiply_for3(const Matrix& A, const Matrix& B, Matrix& Result, int threads_num)
{
	int row_A = 0,
		col_B = 0,
		element = 0,
		res = 0;
	clock_t begin_time = clock();
	//omp_set_num_threads(threads_num);

	omp_set_num_threads(threads_num);


	for (row_A = 0; row_A < A.get_n(); row_A++)
	{

		for (col_B = 0; col_B < B.get_m(); col_B++)
		{
			res = 0;
#pragma omp parallel shared(A, B, Result, res, row_A, col_B) private(element)
			{
#pragma omp for
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

	clock_t end_time = clock();
	cout << "Third loop. Size: " << A.get_m() << " x " << A.get_n()
		<< "\n\tThreads: " << std::to_string(threads_num)
		<< "\n\tTime elapsed: " << (double)(end_time - begin_time) / 1000 << " s" << endl;
	return end_time - begin_time;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
