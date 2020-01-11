#pragma once
#include <string>

template <typename T, typename Let>
int search(const T& container, const Let& target)
{
	std::cout << "Running Normal function" << std::endl;
	for (int i = 0; i < sizeof(container); i++) {
		if (container[i] == target) {
			return i;
		}
	}
	return -1;
}

template <typename T>
int search(const T& container, const char target)
{
	std::cout << "Running overloaded function" << std::endl;
	//std::cout << "sizeof " << sizeof(container) << std::endl;
	for (int i = 0; i < sizeof(container); i++) {
		//std::cout << container[i] << " " << (container[i] == target) << std::endl;
		if (container[i] == target) {
			return i;
		}
	}
	return -1;
}

//template <typename T, char Let>
//int search(const T* container, const char letter)
//{
//	std::cout << "Running Overloaded char function" << std::endl;
//	for (int i = 0; i < sizeof(container); i++) {
//		if (container[i] == letter) {
//			return i;
//		}
//	}
//	return -1;
//}

