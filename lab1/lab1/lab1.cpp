#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct pipes {
    int id_pipe;
    double length, diameter; 
    bool condition;
};

struct stations {
    string name;
    int id_cs, all_workshops, active_workshops;
    double performance;
};

template <typename type>
type check_number (type min, type max) {
    type i;
        while ((cin>>i).fail() || i < min || i >  max || cin.get() != '\n') {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Try again. Enter number ("<< min <<"-"<< max <<"): ";
        } 
   return i;
}

istream& operator >> (istream& in, pipes& pipe)
{
    system("cls");
    cout << "Create a new pipe! Fill in the gaps\n Length (500-20000 m): ";
    pipe.length = check_number(500.0, 20000.0);
    cout << " Diameter (100-5000 m): ";
    pipe.diameter = check_number(100.0, 5000.0);
    cout << " Condition 0 - Under repair\n           1 - OK\n->";
    pipe.condition = check_number(0, 1);
    return in;
}

istream& operator >> (istream& in, stations& cs)
{
    system("cls");
    cout << " Create a new station! Fill in the gaps\n Name station: ";
    getline(in, cs.name);
    cout << " Number of workshops (1-100): ";
    cs.all_workshops = check_number(1, 100);
    cout << " Number of active workshops (<=all workshops): ";
    cs.active_workshops = check_number(0, cs.all_workshops);
    cs.performance = (double)cs.active_workshops / (double)cs.all_workshops * 100;
    cout << " Performance %: " << cs.performance << endl;
    return in;
}

void print_pipe (pipes& pipe)
{
    cout << "\n***Pipe***------+----------------+-----------------------------------------+\n";
    cout << "|    Length     |    Diameter    | Condition: 0 - Under repair,   1 - OK   |\n";
    printf("|    %.2f     |     %.2f     |              %d                          |\n", pipe.length, pipe.diameter, pipe.condition);
}

void print_station(stations& cs)
{
    cout << "\n***Station***----+---------------------+------------------+\n-->";
    cout << cs.name;
    cout << "\n|    All workshops    | Active workshops  | Performance % |\n";
    printf("|         %d         |       %d         |     %.2f    |\n", cs.all_workshops, cs.active_workshops, cs.performance);
}

void view (pipes  &pipe, stations& cs) {
    if (pipe.length > 0 && cs.all_workshops == 0)
    {
        print_pipe(pipe);
    }
    else
        if (pipe.length == 0 && cs.all_workshops > 0)
        {
            print_station(cs);
        }
        else
            if (pipe.length > 0 && cs.all_workshops > 0)
            {
                print_pipe(pipe);
                print_station(cs);
            }
            else
                cout << "You should input objects!" << endl;
}
     
void edit_pipe(pipes &pipe) {
    cout << "\n Pipe condition: " << pipe.condition << ".\n Cnahge it (1- yes; 0 - no)?\n ";
    if (check_number(0, 1) == 1) pipe.condition = (!pipe.condition);
}

void edit_station(stations& cs) {
    cout << "Station has " << cs.active_workshops << " active workshops. New amount active workshops:\n";
    cs.active_workshops = check_number(0, cs.all_workshops);
    cs.performance = (double)cs.active_workshops / (double)cs.all_workshops * 100;
}

void save(pipes &pipe, stations &cs) {
    ofstream fout;
    fout.open("data.txt", ios::out);
    if (fout.is_open())
    {
        fout << cs.name << endl << cs.all_workshops<< endl<< cs.active_workshops << endl <<  cs.performance << endl
             << pipe.length << endl << pipe.diameter << endl << pipe.condition << endl;
        fout.close();
    }
    else cout << "Error opening file!\n";
}

void download(pipes& pipe, stations& cs) {
    ifstream fin;
    fin.open("data.txt", ios::in);
    if (fin.is_open())
    {
        getline(fin, cs.name);
        fin >> cs.all_workshops >> cs.active_workshops >> cs.performance >>
            pipe.length >> pipe.diameter >> pipe.condition;;
        view(pipe, cs);
        fin.close();
    }
    else cout << "Error opening file!\n";
}

void print_menu() {
    system("cls"); 
    cout << "   Welcome! This is the menu. Select an action:\n";
    cout << "1. Add pipe\n2. Add compressor station\n3. View all objects\n4. Edit pipe\n5. Edit compressor station\n6. Save\n7. Download\n0. Exit\n->";
}

int main()
{
    pipes pipe{};
    stations cs{};
    while (1) {
        print_menu();
            switch (check_number(0, 7)) {
            case 1:
            {
                cin >> pipe;
                break;
            }
            case 2:
            {
                cin >> cs;
                break;
            }
            case 3:
            {
                view(pipe, cs);
                break;
            }
            case 4:
            {
                edit_pipe(pipe);
                break;
            }
            case 5:
            {
                edit_station(cs);
                break;
            }
            case 6:
            {
                save(pipe, cs);
                break;
            }
            case 7:
            {
                download(pipe, cs);
                break;
            }
            case 0:
            {
                cout << "\nGood luck!\n";
                return 0;
            }
            }
               system("pause");
    }
    return 0;
}