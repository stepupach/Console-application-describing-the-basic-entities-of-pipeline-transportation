#include "stations.h"
#include "utils.h"
#include <fstream>

using namespace std;

int stations::maxId_cs = 0;

int stations::get_id() const
{
    return id_cs;
}

void stations::set_id()
{
	id_cs = ++maxId_cs;
}

void stations::edit_station(stations& cs) {
    cout << "Station has " << cs.active_workshops << " active workshops. New amount active workshops:\n";
    cs.active_workshops = check_number(0, cs.all_workshops);
    cs.performance = (double)cs.active_workshops / (double)cs.all_workshops * 100;
}

istream& operator >> (istream& in, stations& cs)
{
    cs.set_id();
    cout << " Create a new CS! Fill in the gaps\n Name: ";
    getline(in, cs.name);
    cout << " Number of workshops (1-100): ";
    cs.all_workshops = check_number(1, 100);
    cout << " Number of active workshops (<=all workshops): ";
    cs.active_workshops = check_number(0, cs.all_workshops);
    cs.performance = (double)cs.active_workshops / (double)cs.all_workshops * 100;
    cout << " Performance %: " << cs.performance << endl;
    return in;
}

ostream& operator << (ostream& out, const stations& cs)
{
    cout << "\n***Station***----+---------------------+------------------+";
    cout << "\nid:" << cs.id_cs;
    cout << "\nname:" << cs.name;
    cout << "\n|    All workshops    | Active workshops  | Performance % |\n";
    printf("|         %d         |       %d         |     %.2f    |\n", cs.all_workshops, cs.active_workshops, cs.performance);
    return out;
}

ofstream& operator << (ofstream& out, const stations& cs)
{
    out << cs.get_id() << endl
        << cs.name << endl
        << cs.all_workshops << endl
        << cs.active_workshops << endl
        << cs.performance << endl;
    return out;
}

ifstream& operator >> (ifstream& in, stations& cs)
{
    in >> cs.id_cs;
    in.ignore(10000, '\n');
    getline(in, cs.name);
    in >> cs.all_workshops;
    in >> cs.active_workshops;
    in >> cs.performance;
    return in;
}