//#define _CRT_SECURE_NO_WARNINGS
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

string check_string(string s) { //https://ru.stackoverflow.com/questions/627884/
    int i = 0, k = 0;
    getline(cin, s);
    do {
        int i = 0, k = 0;
        getline(cin, s);
        while (s[i])
        {
            if (s[i] >= '0' && s[i] <= '9')
            {
                k++;
                break;
            }
            i++;
            if (k != 0) cout << "Only letters!";
        }
    } while (k != 0);
    return s;
}

/*string check_char(string i) { // строка для считывания введённых данных
    getline(cin, s);
    // проверка
    while (sscanf_s(s.c_str(), "%s", &i) != 1) {
        cout << "Invalid value. Try again:";
        getline(cin, s);
    }
    return i;
}*/

double check_double (double i, int min, int max) {
    cin >> i;
    if (cin.fail() || i < min || i >max || cin.get() != '\n')
    {
        do {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Try again. Enter double:";
            cin >> i;
        } while (cin.fail() || i < min || i >max || cin.get() != '\n'); 
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
        } while (cin.fail() || i < min || i >max || cin.get() != '\n'); //https://www.cyberforum.ru/cpp-beginners/thread547287.html
    }
    return i;
}

/*int check_variant(int min, int max) {
    int variant;
    string s; // строка для считывания введённых данных
    getline(cin, s);
    // проверка
    while (sscanf_s(s.c_str(), "%d", &variant) != 1 || cin.fail() || variant < min || variant >max || check_string(s) == 2) {
        cout << "Invalid value. Try again:";
        getline(cin, s);
    }
    return variant;
}*/

pipe add_pipe(pipe &pipe_one, int &amount_pipe) {
    system("cls");
    cout << "Create a new pipe! Fill in the gaps\n Length (100-10000): ";
    //scanf("%d", &pipe_one.length); //http://www.c-cpp.ru/content/scanf
    pipe_one.length = check_double(pipe_one.length, 100, 10000);
    cout <<" Diameter (10-999): ";
    pipe_one.diameter = check_double(pipe_one.diameter, 10, 999);;
    cout << " Condition 0 - Under repair\n           1 - OK\n->";
    pipe_one.condition = check_int(pipe_one.condition, 0, 1);
    amount_pipe++;
    return pipe_one;
}

station add_station(station &station_one, int &amount_station) {
    system("cls");
    cout << " Create a new station! Fill in the gaps\n Name station: ";
    check_string(station_one.name);
    cout << " Number of workshops (2-10): ";
    station_one.all_workshops = check_int (station_one.all_workshops, 2, 10);
    cout << " Number of active workshops(1-10): ";
    station_one.active_workshops = check_int (station_one.active_workshops, 1, 10);
    cout << " Performance, 0,00% (0.00-1.00): ";
    station_one.performance = check_double (station_one.performance, 0, 1);
    amount_station++;
    return station_one;
}

//void view_objects(pipe &pipe_one, station  &station_one, int &amount_pipe, int &amount_station) {
void view_objects(pipe  pipe_one) {
    //if (amount_pipe == 0) cout << "|            No pipe was added...              |\n";
    //else {
        cout << "***Pipe***--------+----------------+-----------+\n";
        cout << "|    Length     |    Diameter    | Condition   |\n";
        printf("|    %.2f     |     %.2f      |  %5d      |\n", pipe_one.length, pipe_one.diameter, pipe_one.condition);
   // }
    //if (amount_station == 0) cout << "|            No station was added...                                   |\n";
   // else {
       // cout << "***Station***----+---------------------+------------------+-------------+\n";
       // cout << "|       Name     |    All workshops    | Active workshops | Performance |\n";
       // printf("|       %7s      |     %5d      |  %5d    |   %1lf     |\n", station_one.name, station_one.all_workshops, station_one.active_workshops, station_one.performance);
   // }
}
    

void edit_pipe() {

}

void edit_station() {

}

void save(pipe pipe_one, station &station_one) {
    ofstream fout;
    fout.open("data.txt", ios::out);
    if (fout.is_open())
    {
        fout << "***Pipe***\n";
        fout << pipe_one.length << endl << pipe_one.diameter << endl << pipe_one.condition << endl;
    }
    fout.close();
}

pipe download() {
    ifstream fin;
    pipe pipe_f;
    fin.open("data.txt", ios::in);
    if (fin.is_open()) {
        fin >> pipe_f.length;
        fin >> pipe_f.diameter;
        fin >> pipe_f.condition;
    }
    fin.close();
    return pipe_f;
}

void print_menu() {
    system("cls"); 
    cout << "   Welcome! This is the menu. Select an action:\n";
    cout << "1. Add pipe\n2. Add compressor station\n3. View all objects\n4. Edit pipe\n5. Edit compressor station\n6. Save\n7. Download\n0. Exit\n->";
}

int main()
{
    int variant = 10, amount_pipe = 0, amount_station = 0;
    pipe pipe_one{};
    station station_one{};
    while (1) {
        print_menu();
        variant=check_int(variant, 0, 7);
            switch (variant) {
            case 1:
            {
                add_pipe(pipe_one, amount_pipe);
                break;
            }
            case 2:
            {
                add_station(station_one, amount_station);
                break;
            }
            case 3:
            {
                view_objects(pipe_one);
                break;
            }
            case 4:
            {
                edit_pipe();
                break;
            }
            case 5:
            {
                edit_station();
                break;
            }
            case 6:
            {
                save(pipe_one, station_one);
                break;
            }
            case 7:
            {
                view_objects(download());
                break;
            }
            case 0:
            {
                return 0;
            }
           // default: cout << "try again";
            }
            if (variant != 0)
                system("pause");
    }

    return 0;
}
