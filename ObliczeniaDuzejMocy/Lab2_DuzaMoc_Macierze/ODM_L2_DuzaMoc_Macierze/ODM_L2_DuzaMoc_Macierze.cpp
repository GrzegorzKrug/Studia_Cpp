// ODM_L2_DuzaMoc_Macierze.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.

#include <iostream>
#include <sstream>
#include <fstream>
//#include <vector>
#include <conio.h>
#include "Matrix.h"
#include <ctime>
//#include "Lab2Classes.h"



using namespace std;

int main()
{
	//CSVReader reader;
	//std::vector<std::vector<float>> matrixA = reader.getData("M100_a");
	//std::vector<std::vector<float>> matrixB = reader.getData("M100_b");

	Matrix* A = new Matrix("matrices\\M100_a");
	Matrix* B = new Matrix("matrices\\M100_b");
	Matrix* C = new Matrix(A->get_n(), A->get_m());

	if (A->get_m() == B->get_n())
	{
		std::cout << "Matrixes are ok." << std::endl;

		// -------------------------- Calculation Loop
		clock_t begin_time = clock();
		for (int row_A = 0; row_A < A->get_n(); row_A++)
		{
			//outputRow.clear();
			for (int col_B = 0; col_B < B->get_m(); col_B++)
			{

				//float result = 0;
				for (int element = 0; element < A->get_m(); element++)
				{
					//result += matrixA[i][k] * matrixB[k][j];
					int val = A->get_val(row_A, element) * B->get_val(element, col_B);
					int pre_val = C->get_val(row_A, col_B);
					//C->set_val(row_A, col_B, pre_val + val);
				}
				//outputRow.push_back(result);
			}
			//resultMatrix.push_back(outputRow);
		}
		clock_t end_time = clock();
		//	// -------------------- Display Result
		//	for (auto row : resultMatrix)
		//	{
		//		for (float num : row)
		//		{
		//			std::cout << num << ", ";
		//		}
		//		std::cout << std::endl;
		//	}
		A->writeToFile();
		cout << "Time elapsed: " << end_time - begin_time << " ms" << endl;
	}
	else
	{
		std::cout << "You can not multiply this" << std::endl;
	}

	//std::cout << "vector Len: " << dataCSV;
	std::cout << "End of excecution...";
	//_getch();
	return 0;
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
