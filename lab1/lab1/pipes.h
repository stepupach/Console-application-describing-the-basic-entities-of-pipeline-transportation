#pragma once
#include <iostream>
#include <string>

using namespace std;

class pipes
{
public:
    static int maxId_pipe;
    int id_p;
    double length, diameter;
    bool condition;
    std::string name_pipe;

    pipes();
    static void edit_pipe(pipes& pipe);

    friend std::ostream& operator << (std::ostream& out, const pipes& pipe);
    friend std::istream& operator >> (std::istream& in, pipes& pipe);
};

