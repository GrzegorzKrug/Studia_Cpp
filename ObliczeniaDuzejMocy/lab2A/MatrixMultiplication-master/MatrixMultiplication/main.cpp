#include <iostream>
#include <string>
#include <chrono>
#include <omp.h>
#include "Matrix.h"

Matrix* readFromFile(std::string matrixName);
void saveToFile(Matrix& matrix);
//void multiply(const Matrix& A, const Matrix& B, Matrix& result);

void multiply(const Matrix& A, const Matrix& B, Matrix& result)
{
	// check multiplication correctness condition
	if (A.getN() != B.getM())
	{
		std::cout << "Nie mo�na pomno�y� tych macierzy!" << std::endl;
		return;
	}

	// perform the multiplication
	int i = 0, j, k;
	//#pragma omp		
		//#pragma omp parallel shared(A, B, result) private(i, j, k)


	omp_set_num_threads(3);
#pragma omp parallel shared(i, j, k)
	{
		//#pragma omp for schedule()
		for (i = 0; i < A.getM(); i++)
		{

			for (j = 0; j < B.getN(); j++)
			{
				float temp = 0;
				for (k = 0; k < A.getN(); k++)
				{
					temp = temp + A.getAt(i, k) * B.getAt(k, j);
				}
				result.setAt(i, j, temp);
			}

			std::string textBuff;
			textBuff = std::to_string(omp_get_thread_num());
			/*textBuff = "Watek:" + textBuff + " i= " + std::to_string(i) + " K=" + std::to_string(k) + "\n";*/
			textBuff = "Watek:" + textBuff + " i= " + std::to_string(i) + "\n";
			std::cout << textBuff;

		}
	}
}


int main()
{
	// polish language support
	setlocale(LC_ALL, "polish");

	// read the matrices to multiply
	//Matrix *A = readFromFile("A");
	//Matrix *B = readFromFile("B");

	Matrix* A = new Matrix("matrix10a");
	Matrix* B = new Matrix("matrix10a");

	// prepare the result matrix
	Matrix* C = new Matrix(A->getN(), B->getM());

	// start time masurement
	auto startTime = std::chrono::system_clock::now();

	// multiply the matrices
	multiply(*A, *B, *C);

	// end time and time difference print
	auto endTime = std::chrono::system_clock::now();
	std::chrono::duration<double> time = endTime - startTime;
	std::cout << "Obliczenia zaj�y " << time.count() << "s." << std::endl;

	// save result to file
	saveToFile(*C);
	//C.writeToFile("output.csv")
	// free the memory
	delete A, B, C;

	// hold the screen
	std::cin.get();
	return 0;
}

Matrix* readFromFile(std::string matrixName)
{
	// get file name
	std::string fileName;
	std::cout << "Podaj nazw� pliku z macierz� " << matrixName << ": ";
	std::cin >> fileName;

	// create the matrix and return it
	Matrix* result = new Matrix(fileName);

	// success info
	std::cout << "Macierz " << matrixName << " zosta�a poprawnie wczytana." << std::endl;

	return result;
}

void saveToFile(Matrix& matrix)
{
	// get file name
	std::string fileName = "output.csv";
	//std::cout << "Podaj nazw� pliku wynikowego C = A * B: ";

	std::cin >> fileName;

	// save matrix to file
	matrix.writeToFile(fileName);
}


