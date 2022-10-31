#include "stations.h"
#include "utils.h"

using namespace std;

int stations::maxId_cs = 0;

stations::stations()
{
	id_cs = ++maxId_cs;
}

istream& operator >> (istream& in, stations& cs)
{
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
    cout << "\n***Station***----+---------------------+------------------+\n-->";
    cout << "id:" << cs.id_cs << endl;
    cout << "name:" << cs.name;
    cout << "\n|    All workshops    | Active workshops  | Performance % |\n";
    printf("|         %d         |       %d         |     %.2f    |\n", cs.all_workshops, cs.active_workshops, cs.performance);
    return out;
}