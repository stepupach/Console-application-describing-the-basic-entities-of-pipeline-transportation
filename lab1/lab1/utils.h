#pragma once
#include <iostream>
#include <unordered_map>

template <typename type>
type check_number(type min, type max) {
    type i;
    while ((std::cin >> i).fail() || i < min || i >  max || std::cin.get() != '\n') {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Try again. Enter number (" << min << "-" << max << "): ";
    }
    return i;
}

template <typename type>
type check_diameter(type a, type b, type c) {
    type i;
    while ((std::cin >> i).fail() || i != a  || i != b  || i!= c) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Try again. Enter number (" << a << "or" << b << "or" << c "): ";
    }
    return i;
}

template <typename T>
int checking(std::unordered_map<int, T>& map, std::string t_in, std::string t_error, int min, int max, int neraven)
{
	int x;
	std::cout << t_in;
	while ((std::cin >> x).fail() || x < min || x > max || x == neraven)
	{

		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << t_error << "\n";
		if (map.count(x) == 0) std::cout << "Error! No object with this id\n";
	}
	return x;
}