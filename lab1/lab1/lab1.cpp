#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct pipe {
    int length; 
    int diameter; 
    char condition[20];
};

struct station {
    char name[20];
    int all_workshops;
    int active_workshops;
    double performance;
};

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
    system("cls");
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

void view_objects(pipe* pipes,station* stations, int p_size,int s_size) {
    cout << "***Pipes***--------+----------------+-----------+\n";
    cout << "| N |    Length     |    Diameter    | Condition|\n";
    cout << "+------------------+----------------+-----------+\n";

    if (p_size == 0) cout << "|            No pipes was added...              |\n";

    for (int i = 0; i < p_size; i++)
    printf("| %d|       %5d      |     %5d      |  %5s    |\n", i, pipes[i].length, pipes[i].diameter, pipes[i].condition);

    cout << "***Stations***---+---------------------+------------------+-------------+\n";
    cout << "|       Name     |    All workshops    | Active workshops | Performance |\n";
    cout << "+----------------+---------------------+------------------+-------------+\n";

    if (s_size == 0) cout << "|            No stations was added...                                   |\n";

    for (int i = 0; i < s_size; i++)
        printf("|       %7s      |     %5d      |  %5d    |   %4lf     |\n", stations[i].name, stations[i].all_workshops, stations[i].active_workshops, stations[i].performance);
}

void edit_pipe() {

}

void edit_station() {

}

void save(pipe* pipes, station* stations, int p_size, int s_size) {
    ofstream fout;
    fout.open("data.txt",'w');
    fout << "***Pipes***\n";
    for (int i = 0; i < p_size; i++) {
        fout << "N " << i
            << " Length: " << pipes[i].length
            << " Diameter: " << pipes[i].diameter
            << " Condition: " << pipes[i].condition << endl;
    }
    fout.close();
}

void download() {
    ifstream fin;
    fin.open("data.txt", 'r');


}

void menu() {
    system("cls"); 
    cout << "Welcome! This is the menu.Select an action:\n";
    cout << "1. Add pipe\n2. Add compressor station\n3. View all objects\n4. Edit pipe\n5. Edit compressor station\n6. Save\n7. Download\n0. Exit\n->";
}

int read_variant(int count) {
    int variant;
    string s; // строка для считывания введённых данных
    getline(cin, s); 
    // проверка
    while (sscanf_s(s.c_str(), "%d", &variant) != 1 || variant < 1 || variant > count) {
        cout << "Invalid value. Try again:"; 
        getline(cin, s); 
    }

    return variant;
}

int main()
{
    int variant; 
    int p_size = 0; // количество элементов массива товаров
    int p_capacity = 1; // ёмкость массива товаров
    int s_size = 0; 
    int s_capacity = 1; 
    pipe* pipes = (pipe*)malloc(p_capacity * sizeof(pipe)); //память под массив товаров
    station* stations = (station*)malloc(s_capacity * sizeof(station));
    do {
        menu();

        variant = read_variant(8); 

        switch (variant) {
            case 1:
                add_pipe(&pipes, &p_size, &p_capacity);
                break;
            case 2:
                add_station(&stations, &s_size, &s_capacity);
                break;
            case 3:
                view_objects(pipes,stations, p_size, s_size);
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
                download();
                break;
         }

        if (variant != 0)
            system("pause");
    } while (variant != 0);

    return 0;
}
