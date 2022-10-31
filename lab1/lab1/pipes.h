#pragma once
#include <iostream>
#include <string>

using namespace std;

class pipes
{
public:
    static int maxId_pipe;
    int id_pipe;
    double length, diameter;
    bool condition;
    std::string name_pipe;

    pipes();

    friend std::ostream& operator << (std::ostream& out, const pipes& pipe);
    friend std::istream& operator >> (std::istream& in, pipes& pipe);
};

