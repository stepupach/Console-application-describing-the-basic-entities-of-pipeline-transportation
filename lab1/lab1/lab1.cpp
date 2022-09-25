#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct pipe {
    int length, diameter; 
    char condition[20];
};

struct station {
    char name[20];
    int all_workshops, active_workshops;
    double performance;
};

int check_string(string s) { //https://ru.stackoverflow.com/questions/627884/
    int check = 1;
    for (int i = 0; i < s.length(); i++) { // идем по символам
        if (s[i] >= 'A' && s[i] <= 'Z' || s[i] >= 'a' && s[i] <= 'z') {
            check = 2;
            break;
        }
    }
    return check;
}

int check_float(float num) {
    int check;
    (((int)num) == num) ? check=1 : check=2;
    return check;
}

int check_variant(int min, int max) {
    int variant;
    string s; // строка для считывания введённых данных
    getline(cin, s);
    // проверка
    while (sscanf_s(s.c_str(), "%d", &variant) != 1 || cin.fail() || variant < min || variant >max || check_string(s) == 2) {
        cout << "Invalid value. Try again:";
        getline(cin, s);
    }
    return variant;
}

void add_pipe(pipe &pipe_one, int &amount_pipe) {
    system("cls");
    cout << "Create a new pipe! Fill in the gaps\n Length: ";
    //scanf("%d", &pipe_one.length); //http://www.c-cpp.ru/content/scanf
    cin >> pipe_one.length;
    cout <<" Diameter: ";
    cin >> pipe_one.diameter;
    cout << " Condition 0 - Under repair\n          1 - OK\n->";
    cin >> pipe_one.condition;
    amount_pipe++;
}

void add_station(station &station_one, int &amount_station) {
    system("cls");
    cout << " Create a new station! Fill in the gaps\n Name station: ";
    cin >>  station_one.name;
    cout << " Number of workshops: ";
    cin >> station_one.all_workshops;
    cout << " Number of active workshops: ";
    cin >> station_one.active_workshops;
    cout << " Performance: ";
    cin >> station_one.performance;
    amount_station++;
}

//void view_objects(pipe &pipe_one, station  &station_one, int &amount_pipe, int &amount_station) {
void view_objects(pipe  pipe_one) {
    //if (amount_pipe == 0) cout << "|            No pipe was added...              |\n";
    //else {
        cout << "***Pipe***--------+----------------+-----------+\n";
        cout << "|    Length     |    Diameter    | Condition   |\n";
        printf("|    %5d      |     %5d      |  %5s      |\n", pipe_one.length, pipe_one.diameter, pipe_one.condition);
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
    cout << "Welcome! This is the menu.Select an action:\n";
    cout << "1. Add pipe\n2. Add compressor station\n3. View all objects\n4. Edit pipe\n5. Edit compressor station\n6. Save\n7. Download\n0. Exit\n->";
}

int main()
{
    int variant, amount_pipe=0, amount_station=0;
    pipe pipe_one{};
    station station_one{};
    do {
        print_menu();
        variant = check_variant(0,7);
        switch (variant) {
            case 1:
                add_pipe(pipe_one, amount_pipe);
                break;
            case 2:
                add_station(station_one, amount_station);
                break;
            case 3:
                view_objects(pipe_one);
                break;
            case 4:
                edit_pipe();
                break;
            case 5:
                edit_station();
                break;
            case 6:
                save(pipe_one, station_one);
                break;
            case 7:
                view_objects(download());
                break;
         }

        if (variant != 0)
            system("pause");
    } while (variant != 0);

    return 0;
}
