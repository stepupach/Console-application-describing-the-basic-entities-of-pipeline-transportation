#include "pipes.h"
#include "utils.h"
#include <fstream>

using namespace std;

int pipes::maxId_pipe = 0;

int pipes::get_id() const
{
    return id_p;
}

void pipes::set_id()
{
    id_p = ++maxId_pipe;
}

void pipes::edit_pipe(pipes& pipe) {
    cout << "\n Pipe condition: " << pipe.condition << ".\n Cnahge it (1- yes; 0 - no)?\n ";
    if (check_number(0, 1) == 1) pipe.condition = (!pipe.condition);
}

istream& operator >> (istream& in, pipes& pipe)
{
    pipe.set_id();
    cout << " Create a new pipe! Fill in the gaps\n Name: ";
    getline(in, pipe.name_pipe);
    cout << " Length (500-20000 m): ";
    pipe.length = check_number(500.0, 20000.0);
    cout << " Diameter (100-5000 m): ";
    pipe.diameter = check_number(100.0, 5000.0);
    cout << " Condition 0 - Under repair\n           1 - OK\n->";
    pipe.condition = check_number(0, 1);
    return in;
}

ostream& operator << (ostream& out, const pipes& pipe)
{
    cout << "\n***Pipe***------+----------------+-----------------------------------------+\n";
    cout << "id:" << pipe.id_p;
    cout << "\nname:" << pipe.name_pipe;
    cout << "\n|    Length     |    Diameter    | Condition: 0 - Under repair,   1 - OK   |\n";
    printf("|    %.2f     |     %.2f     |              %d                          |\n", pipe.length, pipe.diameter, pipe.condition);
    return out;
}

ofstream& operator << (ofstream& out, const pipes& pipe)
{
    out << pipe.get_id() << endl
        << pipe.name_pipe << endl
        << pipe.length << endl
        << pipe.diameter << endl
        << pipe.condition << endl;
    return out;
}
ifstream& operator >> (ifstream& in, pipes& pipe)
{
    in >> pipe.id_p;
    in >> pipe.name_pipe;
    in >> pipe.length;
    in >> pipe.diameter;
    in >> pipe.condition;
    return in;
}