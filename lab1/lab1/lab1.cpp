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
    char name[10];
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

pipe add_pipe(pipe &pipe_one) {
    system("cls");
    cout << "Create a new pipe! Fill in the gaps\n Length (100-10000): ";
    pipe_one.length = check_double(pipe_one.length, 100, 10000);
    cout <<" Diameter (10-999): ";
    pipe_one.diameter = check_double(pipe_one.diameter, 10, 999);;
    cout << " Condition 0 - Under repair\n           1 - OK\n->";
    pipe_one.condition = check_int(pipe_one.condition, 0, 1);
    return pipe_one;
}

station add_station(station &station_one) {
    system("cls");
    cout << " Create a new station! Fill in the gaps\n Name station: ";
    cin >> station_one.name;
    cout << " Number of workshops (2-10): ";
    station_one.all_workshops = check_int (station_one.all_workshops, 2, 10);
    cout << " Number of active workshops(1-10): ";
    station_one.active_workshops = check_int (station_one.active_workshops, 1, station_one.all_workshops-1);
    cout << " Performance, 0,00% (0.00-1.00): ";
    station_one.performance = check_double (station_one.performance, 0, 1);
    return station_one;
}

void view_pipe(pipe  pipe_one) {
    cout << "\n***Pipe***------+----------------+-----------------------------------------+\n";
    cout << "|    Length     |    Diameter    | Condition: 0 - Under repair,   1 - OK   |\n";
    printf("|    %.2f       |     %.2f       |  %5d                                  |\n",
           pipe_one.length, pipe_one.diameter, pipe_one.condition);
}

void view_station(station  station_one) {
     cout << "\n***Station***----+---------------------+------------------+-------------+\n";
     cout << "|       Name     |    All workshops    | Active workshops | Performance |\n";
     printf("|       %5s      |     %5d      |  %5d    |   %.2f     |\n", station_one.name, station_one.all_workshops, station_one.active_workshops, station_one.performance);
}
    
pipe edit_pipe(pipe &pipe_one) {
    string answer;
    system("cls");
    view_pipe(pipe_one);
    cout << "\nDo you want to change the condition of the pipe? (yes/no) ";
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
    return pipe_one;
}

void edit_station() {

}

void save(pipe pipe_one, station station_one) {
    ofstream fout;
    fout.open("data.txt", ios::out);
    if (fout.is_open())
    {
        fout << "***Pipe***\n";
        fout << "Length " << pipe_one.length << endl << "Diameter " << pipe_one.diameter << endl << "Condition " << pipe_one.condition << endl;
        fout << "***Station***\n";
        fout << "Name " << station_one.name << endl << "All workshops " << station_one.all_workshops<< endl
             << "Active workshops " << station_one.active_workshops << endl << "Performance " << station_one.performance;
    }
    fout.close();
}

pipe download_pipe (pipe pipe_one) {
    ifstream fin;
    fin.open("data.txt", ios::in);
    if (fin.is_open())
    {
        string word;
        while (fin >> word)
        {
            if (word == "Length ")
            {
                fin >> pipe_one.length;
                break;
            }
            if (word == "Diameter ")
            {
                fin >> pipe_one.diameter;
                break;
            }
            if (word == "Condition ")
            {
                fin >> pipe_one.condition;
                break;
            }
        }
        fin.close();
    }
    else cout << "Error opening file!" << endl;
    return pipe_one;
}

station download_station(station station_one) {
    ifstream fin;
    fin.open("data.txt", ios::in);
    if (fin.is_open())
    {
        string word;
        while (fin >> word)
        {
            if (word == "Name ")
            {
                fin >> station_one.name;
                break;
            }
            if (word == "All workshops ")
            {
                fin >> station_one.all_workshops;
                break;
            }
            if (word == "Active workshops ")
            {
                fin >> station_one.active_workshops;
                break;
            }
            if (word == "Performance  ")
            {
                fin >> station_one.performance;
                break;
            }
        }
        fin.close();
    }
    else cout << "Error opening file!" << endl;
    return station_one;
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
                view_pipe(pipe_one);
                view_station(station_one);
                break;
            }
            case 4:
            {
                edit_pipe(pipe_one);
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
                view_pipe(download_pipe(pipe_one));
                view_station(download_station(station_one));
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
