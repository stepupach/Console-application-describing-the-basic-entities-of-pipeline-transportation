#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "pipes.h"
#include "stations.h"
#include "utils.h"

using namespace std;

pipes& select_pipe(vector<pipes>& pipe)
{
    cout << "Enter pipe id: ";
    unsigned int index = check_number<uint64_t>(1, pipe.size());
    return pipe[index - 1];
}

stations& select_cs(vector<stations>& cs)
{
    cout << "Enter compressor station id: ";
    unsigned int index = check_number<uint64_t>(1, cs.size());
    return cs[index - 1];
}

void delete_pipe(vector<pipes>& pipe)
{
    cout << "Enter pipe id: ";
    int index = check_number<uint64_t>(1, pipe.size());
    auto i = pipe.cbegin();
    pipe.erase(i + index - 1);
}

void delete_station(vector<stations>& cs)
{
    cout << "Enter compressor station id: ";
    auto index = check_number<uint64_t>(1, cs.size());
    auto i = cs.cbegin();
    cs.erase(i + index - 1);
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

void save_pipe(ofstream& fout, const pipes& pipe)
{
    string object;
    object = "pipe";
    fout << object << endl;
    fout << pipe.id_pipe << endl << pipe.name_pipe << endl << pipe.length << endl << pipe.diameter << endl << pipe.condition << endl;
}

void save_station(ofstream& fout, const stations& cs)
{
    string object;
    object = "compressor station";
    fout << object << endl;
    fout << cs.id_cs << endl << cs.name << endl << cs.all_workshops << endl << cs.active_workshops << endl << cs.performance << endl;
}

pipes load_pipe(ifstream& fin)
{
    pipes pipe;
    fin >> pipe.id_pipe;
    fin >> pipe.name_pipe;
    fin >> pipe.length;
    fin >> pipe.diameter;
    fin >> pipe.condition;
    return pipe;
}

stations load_station(ifstream& fin)
{
    stations cs;
    fin >> cs.id_cs;
    fin.ignore(10000, '\n');
    getline(fin, cs.name);
    fin >> cs.all_workshops;
    fin >> cs.active_workshops;
    fin >> cs.performance;
    return cs;
}

void print_menu() {
    system("cls"); 
    cout << "   Welcome! This is the menu. Select an action:\n";
    cout << "1. Add pipe\n2. Add compressor station\n3. View all objects\n4. Edit pipe\n5. Edit compressor station" << endl
         << "6. Save\n7. Download\n8. Delete pipe\n9. Delete station\n10. Find object\n0. Exit\n->";
}

template<typename T>
using filter1 = bool(*)(const pipes& pipe, T p);
    bool check_condition(const pipes& pipe, bool p)
    {
        return pipe.condition == p;
    }
    bool check_nameP(const pipes& pipe, string p)
    {
        return pipe.name_pipe == p;
    }

template<typename T>
vector<int>find_pipe(const vector<pipes>& pipeline, filter1 <T> f, T p)
{
    vector<int>res;
    int i = 0;
    for (auto& pipe : pipeline)
    {
            if (f(pipe, p))  res.push_back(i);
        i++;
    }
    return res;
}

template<typename T>
using filter2 = bool(*)(const stations& cs, T p);
    bool check_nameCS(const stations& cs, string p)
    {
        return cs.name == p;
    }
    bool check_nowork(const stations& cs, double p)
    {
        double nowork = ((double)cs.all_workshops - (double)cs.active_workshops) / cs.all_workshops * 100;
        return nowork >= p;
    }

template<typename T>
vector<int>find_cs(const vector<stations>& cs_sistem, filter2 <T> f, T p)
{
    vector<int>res;
    int i = 0;
    for (auto& cs : cs_sistem)
    {
        if (f(cs, p)) res.push_back(i);
        i++;
    }
    return res;
}

int main()
{
    vector <pipes> pipeline;
    vector <stations> cs_sistem;
    while (1) {
        print_menu();
            switch (check_number(0, 10)) {
            case 1:
            {
                pipes pipe;
                cin >> pipe;
                pipeline.push_back(pipe);
                break;
            }
            case 2:
            {
                stations cs;
                cin >> cs;
                cs_sistem.push_back(cs);
                break;
            }
            case 3:
            {
                cin.clear();
                system("cls");
                if ((pipeline.size() != 0) && (cs_sistem.size() == 0))
                {
                    for (auto& pipe : pipeline)
                        cout << pipe << endl;
                }
                else if ((pipeline.size() == 0) && (cs_sistem.size() != 0))
                {
                    for (auto& cs : cs_sistem)
                        cout << cs << endl;
                }
                else if ((pipeline.size() != 0) && (cs_sistem.size() != 0))
                {
                    for (auto& p : pipeline)
                        cout << p << endl;
                    for (auto& cs : cs_sistem)
                        cout << cs << endl;
                }
                else cout << "Input objects" << endl;
                break;
            }
            case 4:
            {
                cin.clear();
                    if (pipeline.size() > 0)
                    {
                        edit_pipe(select_pipe(pipeline));
                    }
                    else cout << "Input pipe! " << endl;
                break;
            }
            case 5:
            {
                cin.clear();
                    if (cs_sistem.size() > 0)
                    {
                        edit_station(select_cs(cs_sistem));
                    }
                    else cout << "Input compressor station! " << endl;
                break;
            }
            case 6:
            {
                ofstream fout;
                fout.open("data.txt", ios::out);
                if (fout.is_open())
                {
                    for (pipes& pipe : pipeline)
                        save_pipe(fout, pipe);
                    for (stations& cs : cs_sistem)
                        save_station(fout, cs);
                    break;
                }
                else cout << "Error opening file!\n";
                break;
            }
            case 7:
            {
                cin.clear();
                system("cls");
                string object;
                ifstream fin;
                fin.open("data.txt", ios::in);
                if (fin.is_open())
                {
                    while (!fin.eof())
                    {
                        getline(fin, object);
                        if (object == "pipe")
                            pipeline.push_back(load_pipe(fin));
                        if (object == "compressor station")
                            cs_sistem.push_back(load_station(fin));
                    }
                    break;
                }
                else
                    cout << "File didn't open..." << endl;
                break;
            }
            case 8:
            {
                cin.clear();
                system("cls");
                if (pipeline.size() > 0)
                {
                    delete_pipe(pipeline);
                }
                else cout << "Input pipe!" << endl;
                break;
            }
            case 9:
            {
                cin.clear();
                system("cls");
                if (cs_sistem.size() > 0)
                {
                    delete_station(cs_sistem);
                }
                else cout << "Input CS!" << endl;
                break;
            }
            case 10:
            {
                cin.clear();
                system("cls");
                cout << "Search pipes or CS by filter (1 - pipes ; 0 - CS):  " << endl;
                if (check_number(0, 1) == 1)
                {
                    cout << "Search pipes by filter (1 - name ; 2 - condition):  " << endl;
                    switch (check_number(1, 2))
                    {
                    case 1:
                    {
                        string pname;
                        cout << "Search pipes with name:  " << endl;
                        cin.ignore(10000, '\n');
                        getline(cin, pname);
                        for (int i : find_pipe(pipeline, check_nameP, pname))
                            cout << pipeline[i];
                    }
                    case 2:
                    {
                        cout << "Search pipes with condition (0 - Under repair,   1 - OK):  " << endl;
                        bool condition = check_number(0, 1);
                        for (int i : find_pipe(pipeline, check_condition, condition))
                            cout << pipeline[i];
                        break;
                    }
                    }
                }
                else
                {
                    cout << "Find CS by filter (1 - name ; 2 - nowork shops):  " << endl;
                    switch (check_number(1, 2))
                    {
                    case 1:
                    {
                        string csname;
                        cout << "Search CS with name:  " << endl;
                        cin.ignore(10000, '\n');
                        getline(cin, csname);
                        for (int i : find_cs(cs_sistem, check_nameCS, csname))
                            cout << cs_sistem[i];
                    }
                    case 2:
                    {
                        cout << "Find CS with percent of no working shops (0 - 100 %):  " << endl;
                        double nowork = check_number(0, 100);
                        for (int i : find_cs(cs_sistem, check_nowork, nowork))
                            cout << cs_sistem[i];
                    }
                    }
                }
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