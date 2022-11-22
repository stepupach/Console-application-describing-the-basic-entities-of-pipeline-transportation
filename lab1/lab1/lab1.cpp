#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
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

void print_menu() {
    system("cls");
    cout << "   Welcome! This is the menu. Select an action:\n";
    cout << "1. Add pipe\n2. Add compressor station\n3. View all objects\n4. Edit pipe\n5. Edit compressor station" << endl
        << "6. Save\n7. Download\n8. Delete pipe or pipes\n9. Delete station\n10. Find object\n11. Packet edit pipe\n0. Exit\n->";
}

void load(ifstream& fin, unordered_map<int, pipes>& pipeline, unordered_map<int, stations>& cs_sistem)
{
    pipes pipe;
    stations cs;

    int kolvo_p;
    fin >> kolvo_p;
    for (int k = 1; k <= kolvo_p; k++)
    {
        fin >> pipe;
        pipe.maxId_pipe = pipe.get_id();
        pipeline.emplace(pipe.get_id(), pipe);
    }

    int kolvo_cs;
    fin >> kolvo_cs;
    for (int k = 1; k <= kolvo_cs; k++)
    {
        fin >> cs;
        cs.maxId_cs = cs.get_id();
        cs_sistem.emplace(cs.get_id(), cs);   
    }
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
        //double nowork = ((double)cs.all_workshops - (double)cs.active_workshops) / cs.all_workshops * 100;
        double nowork = 100 - cs.performance;
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
    cout << "Edit [1] - all pipes / [2] - some pipes: ";
    if (check_number(1, 2) == 1)
    {
        cout << "All pipes [1] - are working; [2] - under repair: ";
        if (check_number(1, 2) == 1)
        {
            for (auto& p : pipeline)
                p.second.condition = 1;
        }
        else
        {
            for (auto& p : pipeline)
                p.second.condition = 0;
        }
    }
    else
    {
     vector <int> vectID;
        while (true)
        {
            cout << "Enter pipe's id to edit or 0 to complete: ";
            int i = check_number<uint64_t>(0, pipes::maxId_pipe);
            if (i)
            {
                if (pipeline.count(i) == 0)
                    cout << "Error! There is no pipe with this id\n";
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

void delete_pipe(unordered_map<int, pipes>& pipe)
{
    cout << "Delete: 1 - one pipe; 2 - pipes with <condition>: ";
    switch (check_number(1, 2))
    {
    case 1:
    {
        cout << "Enter pipe id: ";
        int id = check_number<uint64_t>(1, pipe.size());
        if (pipe.count(id) == 0)
            cout << "Error! No pipe with this id\n";
        pipe.erase(id);
        break;
    }
    case 2:
    {
        cout << "Delete pipes condition (1 - pipe is working ; 0 - pipe under repair):  " << endl;
        bool condition = check_number(0, 1);
        vector <int> vectID = find_pipe(pipe, check_condition, condition);
        for (auto& id_p : vectID)
            cout << id_p << pipe[id_p] << endl;
        if (vectID.empty())
        {
            break;
        }
        else
        {
            cout << "Delete 1 - all of this pipes / 2 - some pipes: ";
            if (check_number(1, 2) == 1)
            {
                for (auto& id_p : vectID)
                    pipe.erase(id_p);
            }
            else
            {
                while (true)
                {
                    int i = 0;
                    int id;
                    cout << "\nEnter pipe's id to delete or 0 to complete: ";
                    cin >> id;
                    if (id)
                    {
                        for (auto& id_p : vectID)
                        {
                            if (id == id_p)
                            {
                                i++;
                            }
                        }
                        if (i == 0)
                        {
                            cout << "\nError! No pipe with this condition and this id";
                        }
                        else
                        {
                            pipe.erase(id);
                        }
                    } else break;
                } 
            }
        }
        break;
    }
    }
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
                pipeline.emplace(pipe.maxId_pipe, pipe);
                break;
            }
            case 2:
            {
                stations cs;
                cin >> cs;
                cs_sistem.emplace(cs.maxId_cs, cs);
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
                        cout << pipe << endl;
                    }
                }
                else if ((pipeline.size() == 0) && (cs_sistem.size() != 0))
                {
                    for (const auto& [id_cs, cs] : cs_sistem)
                    {
                        cout << cs << endl;
                    }
                }
                else if ((pipeline.size() != 0) && (cs_sistem.size() != 0))
                {
                    for (const auto& [id_p, pipe] : pipeline)
                    {
                        cout << pipe << endl;
                    }
                    for (const auto& [id_cs, cs] : cs_sistem)
                    {
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
                        select_pipe(pipeline).edit_pipe();
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
                    for (const auto& [id_p, pipe] : pipeline)
                    {
                        fout << pipe;
                    }
                    fout << cs_sistem.size() << endl;
                    for (const auto& [id_cs, cs] : cs_sistem)
                    {
                        fout << cs;
                    }
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
                cout << "Enter file's name: \n";
                getline(cin, fname);
                fin.open(fname + ".txt", ios::in);
                if (fin.is_open())
                {
                        load(fin, pipeline, cs_sistem);
                        fin.close();
                }
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