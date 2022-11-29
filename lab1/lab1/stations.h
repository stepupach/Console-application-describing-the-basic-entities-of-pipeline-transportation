#pragma once
#include <iostream>
#include <string>
#include <fstream>
class stations
{
    int id_cs{};
public:
    static int maxId_cs;
    std::string name;
    int all_workshops, active_workshops;
    double performance;
    int ishod = 0;
    int zahod = 0;

    int get_id() const;
    void set_id();
    static void edit_station(stations& cs);

    friend std::ostream& operator << (std::ostream& out, const stations& cs);
    friend std::istream& operator >> (std::istream& in, stations& cs);
    friend std::ofstream& operator << (std::ofstream& out, const stations& cs);
    friend std::ifstream& operator >> (std::ifstream& in, stations& cs);
};

