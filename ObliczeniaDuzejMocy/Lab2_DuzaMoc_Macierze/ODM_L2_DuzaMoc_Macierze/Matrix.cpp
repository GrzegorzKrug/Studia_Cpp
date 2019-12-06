#include <iostream>
#include <fstream>
#include "Matrix.h"

Matrix::Matrix(int _m, int _n) : m(_m), n(_n)
{
	content = new int[m * n];
}

Matrix::Matrix(std::string filename)
{
	std::ifstream file;
	file.open(filename, std::ifstream::in);
	file >> n >> m; // N -> Rows, M -> Cols

	content = new int[m * n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			file >> content[i * m + j];
		}
}

Matrix::~Matrix()
{
	// free all the memory
	delete[] content;
}

void Matrix::writeToFile()
{
	// open the file
	std::ofstream file;
	file.open("Result_Matrix", std::ofstream::out);

	// save the dimentions
	file << m << " " << n << std::endl;

	// save the content
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			file << content[i * m + j] << " ";
		}
		file << std::endl;
	}

	// close the file
	file.close();
}