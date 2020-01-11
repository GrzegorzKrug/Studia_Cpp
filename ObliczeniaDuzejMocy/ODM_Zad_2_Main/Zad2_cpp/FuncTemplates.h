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
int search(const T& container, const char letter)
{
	std::cout << "Running overloaded function" << std::endl;
	for (int i = 0; i < sizeof(container); i++) {
		if (container[i] == letter) {
			return i;
		}
	}
	return -1;
}
