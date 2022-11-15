#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class pipes
{
    int id_p{};
public:
    static int maxId_pipe;
    double length, diameter;
    bool condition;
    std::string name_pipe;

    int get_id() const;
    pipes();
    static void edit_pipe(pipes& pipe);

    friend std::ostream& operator << (std::ostream& out, const pipes& pipe);
    friend std::istream& operator >> (std::istream& in, pipes& pipe);
    friend std::ofstream& operator << (std::ofstream& out, const pipes& pipe);
    friend std::ifstream& operator >> (std::ifstream& in, pipes& pipe);
};

