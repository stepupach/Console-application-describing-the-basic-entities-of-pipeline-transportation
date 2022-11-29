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

void pipes::edit_pipe() {
    //cout << "\n Pipe condition: " << condition << ".\n Cnahge it (1- yes; 0 - no)?\n ";
    condition = (!condition);
}

istream& operator >> (istream& in, pipes& pipe)
{
    pipe.set_id();
    cout << " Create a new pipe! Fill in the gaps\n Name: ";
    getline(in, pipe.name_pipe);
    cout << " Length (1-20000 m): ";
    pipe.length = check_number(1.0, 20000.0);
    cout << " Diameter (500, 700, 1400 mm): ";
    pipe.diameter = check_diameter(500, 700, 1400);
    cout << " Condition 0 - Under repair\n           1 - OK\n->";
    pipe.condition = check_number(0, 1);
    pipe.cs_id_out = 0;
    pipe.cs_id_in = 0;
    return in;
}

ostream& operator << (ostream& out, const pipes& pipe)
{
    cout << "\n***Pipe***------+----------------+-----------------------------------------+\n";
    cout << "id:" << pipe.id_p;
    cout << "\nname:" << pipe.name_pipe;
    cout << "\n|    Length     |    Diameter    | Condition: 0 - Under repair,   1 - OK   |\n";
    printf("|    %.2f     |     %.2f     |              %d                          |\n", pipe.length, pipe.diameter, pipe.condition);
    cout << "\nPipe degree of OUT: " << pipe.cs_id_out;
    cout << "\nPipe degree of IN: " << pipe.cs_id_in;
    return out;
}

ofstream& operator << (ofstream& out, const pipes& pipe)
{
    out << pipe.get_id() << endl
        << pipe.name_pipe << endl
        << pipe.length << endl
        << pipe.diameter << endl
        << pipe.condition << endl
        << pipe.cs_id_out << endl
        << pipe.cs_id_in << endl;
    return out;
}
ifstream& operator >> (ifstream& in, pipes& pipe)
{
    in >> pipe.id_p;
    in.ignore(10000, '\n');
    getline(in, pipe.name_pipe);
    in >> pipe.length;
    in >> pipe.diameter;
    in >> pipe.condition;
    in >> pipe.cs_id_out;
    in >> pipe.cs_id_in;
    return in;
}