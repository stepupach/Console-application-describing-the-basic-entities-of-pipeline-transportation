#pragma once
#include <iostream>
#include <string>
class stations
{
    public:
    static int maxId_cs;
    std::string name;
    int id_cs, all_workshops, active_workshops;
    double performance;

    stations();
    static void edit_station(stations& cs);

    friend std::ostream& operator << (std::ostream& out, const stations& cs);
    friend std::istream& operator >> (std::istream& in, stations& cs);
};

