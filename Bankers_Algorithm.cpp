#include <bits/stdc++.h>
using namespace std;

#define vii vector<int>

struct Process
{
    vii allocation, need, max_need;
};

vii sequence;

void Bankers_Algorithm(int num_proc, int num_res, vii available, vector<Process> info)
{
    vector<bool> finish(num_proc);
    sequence.clear();
    bool check = false, flag = true;
    while (flag)
    {
        flag = false;
        for (int i = 0; i < num_proc; i++)
        {
            if (finish[i])
                continue;
            check = true;
            for (int j = 0; j < num_res; j++)
            {
                if (info[i].need[j] > available[j])
                {
                    check = false;
                    break;
                }
            }
            if (check)
            {
                // cout << "OK=" << i << endl;
                flag = true;
                sequence.push_back(i);
                finish[i] = true;
                for (int j = 0; j < num_res; j++)
                    available[j] += info[i].need[j];
            }
        }
    }
}

int main()
{
    int num_of_processes, num_of_resources;
    // cout<<"ENTER Number of Process and Resources: ";
    cin >> num_of_processes >> num_of_resources;

    // cout<<"ENTER Available Resources: ";
    vii available(num_of_resources);
    for (int i = 0; i < num_of_resources; i++)
        cin >> available[i];

    vector<Process> Info(num_of_processes);
    for (int i = 0; i < num_of_processes; i++)
    {
        Info[i].allocation.resize(num_of_resources);
        Info[i].max_need.resize(num_of_resources);
        Info[i].need.resize(num_of_resources);

        // cout<<"ENTER Allocation for each Resources: ";
        for (int j = 0; j < num_of_resources; j++)
            cin >> Info[i].allocation[j];
        // cout<<"ENTER Max_Need for each Resources: ";
        for (int j = 0; j < num_of_resources; j++)
        {
            cin >> Info[i].max_need[j];
            Info[i].need[j] = Info[i].max_need[j] - Info[i].allocation[j];
        }
    }

    Bankers_Algorithm(num_of_processes, num_of_resources, available, Info);
    if (sequence.size() == num_of_processes)
    {
        cout << "The system is in the safe state....." << endl;
        cout << "The Safe state is = ";
        for (auto seq : sequence)
            cout << "T" << seq << "  ";
        cout << endl;
    }
    else
        cout << "The system is not in the safe state....." << endl;

    //  Resource request algorithm
    int request_id;
    cin >> request_id;
    vii request_resource(num_of_resources);
    for (int i = 0; i < num_of_resources; i++)
        cin >> request_resource[i];

    for (int i = 0; i < num_of_resources; i++)
    {
        if (request_resource[i] > available[i])
        {
            cout << "Request exceeds available resources...Can't accept request!!!!" << endl;
            return 0;
        }
        else if (request_resource[i] > Info[request_id].need[i])
        {
            cout << "Request exceeds maximum need...Can't accept request!!!!" << endl;
            return 0;
        }
        else
        {
            available[i] -= request_resource[i];
            Info[request_id].need[i] -= request_resource[i];
            Info[request_id].allocation[i] += request_resource[i];
        }
    }

    Bankers_Algorithm(num_of_processes, num_of_resources, available, Info);
    if (sequence.size() == num_of_processes)
    {
        cout << "Resources are allocated....." << endl;
        cout << "The Safe state is = ";
        for (auto seq : sequence)
            cout << "T" << seq << "  ";
        cout << endl;
    }
    else
    {
        cout << "The process must wait and the previous allocation is restored....";
        for (int i = 0; i < num_of_resources; i++)
        {
            available[i] += request_resource[i];
            Info[request_id].need[i] += request_resource[i];
            Info[request_id].allocation[i] -= request_resource[i];
        }
    }
}

/*
Sample Input:

5 3
3 3 2
0 1 0   7 5 3
2 0 0   3 2 2
3 0 2   9 0 2
2 1 1   2 2 2
0 0 2   4 3 3
4
3 3 0

*/