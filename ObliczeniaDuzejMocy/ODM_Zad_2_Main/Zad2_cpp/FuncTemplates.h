#pragma once
#include <string>

template <typename T>
int search(const T* container, const T target)
{
	for (int i = 0; i < sizeof(container); i++) {
		if (container[i] == target) {
			return i;
		}
	}
	return -1;
}

template <typename Let>
int search(const char& container, const Let& letter)
{
	std::cout << "Running Overloaded char function" << std::endl;
	for (int i = 0; i < sizeof(container); i++) {
		if (container[i] == letter) {
			return i;
		}
	}
	return -1;
}

template <typename T, typename Let>
int search(const T& container, const Let& letter)
{
	std::cout << "Running Overloaded string function" << std::endl;
	for (int i = 0; i < sizeof(container); i++) {
		if (container[i] == letter) {
			return i;
		}
	}
	return -1;
}