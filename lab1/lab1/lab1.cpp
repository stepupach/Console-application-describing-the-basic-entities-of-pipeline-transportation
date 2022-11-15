#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "pipes.h"
#include "stations.h"
#include "utils.h"

using namespace std;

pipes& select_pipe(unordered_map<int, pipes>& pipe)
{
    cout << "Enter pipe id: ";
    int id = check_number<uint64_t>(1, pipes::maxId_pipe);
    if (pipe.count(id) == 0)
        cout << "Error! No pipe with this id\n";
    else
        return pipe[id];
}

stations& select_cs(unordered_map<int, stations>& cs)
{
    cout << "Enter compressor station id: ";
    int id = check_number<uint64_t>(1, stations::maxId_cs);
    if (cs.count(id) == 0)
        cout << "Error! No CS with this id\n";
    else
        return cs[id];
}

void delete_pipe(unordered_map<int, pipes>& pipe)
{
    cout << "Enter pipe id: ";
    int id = check_number<uint64_t>(1, pipes::maxId_pipe);
    if (pipe.count(id) == 0)
        cout << "Error! No pipe with this id\n";
    else
        pipe.erase(id);
}

void delete_station(unordered_map<int, stations>& cs)
{
    cout << "Enter compressor station id: ";
    int id = check_number<uint64_t>(1, stations::maxId_cs);
    if (cs.count(id) == 0)
        cout << "Error! No CS with this id\n";
    else
        cs.erase(id);
}

void load_pipe(ifstream& fin, unordered_map<int, pipes>& pipeline)
{
    pipes pipe;
    fin >> pipe;
    pipeline.emplace(pipes::maxId_pipe + 1, pipe);

}

void load_station(ifstream& fin, unordered_map<int,stations>& cs_sistem)
{
    stations cs;
    fin >> cs;
    cs_sistem.emplace(stations::maxId_cs + 1, cs);
}

void print_menu() {
    system("cls"); 
    cout << "   Welcome! This is the menu. Select an action:\n";
    cout << "1. Add pipe\n2. Add compressor station\n3. View all objects\n4. Edit pipe\n5. Edit compressor station" << endl
         << "6. Save\n7. Download\n8. Delete pipe\n9. Delete station\n10. Find object\n11. Packet edit pipe\n0. Exit\n->";
}

template<typename T>
using filter_pipe = bool(*)(const pipes& pipe, T p);
    bool check_condition(const pipes& pipe, bool p)
    {
        return pipe.condition == p;
    }
    bool check_nameP(const pipes& pipe, string p)
    {
        return pipe.name_pipe == p;
    }

template<typename T>
vector<int>find_pipe(const unordered_map<int, pipes>& pipeline, filter_pipe <T> f, T p)
{
    vector<int>res;
    int i = 0;
    for (auto& pipe : pipeline)
    {
        if (f(pipe.second, p))  res.push_back(pipe.first);
        i++;
    }
    if (res.empty())
        cout << "No pipe with this parameter" << endl;
    return res;
}

template<typename T>
using filter_cs = bool(*)(const stations& cs, T p);
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
vector<int>find_cs(const unordered_map<int, stations>& cs_sistem, filter_cs <T> f, T p)
{
    vector<int>res;
    int i = 0;
    for (auto& cs : cs_sistem)
    {
        if (f(cs.second, p)) res.push_back(cs.first);;
        i++;
    }
    if (res.empty())
        cout << "No CS with this parameter" << endl;
    return res;
}

void packet_edit_pipe(unordered_map<int, pipes>& pipeline)
{
    cout << "Edit 1 - all pipes, 2 - some pipes: ";
    if (check_number(1, 2) == 1)
    {
        for (auto& pipe : pipeline)
            pipes::edit_pipe(pipe.second);
    }
    else
    {
        vector <int> vectID;
        while (true)
        {
            cout << "Enter pipe id - to edit, 0 - to complete: ";
            int i = check_number(0, (int)pipeline.size());
            if (i)
            {
                if (pipeline.count(i) == 0)
                    cout << "Error! No pipe with this id\n";
                else
                    vectID.push_back(i);
            }
            else
                break;
        }
        for (int i : vectID)
            pipeline[i].condition = !pipeline[i].condition;
    }
}

