/*
Problem : ROUND ROBIN
Author: Tareq Munawer Taj
CSE, Rajshahi University
*/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define vii vector<int>
#define ff first
#define ss second
#define nl "\n"
using namespace std;

struct process
{
    int id, burst, turn, wait;
};

int num, quantam;
vii times, process_no;
queue<pii> processes;

void RoundRobin(vector<process> &proc);
void print_table(vector<process> &proc);
void Average(vector<process> &proc);
void gant_chart();

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> num >> quantam;
    vector<process> proc(num);
    int bt;
    for (int i = 0; i < num; i++)
    {
        cin >> bt;
        proc[i].id = i;
        proc[i].burst = bt;
        processes.push({i, bt});
    }

    cout << "ROUND ROBIN SCHEDULING ALGORITHM IMPLEMENTATION:" << nl << nl;
    RoundRobin(proc);
    print_table(proc);
    Average(proc);
    gant_chart();
}

void RoundRobin(vector<process> &proc)
{
    int total_time = 0;
    times.push_back(0);
    pair<int, int> temp;
    int p_id, b_time;

    while (processes.size())
    {
        temp = processes.front();
        processes.pop();
        p_id = temp.first;
        b_time = temp.second;

        if (b_time <= quantam || processes.empty())
            total_time += b_time;
        else
        {
            total_time += quantam;
            b_time -= quantam;
            processes.push({p_id, b_time});
        }
        proc[p_id].turn = total_time;
        times.push_back(total_time);
        process_no.push_back(p_id);
    }
}

void print_table(vector<process> &proc)
{
    cout << "---------------Table--------------" << nl;
    cout << "Process\tBurst\tTurnAround\tWaiting" << nl;

    for (int i = 0; i < proc.size(); i++)
        proc[i].wait = proc[i].turn - proc[i].burst;

    for (auto x : proc)
        cout << "P" << x.id << "\t\t" << x.burst << "\t\t" << x.turn << "\t\t\t" << x.wait << nl;
    cout << nl;
}

void Average(vector<process> &proc)
{
    cout << "---------------Average values--------------" << nl;
    double total_turn_around = 0, total_waiting = 0;
    for (auto x : proc)
    {
        total_turn_around += x.turn;
        total_waiting += x.wait;
    }
    cout << nl << "Average Turn around time = " << total_turn_around / num << nl;
    cout << "Average Waiting time = " << total_waiting / num << nl;
    cout << nl;
}

void gant_chart()
{
    cout << "---------------GANT CHART--------------" << nl;

    string sequence, dash;

    // Generating Process string
    sequence.pb('|');
    for (int i = 1; i < times.size(); i++)
    {
        for (int j = 0; j < times[i] - times[i - 1]; j++)
            sequence.pb(' ');
        sequence.pb('P');
        sequence.pb(process_no[i - 1] + '0');
        for (int j = 0; j < times[i] - times[i - 1]; j++)
            sequence.pb(' ');
        sequence.pb('|');
    }

    // Generating line for upper and lower
    for (int i = 0; i < sequence.size(); i++)
        dash.pb('-');
    // Printing the GANT Chart
    cout << dash << nl << sequence << nl << dash << nl;

    // Printing Completion time
    int i = 0;
    for (int j = 0; j < sequence.size(); j++)
    {
        if (sequence[j] == '|')
        {
            cout << times[i];
            if (times[i] > 9)
                j++;
            i++;
        }
        else
            cout << " ";
    }
    cout << nl;
}

/*
Sample Input:
3 4
20 11 7

Sample Output:
ROUND ROBIN SCHEDULING ALGORITHM IMPLEMENTATION:

---------------Table--------------
Process	Burst	TurnAround	Waiting
P0		20		38			18
P1		11		30			19
P2		7		23			16

---------------Average values--------------

Average Turn around time = 30.3333
Average Waiting time = 17.6667

---------------GANT CHART--------------
--------------------------------------------------------------------------------------------------------
|    P0    |    P1    |    P2    |    P0    |    P1    |   P2   |    P0    |   P1   |        P0        |
--------------------------------------------------------------------------------------------------------
0          4          8          12         16         20       23         27       30                 38


*/
