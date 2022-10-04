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

double check_double (double i, int min, int max) {
    cin >> i;
    if (cin.fail() || i < min || i >max || cin.get() != '\n')
    {
        do {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Try again. Enter double: ";
            cin >> i;
        } while (cin.fail() || i < min || i > max || cin.get() != '\n'); 
    }
   return i;
}

double check_double_f(double i, int min, int max) {
    ifstream fin;
    if (fin.fail() || i < min || i >max || fin.get() != '\n')
    {
        fin.clear();
        fin.ignore(10000, '\n');
        i = 0;
    }
    return i;
}

int check_int_f(int i, int min, int max) {
    ifstream fin;
    if (fin.fail() || i < min || i >max || fin.get() != '\n')
    {
        fin.clear();
        fin.ignore(10000, '\n');
        i = 0;
    }
    return i;
}

int check_int (int i, int min, int max) {
    cin >> i;
    if (cin.fail() || i < min || i >max || cin.get() != '\n')
    {
        do {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Try again. Enter int:";
            cin >> i;
        } while (cin.fail() || i < min || i >= max || cin.get() != '\n'); //https://www.cyberforum.ru/cpp-beginners/thread547287.html
    }
    return i;
}

void add_pipe(pipe &pipe_one) {
    system("cls");
    cout << "Create a new pipe! Fill in the gaps\n Length (100-10000): ";
    pipe_one.length = check_double(pipe_one.length, 100, 10000);
    cout <<" Diameter (10-999): ";
    pipe_one.diameter = check_double(pipe_one.diameter, 10, 999);
    cout << " Condition 0 - Under repair\n           1 - OK\n->";
    pipe_one.condition = check_int(pipe_one.condition, 0, 1);
}

void add_station(station &station_one) {
    system("cls");
    cout << " Create a new station! Fill in the gaps\n Name station: ";
    getline(cin, station_one.name);
    cout << " Number of workshops (1-10): ";
    station_one.all_workshops = check_int (station_one.all_workshops, 1, 10);
    cout << " Number of active workshops (<=all workshops): ";
    station_one.active_workshops = check_int (station_one.active_workshops, 0, station_one.all_workshops);
    station_one.performance = (double)station_one.active_workshops / (double)station_one.all_workshops * 100;
    cout << " Performance %: " << station_one.performance << endl;
}

void view(pipe  &pipe_one, station& station_one) {
    cout << "\n***Pipe***------+----------------+-----------------------------------------+\n";
    cout << "|    Length     |    Diameter    | Condition: 0 - Under repair,   1 - OK   |\n";
    printf("|    %.2f    |     %.2f      |  %d                                  |\n",
           pipe_one.length, pipe_one.diameter, pipe_one.condition);
    cout << "\n***Station***----+---------------------+------------------+-------------+\n";
    cout << station_one.name;
    cout << "\n|    All workshops    | Active workshops | Performance % |\n";
    printf("|         %d           |     %d           |   %.2f      |\n", station_one.all_workshops, station_one.active_workshops, station_one.performance);
}
     
void edit_pipe(pipe &pipe_one) {
    string answer;
    cout << "\n(0 - Under repair, 1 - OK). Now pipe condition: " << pipe_one.condition << ". Cnahge condition (write 'yes/no') ? ";
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
    cout << "Now station has " << station_one.active_workshops << " active workshops. Type new amount active workshops\n";
    station_one.active_workshops = check_int(station_one.active_workshops, 0, station_one.all_workshops);
    station_one.performance = (double)station_one.active_workshops / (double)station_one.all_workshops * 100;
}

void save(pipe &pipe_one, station &station_one) {
    ofstream fout;
    fout.open("data.txt", ios::out);
    if (fout.is_open())
    {
        fout << pipe_one.length << endl << pipe_one.diameter << endl <<pipe_one.condition << endl;
        fout << station_one.name << endl << station_one.all_workshops<< endl<< station_one.active_workshops << endl <<  station_one.performance;
        fout.close();
    }
    else cout << "Error opening file!\n";
}

void download(pipe& pipe_one, station& station_one) {
    ifstream fin;
    fin.open("data.txt", ios::in);
    if (fin.is_open())
    {
        fin >> pipe_one.length >> pipe_one.diameter >> pipe_one.condition >> station_one.name 
            >> station_one.all_workshops >> station_one.active_workshops >> station_one.performance;
       /* if (check_double_f(pipe_one.length, 100, 10000) == 0 || check_double_f(pipe_one.diameter, 10, 999) == 0 || check_int_f(pipe_one.condition, 0, 1) == 0)
        {
            cout << "For pipe invalid value in file!\n";
        }
        else view(pipe_one, station_one);
        if (check_int_f(station_one.all_workshops, 1, 10) == 0 || check_int_f(station_one.active_workshops, 0, 10) == 0)
        {
            cout << "For station invalid value in file!\n";
            station_one.name = "none";
        }
        else view(pipe_one, station_one);
        view(pipe_one, station_one);
       //check_int(pipe_one.condition);*/
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
    int variant = 10;
    pipe pipe_one{};
    station station_one{};
    while (1) {
        print_menu();
            switch (check_int(variant, 0, 7)) {
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
                view(pipe_one, station_one);
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
            if (variant != 0)
                system("pause");
    }
    return 0;
}