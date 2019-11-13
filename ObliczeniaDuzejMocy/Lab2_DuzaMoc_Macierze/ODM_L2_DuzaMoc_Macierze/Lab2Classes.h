#include <algorithm>
#include <boost/algorithm/string.hpp>
#pragma once

class CSVReader
{
	std::string fileName;
	std::string delimeter;

public:
	CSVReader(std::string filename, std::string delm = ",") :
		fileName(filename), delimeter(delm)
	{ }

	// Function to fetch data from a CSV File
	std::vector<std::vector<std::string>> getData();
};

std::vector<std::vector<std::string>> CSVReader::getData()
{
	std::ifstream file(fileName);
	std::vector<std::vector<std::string>> dataList;

	std::string line = "";

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
	std::cout << "Loaded Matrix: " << rows << " x " << cols;
	//std::cout << row[1];

	return dataList;
};



class MatrixMultiply
{

};