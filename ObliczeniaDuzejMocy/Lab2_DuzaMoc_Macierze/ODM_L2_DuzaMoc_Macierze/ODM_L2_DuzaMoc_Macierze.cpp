// ODM_L2_DuzaMoc_Macierze.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Lab2Classes.h"

using namespace std;

int main()
{
	CSVReader reader;
	std::vector<std::vector<float>> matrixA = reader.getData("losowy_matrix.csv");
	std::vector<std::vector<float>> matrixB = reader.getData("losowy_matrix2.csv");

	if (matrixA[0].size() == matrixB.size())
	{
		std::cout << "Matrixes are ok." << std::endl;
		std::vector<std::vector<float>> resultMatrix;

	}
	else
	{
		std::cout << "You can not multiply this" << std::endl;
	}

	//std::cout << "vector Len: " << dataCSV;
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
