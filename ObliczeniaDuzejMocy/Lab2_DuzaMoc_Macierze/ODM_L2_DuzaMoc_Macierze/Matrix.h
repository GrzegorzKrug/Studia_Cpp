#pragma once
#include <string>

class Matrix
{
private: int m, n;
		 int* content;

public:

	// Create Empty matrix
	Matrix(int _n, int _m);

	// Create Matrix and read from file
	Matrix(std::string fileName);

	// Release memory
	~Matrix();

	void Matrix::writeToFile();

	int* get_content() { return content; };
	int get_m() const { return m; };
	int get_n() const { return n; };
	int get_val(int row, int col) const { return content[row * m + col]; };

	void set_val(int row, int col, int value) { content[row * m + col] = value; };
	void writeToFile(std::string fileName);
};

