#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

typedef struct pipe {
    char length[20]; 
    double diameter; 
    int condition; 
} pipe;

void add_pipe(pipe** pipes, int* size, int* capacity) {
    printf("Длина: ");
    scanf("%s", &(*pipes)[*size].length);
    printf("Диаметр: ");
    scanf("%lf", &(*pipes)[*size].diameter);
    printf("Состояние: ");
    scanf("%d", &(*pipes)[*size].condition);

    (*size)++;

    if (*size >= *capacity) {
        *capacity *= 2;

        *pipes = (pipe*)realloc(*pipes, *capacity * sizeof(pipe));
    }
}

void menu() {
    system("cls"); // очистка экрана
    cout << "Выберите действие" << endl;
    cout << "1. Добавить трубу" << endl;
    cout << "2. Добавить КС" << endl;
    cout << "3. Просмотреть все объекты" << endl;
    cout << "4. Редактировать трубу" << endl;
    cout << "5. Редактировать КС" << endl;
    cout << "6. Сохранить" << endl;
    cout << "7. Загрузить" << endl;
    cout << "0. Выйти" << endl;
    cout << "->";
}

int read_variant(int count) {
    int variant;
    string s; // строка для считывания введённых данных
    getline(cin, s); 
    // проверка
    while (sscanf(s.c_str(), "%d", &variant) != 1 || variant < 1 || variant > count) {
        cout << "Некорректное значение. Введите снова:"; // вывод сообщения об ошибке
        getline(cin, s); 
    }

    return variant;
}

int main()
{
    int variant; // выбранный пункт меню
    do {
        menu(); // выводим меню на экран

        variant = read_variant(5); // получаем номер выбранного пункта меню

        switch (variant) {
        case 1:
            add_tube(&goods, &size, &capacity);
            break;
        }

        if (variant != 0)
            system("pause");
    } while (variant != 5);

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
