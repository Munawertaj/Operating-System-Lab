#include <bits/stdc++.h>
using namespace std;

#define vii vector<int>

struct Process
{
    vii allocation, request;
};

void Deadlock_Detection(int num_proc, int num_res, vii work, vector<Process> info)
{
    vector<bool> finish(num_proc);
    vii sequence;
    sequence.clear();
    bool check = false, flag = true;

    for (int i = 0; i < num_proc; i++)
    {
        check = true;
        for (int j = 0; j < num_res; j++)
        {
            if (info[i].allocation[j])
            {
                check = false;
                break;
            }
        }
        if (check)
            finish[i] = true;
    }

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
                if (info[i].request[j] > work[j])
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
                    work[j] += info[i].allocation[j];
            }
        }
    }
    for (int i = 0; i < num_proc; i++)
    {
        if (!finish[i])
        {
            cout << "The system is in Deadlock state!!!!!" << endl;
            return;
        }
    }
    cout << "No Deadlock!!!!\nThe Safe sequence is = ";
    for (auto seq : sequence)
        cout << "T" << seq << "  ";
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

        Info[i].request.resize(num_of_resources);

        // cout<<"ENTER Allocation for each Resources: ";
        for (int j = 0; j < num_of_resources; j++)
            cin >> Info[i].allocation[j];
        // cout<<"ENTER Max_Need for each Resources: ";
        for (int j = 0; j < num_of_resources; j++)
            cin >> Info[i].request[j];
    }

    Deadlock_Detection(num_of_processes, num_of_resources, available, Info);
}