int main()
{
    unordered_map <int, pipes> pipeline = {};
    unordered_map <int, stations> cs_sistem = {};
    while (1) {
        print_menu();
            switch (check_number(0, 11)) {
            case 1:
            {
                pipes pipe;
                cin >> pipe;
                pipeline.emplace(pipeline.size() + 1, pipe);
                break;
            }
            case 2:
            {
                stations cs;
                cin >> cs;
                cs_sistem.emplace(cs_sistem.size() + 1, cs);
                break;
            }
            case 3:
            {
                cin.clear();
                system("cls");
                if ((pipeline.size() != 0) && (cs_sistem.size() == 0))
                {
                    for (const auto& [id_p, pipe] : pipeline)
                    {
                        cout << id_p;
                        cout << pipe << endl;
                    }
                }
                else if ((pipeline.size() == 0) && (cs_sistem.size() != 0))
                {
                    for (const auto& [id_cs, cs] : cs_sistem)
                    {
                        cout << id_cs;
                        cout << cs << endl;
                    }
                }
                else if ((pipeline.size() != 0) && (cs_sistem.size() != 0))
                {
                    for (const auto& [id_p, pipe] : pipeline)
                    {
                        cout << id_p;
                        cout << pipe << endl;
                    }
                    for (const auto& [id_cs, cs] : cs_sistem)
                    {
                        cout << id_cs;
                        cout << cs << endl;
                    }
                }
                else cout << "Input objects" << endl;
                break;
            }
            case 4:
            {
                cin.clear();
                    if (pipeline.size() > 0)
                    {
                        pipes::edit_pipe(select_pipe(pipeline));
                    }
                    else cout << "Input pipe to edit! " << endl;
                break;
            }
            case 5:
            {
                cin.clear();
                    if (cs_sistem.size() > 0)
                    {
                        stations::edit_station(select_cs(cs_sistem));
                    }
                    else cout << "Input compressor station to edit! " << endl;
                break;
            }
            case 6:
            {
                ofstream fout;
                string fname;
                cout << "Enter file's name: ";
                getline(cin, fname);
                fout.open(fname + ".txt", ios::out);
                if (fout.is_open())
                {
                    fout << pipeline.size() << endl;
                    for (const auto& [id_p, p] : pipeline)
                        fout << pipe;
                    fout << cs_sistem.size() << endl;
                    for (const auto& [id_cs, cs] : cs_sistem)
                        fout << cs;
                    fout.close();
                    break;
                }
                else cout << "Error opening file!\n";
                break;
            }
            case 7:
            {
                cin.clear();
                system("cls");
                ifstream fin;
                string fname;
                cout << "Enter file's name: ";
                getline(cin, fname);
                fin.open(fname + ".txt", ios::in);
                if (fin.is_open())
                {
                    int i;
                    fin >> i;
                    while (i != 0)
                    {
                        load_pipe(fin, pipeline);
                        --i;
                    }
                    int j;
                    fin >> j;
                    while (j != 0)
                    {
                        load_station(fin, cs_sistem);
                        --j;
                    }
                }
                fin.close();
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
                else cout << "Error! No pipes yet" << endl;
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
                else cout << "Error! No CS yet" << endl;
                break;
            }
            case 10:
            {
                cin.clear();
                system("cls");
                cout << "Search pipes or CS by filter (0 - CS , 1 - pipes):  " << endl;
                if (check_number(0, 1) == 1)
                {
                    cout << "Search pipes by filter (1 - name ; 2 - condition):  " << endl;
                    switch (check_number(1, 2))
                    {
                    case 1:
                    {
                        string pname;
                        cout << "Search pipes with name:  " << endl;
                        getline(cin, pname);
                        for (int i : find_pipe(pipeline, check_nameP, pname))
                            cout << pipeline[i];
                        break;
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
                        getline(cin, csname);
                        for (int i : find_cs(cs_sistem, check_nameCS, csname))
                            cout << cs_sistem[i];
                        break;
                    }
                    case 2:
                    {
                        cout << "Find CS with percent of no working shops (0 - 100 %):  " << endl;
                        double nowork = check_number(0.0, 100.0);
                        for (int i : find_cs(cs_sistem, check_nowork, nowork))
                            cout << cs_sistem[i];
                        break;
                    }
                    }
                }
                break;
            }
            case 11:
            {
                cin.clear();
                system("cls");
                packet_edit_pipe(pipeline);
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