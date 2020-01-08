#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <assert.h>
#pragma once

class CSVReader
{
	std::string fileName;
	std::string delimeter;

public:
	CSVReader(std::string delm = ",") :
		delimeter(delm)
	{ }

	// Function to fetch data from a CSV File
	std::vector<std::vector<float>> getData(std::string fileName);
};

std::vector<std::vector<float>> CSVReader::getData(std::string fileName)
{
	//std::cout << "Open file: " << fileName;
	std::ifstream file(fileName);
	std::vector<std::vector<std::string>> dataList;
	std::string line = "";
	std::vector<std::vector<float>> numMatrix;

	while (getline(file, line))
	{
		std::vector<std::string> vec;
		boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
		dataList.push_back(vec);
	}
	file.close();

	std::vector<std::string> row = dataList[0];
	int rows = std::stoi(row[0]);
	int cols = std::stoi(row[1]);
	std::cout << "Loaded Matrix: " << rows << " x " << cols << std::endl;
	//std::cout << "Vector sizes: " << dataList.size() - 1 << " x " << dataList[0].size();
	if (!((rows == (dataList.size() - 1)) && (cols == (dataList[1].size()))))
	{
		std::cout << "Matrix dimensions are not correct!" << std::endl;
		return numMatrix;
	}

	
	for (int i = 1; i <= rows; i++)
	{
		std::vector<float> row;
		for (std::string text : dataList[i])
		{
			row.push_back(std::stof(text));
		}
		numMatrix.push_back(row);
	}
	return numMatrix;
};



//std::vector<std::vector<float>> MatrixMultiply()
//{
//
//};