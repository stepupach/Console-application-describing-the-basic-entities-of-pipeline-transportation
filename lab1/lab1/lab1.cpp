#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct pipe {
    double length, diameter; 
    int condition;
};

struct station {
    string name;
    int all_workshops, active_workshops;
    double performance;
};

template <typename type>

type check_number (type min, type max) {
    type i;
   // cin >> i;
        while ((cin>>i).fail() || i < min || i >  max || cin.get() != '\n') {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Try again. Enter number ("<< min <<"-"<< max <<"): ";
            //cin >> i;
        } 
   return i;
}

istream& operator >> (istream& in, pipe& pipe_one)
{
    system("cls");
    cout << "Create a new pipe! Fill in the gaps\n Length (500-20000 m): ";
    pipe_one.length = check_number(500.0, 20000.0);
    cout << " Diameter (100-5000 m): ";
    pipe_one.diameter = check_number(100.0, 5000.0);
    cout << " Condition 0 - Under repair\n           1 - OK\n->";
    pipe_one.condition = check_number(0, 1);
    return in;
}

ostream& operator << (ostream& out, pipe& pipe_one)
{
   //cout << "\n***Station***----+---------------------+------------------+\n-->";
   // cout << station_one.name;
   // cout << "\n|    All workshops    | Active workshops  | Performance % |\n";
   // printf("|         %d         |       %d         |     %.2f    |\n", station_one.all_workshops, station_one.active_workshops, station_one.performance);
    out << "\n***Pipe***------+----------------+-----------------------------------------+\n";
    out << "|    Length     |    Diameter    | Condition: 0 - Under repair,   1 - OK   |\n";
    printf("|    %.2f     |     %.2f     |              %d                          |\n", pipe_one.length, pipe_one.diameter, pipe_one.condition);
    return out;
}

/*int check_int(int i, int min, int max) {
    cin >> i;
        while (cin.fail() || i < min || i > max || cin.get() != '\n') //https://www.cyberforum.ru/cpp-beginners/thread547287.html 
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Try again. Enter int (" << min << "-" << max << "): ";
            cin >> i;
        }
   return i;
} */

void add_pipe(pipe &pipe_one) {
    system("cls");
    cout << "Create a new pipe! Fill in the gaps\n Length (500-20000 m): ";
    pipe_one.length = check_number(500.0, 20000.0);
    cout <<" Diameter (100-5000 m): ";
    pipe_one.diameter = check_number(100.0, 5000.0);
    cout << " Condition 0 - Under repair\n           1 - OK\n->";
    pipe_one.condition = check_number(0, 1);
}

void add_station(station &station_one) {
    system("cls");
    cout << " Create a new station! Fill in the gaps\n Name station: ";
    getline(cin, station_one.name);
    cout << " Number of workshops (1-100): ";
    station_one.all_workshops = check_number(1, 100);
    cout << " Number of active workshops (<=all workshops): ";
    station_one.active_workshops = check_number(0, station_one.all_workshops);
    station_one.performance = (double)station_one.active_workshops / (double)station_one.all_workshops * 100;
    cout << " Performance %: " << station_one.performance << endl;
}

void view(pipe  &pipe_one, station& station_one) {
    cout << "\n***Station***----+---------------------+------------------+\n-->";
    cout << station_one.name;
    cout << "\n|    All workshops    | Active workshops  | Performance % |\n";
    printf("|         %d         |       %d         |     %.2f    |\n", station_one.all_workshops, station_one.active_workshops, station_one.performance);
    cout << "\n***Pipe***------+----------------+-----------------------------------------+\n";
    cout << "|    Length     |    Diameter    | Condition: 0 - Under repair,   1 - OK   |\n";
    printf("|    %.2f     |     %.2f     |              %d                          |\n", pipe_one.length, pipe_one.diameter, pipe_one.condition);
}
     
void edit_pipe(pipe &pipe_one) {
    string answer;
    cout << "\n Pipe condition: " << pipe_one.condition << ".\n Cnahge it (write 'yes/no')?\n ";
    do
    {
        cin >> answer;
        if ((answer == "yes" && pipe_one.condition == 0) || (answer == "no" && pipe_one.condition == 1))
        {
            pipe_one.condition = 1;
            break;
        }
        else if ((answer == "yes" && pipe_one.condition == 1) || (answer == "no" && pipe_one.condition == 0))
        {
            pipe_one.condition = 0;
            break;
        }
        cout << "Type 'yes / no' ";
    }while (answer != "yes" || answer != "no");
}

void edit_station(station& station_one) {
    cout << "Station has " << station_one.active_workshops << " active workshops. New amount active workshops:\n";
    station_one.active_workshops = check_number(0, station_one.all_workshops);
    station_one.performance = (double)station_one.active_workshops / (double)station_one.all_workshops * 100;
}

void save(pipe &pipe_one, station &station_one) {
    ofstream fout;
    fout.open("data.txt", ios::out);
    if (fout.is_open())
    {
        fout << station_one.name << endl << station_one.all_workshops<< endl<< station_one.active_workshops << endl <<  station_one.performance << endl
             << pipe_one.length << endl << pipe_one.diameter << endl << pipe_one.condition << endl;
        fout.close();
    }
    else cout << "Error opening file!\n";
}

void download(pipe& pipe_one, station& station_one) {
    ifstream fin;
    fin.open("data.txt", ios::in);
    if (fin.is_open())
    {
        getline(fin, station_one.name);
        fin >> station_one.all_workshops >> station_one.active_workshops >> station_one.performance >>
            pipe_one.length >> pipe_one.diameter >> pipe_one.condition;;
        view(pipe_one, station_one);
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
    pipe pipe_one{};
    station station_one{};
    while (1) {
        print_menu();
            switch (check_number(0, 7)) {
            case 1:
            {
                add_pipe(pipe_one);
                break;
            }
            case 2:
            {
                add_station(station_one);
                break;
            }
            case 3:
            {
               // view(pipe_one, station_one);
                cout << pipe_one;
                break;
            }
            case 4:
            {
                edit_pipe(pipe_one);
                break;
            }
            case 5:
            {
                edit_station(station_one);
                break;
            }
            case 6:
            {
                save(pipe_one, station_one);
                break;
            }
            case 7:
            {
                download(pipe_one, station_one);
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