// ODM_L2_DuzaMoc_Macierze.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.

#include <iostream>
#include <sstream>
#include <fstream>
//#include <vector>
#include <conio.h>
#include "Matrix.h"
#include <ctime>
//#include "Lab2Classes.h"

double multiply_seq(const Matrix& A, const Matrix& B, Matrix& result);
double multiply_for1(const Matrix& A, const Matrix& B, Matrix& result, int threads_num);
double multiply_for2(const Matrix& A, const Matrix& B, Matrix& result, int threads_num);
double multiply_for3(const Matrix& A, const Matrix& B, Matrix& result, int threads_num);

using namespace std;

int main()
{
	//CSVReader reader;
	//std::vector<std::vector<float>> matrixA = reader.getData("M100_a");
	//std::vector<std::vector<float>> matrixB = reader.getData("M100_b");
	clock_t time0 = clock();
	Matrix* A = new Matrix("matrices\\M1000_a");
	Matrix* B = new Matrix("matrices\\M1000_b");
	Matrix* C = new Matrix(A->get_n(), A->get_m());
	Matrix* Res = new Matrix(A->get_n(), A->get_m());
	clock_t load_time = clock();
	std::cout << "Matrices loaded in " << load_time - time0 << " ms" << endl << endl;
	if (A->get_m() == B->get_n())
	{
		//std::cout << "Matrixes are ok." << std::endl;
		// -------------------------- Calculation Loop
		multiply_seq(*A, *B, *Res);
		multiply_for1(*A, *B, *C, 4);
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
				res += result.get_val(row_A, col_B) + A.get_val(row_A, element) * B.get_val(element, col_B);
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


double multiply_for1(const Matrix& A, const Matrix& B, Matrix& result, int threads_num)
{
	int row_A = 0,
		col_B = 0,
		element = 0,
		res = 0;
	clock_t begin_time = clock();
#pragma omp parallel
	{
		for (row_A = 0; row_A < A.get_n(); row_A++)
		{
			for (col_B = 0; col_B < B.get_m(); col_B++)
			{
				res = 0;
				for (element = 0; element < A.get_m(); element++)
				{
					res += result.get_val(row_A, col_B) + A.get_val(row_A, element) * B.get_val(element, col_B);
				}
				result.set_val(row_A,
					col_B,
					res
				);
			}
		}
	}
	clock_t end_time = clock();
	cout << "Paraller first loop. Size: " << A.get_m() << " x " << A.get_n()
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
