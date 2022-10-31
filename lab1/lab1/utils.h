#pragma once
#include <iostream>

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