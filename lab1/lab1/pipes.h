#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class pipes
{
    int id_p;

public:
    static int maxId_pipe;
    double length, diameter;
    bool condition;
    int cs_id_in;
    int cs_id_out;
    std::string name_pipe;

    int get_id() const;
    void set_id();
    void edit_pipe();

    friend std::ostream& operator << (std::ostream& out, const pipes& pipe);
    friend std::istream& operator >> (std::istream& in, pipes& pipe);
    friend std::ofstream& operator << (std::ofstream& out, const pipes& pipe);
    friend std::ifstream& operator >> (std::ifstream& in, pipes& pipe);
};

