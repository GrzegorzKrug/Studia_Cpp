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
	clock_t time0 = clock();
	Matrix* A = new Matrix("matrices\\M500_a");
	Matrix* B = new Matrix("matrices\\M500_b");
	Matrix* C = new Matrix(A->get_n(), A->get_m());
	clock_t load_time = clock();
	std::cout << "Matrices loaded in " << load_time - time0 << " ms" << endl;
	if (A->get_m() == B->get_n())
	{
		//std::cout << "Matrixes are ok." << std::endl;
		// -------------------------- Calculation Loop
		int row_A = 0, col_B = 0, element = 0;
		clock_t begin_time = clock();
		for (row_A = 0; row_A < A->get_n(); row_A++)
		{
			for (col_B = 0; col_B < B->get_m(); col_B++)
			{
				int res = 0;
				for (element = 0; element < A->get_m(); element++)
				{
					res += C->get_val(row_A, col_B) + A->get_val(row_A, element) * B->get_val(element, col_B);
				}
				C->set_val(row_A,
					col_B,
					res
				);
			}

		}
		clock_t end_time = clock();
		cout << "Time elapsed: " << end_time - begin_time << " ms" << endl;
		C->writeToFile();
	}
	else
	{
		std::cout << "You can not multiply this" << std::endl;
	}

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
