#pragma once
#include <assert.h>
#include <random>

template <class T, int ROWS, int COLS>
class SuperClass {
protected:
	T content[ROWS][COLS];
public:
	SuperClass() {
		std::cout << "Creating matrix with zeros" << std::endl;
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				content[i][j] = (T)(rand() % 20);
			}
		}
	}

	SuperClass(T x) {
		std::cout << "Creating matrix with defined numbers" << std::endl;
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				content[i][j] = x;
			}
		}
	}

	SuperClass(std::string txt) {
		if (txt == "EYE") {
			std::cout << "Creating EYE matrix" << std::endl;
			for (int i = 0; i < ROWS; i++) {
				for (int j = 0; j < COLS; j++) {
					if (i == j) content[i][j] = 1;
					else content[i][j] = 0;

				}
			}
		}
		else {
			SuperClass();
		}
	}

	~SuperClass() {
		delete content;
	}


	T getElement(int i, int j) const
	{
		assert(i >= 0 && i < ROWS);
		assert(j >= 0 && j < COLS);

		return content[i][j];
	}

	void setElement(int i, int j, T value)
	{
		assert(i >= 0 && i < ROWS);
		assert(j >= 0 && j < COLS);

		content[i][j] = value;
	}

	void printMatrix() {
		std::cout << "Matrix " << ROWS << " x " << COLS << "\n";
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				std::cout << this->getElement(i, j) << "   ";
			}
			std::cout << "\n";
		}
	}

	SuperClass& operator*(const SuperClass& other)
	{
		SuperClass* result = new SuperClass();
		for (int row = 0; row < ROWS; row++) {
			for (int col = 0; col < COLS; col++) {
				T temp = 0;
				for (int element = 0; element < ROWS; element++) {
					temp += this->getElement(row, element) * other.getElement(element, col);
				}
				result->setElement(row, col, temp);

			}
		}

		return *result;
	}

	SuperClass& operator+(const SuperClass& other)
	{
		SuperClass* result = new SuperClass();
		for (int row = 0; row < ROWS; row++) {
			for (int col = 0; col < COLS; col++) {
				T temp = (T)0;
				temp += this->getElement(row, col) + other.getElement(row, col);
				result->setElement(row, col, temp);

			}
		}

		return *result;
	}

	//	SuperClass& operator=(const SuperClass& other)
	//	{
	//		//std::cout << "\n Overloading '=' \n";
	//		delete this->content;
	//		this->content = other.content;
	//		return this;
	//	}
};