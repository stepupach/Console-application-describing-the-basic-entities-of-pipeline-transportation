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

void add_pipe(pipe **pipes, int* p_size, int* p_capacity) {
    system("cls");
    cout << "Length: ";
    scanf("%d", &(*pipes)[*p_size].length); //http://www.c-cpp.ru/content/scanf
    cout <<"Diameter: ";
    scanf("%d", &(*pipes)[*p_size].diameter);
    cout << "Condition 1 - Under repair\n          0 - OK\n->";
    scanf("%s", &(*pipes)[*p_size].condition);

    (*p_size)++;

    if (*p_size >= *p_capacity) {
        *p_capacity *= 2;

        *pipes = (pipe*)realloc(*pipes, *p_capacity * sizeof(pipe));
    }
}

void add_station(station **stations, int* s_size, int* s_capacity) {
    //system("cls");
    cout << "Name station: ";
    scanf("%s", &(*stations)[*s_size].name);
    cout << "Number of workshops: ";
    scanf("%d", &(*stations)[*s_size].all_workshops);
    cout << "Number of active workshops: ";
    scanf("%d", &(*stations)[*s_size].active_workshops);
    cout << "Performance: ";
    scanf("%lf", &(*stations)[*s_size].performance);

    (*s_size)++;

    if (*s_size >= *s_capacity) {
        *s_capacity *= 2;

        *stations = (station*)realloc(*stations, *s_capacity * sizeof(station));
    }
}

void view_objects(pipe* pipes, int p_size) {
    cout << "***Pipes***--------+----------------+-----------+\n";
    cout << "| N |    Length     |    Diameter    | Condition|\n";
    cout << "+------------------+----------------+-----------+\n";

    if (p_size == 0) cout << "|            No pipes was added...              |\n";

    for (int i = 0; i < p_size; i++)
    printf("| %d|       %5d      |     %5d      |  %5s    |\n", i, pipes[i].length, pipes[i].diameter, pipes[i].condition);

   /* cout << "***Stations***---+---------------------+------------------+-------------+\n";
    cout << "|       Name     |    All workshops    | Active workshops | Performance |\n";
    cout << "+----------------+---------------------+------------------+-------------+\n";

    if (s_size == 0) cout << "|            No stations was added...                                   |\n";

    for (int i = 0; i < s_size; i++)
        printf("|       %7s      |     %5d      |  %5d    |   %4lf     |\n", stations[i].name, stations[i].all_workshops, stations[i].active_workshops, stations[i].performance);
*/
}

void edit_pipe() {

}

void edit_station() {

}

void save(pipe* pipes, station* stations, int p_size, int s_size) {
    ofstream fout;
    fout.open("data.txt", ios::out);
    if (fout.is_open())
    {
        fout << "***Pipes***\n";
        for (int i = 0; i < p_size; i++)
            fout << i << endl << pipes[i].length << endl << pipes[i].diameter << endl << pipes[i].condition << endl;
        fout.close();
    }
}

pipe download() {
    ifstream fin;
    pipe pipes;
    fin.open("data.txt", ios::in);
    if (fin.is_open())
    { 
    //for (int i = 0; i < p_size; i++) {
        fin >> pipes.length;
        fin >> pipes.diameter;
        fin >> pipes.condition;
    }
 return pipes;
}

void print_menu() {
    system("cls"); 
    cout << "Welcome! This is the menu.Select an action:\n";
    cout << "1. Add pipe\n2. Add compressor station\n3. View all objects\n4. Edit pipe\n5. Edit compressor station\n6. Save\n7. Download\n0. Exit\n->";
}

int main()
{
    int variant, p_size = 0, p_capacity = 1,s_size = 0, s_capacity = 1; 
    pipe* pipes = (pipe*)malloc(p_capacity * sizeof(pipe)); //память под массив товаров
    station* stations = (station*)malloc(s_capacity * sizeof(station));
    do {
        print_menu();
        variant = check_variant(0,7);
        switch (variant) {
            case 1:
                add_pipe(&pipes, &p_size, &p_capacity);
                break;
            case 2:
                add_station(&stations, &s_size, &s_capacity);
                break;
            case 3:
                view_objects(pipes, p_size);
                break;
            case 4:
                edit_pipe();
                break;
            case 5:
                edit_station();
                break;
            case 6:
                save(pipes, stations, p_size, s_size);
                break;
            case 7:
               // view_objects(download());
                break;
            //default:   cout << "Invalid value. Try again:";
         }

        if (variant != 0)
            system("pause");
    } while (variant != 0);

    return 0;
}
