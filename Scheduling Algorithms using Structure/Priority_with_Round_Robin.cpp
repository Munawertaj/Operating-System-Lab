/*
Problem : PRIORITY WITH ROUND ROBIN SCHEDULING
Author: Tareq Munawer Taj
CSE, Rajshahi University
*/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vii vector<int>
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define ff first
#define ss second
#define nl "\n"
using namespace std;
struct process
{
    int id;
    int burst, turn, wait, priority;
};

bool compare_by_priority(process x, process y)
{
    return x.priority < y.priority;
}

bool compare_by_id(process x, process y)
{
    return x.id < y.id;
}

int num, quantam, total_time = 0;
vii times, process_no;
queue<pii> processes;

void Priority_Scheduling(vector<process> &proc);
void RoundRobin(vector<process> &proc);
void print_table(vector<process> &proc);
void Average(vector<process> &proc);
void gant_chart();

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    // taking inputs
    cin >> num >> quantam;
    vector<process> proc(num);
    int prior, brst;

    for (int i = 0; i < num; i++)
    {
        cin >> brst >> prior;
        proc[i].id = i;
        proc[i].burst = brst;
        proc[i].priority = prior;
    }

    cout << "PRIORITY WITH ROUND ROBIN SCHEDULING ALGORITHM IMPLEMENTATION:" << nl << nl;
    Priority_Scheduling(proc);
    print_table(proc);
    Average(proc);
    gant_chart();

    return 0;
}

void Priority_Scheduling(vector<process> &proc)
{
    sort(proc.begin(), proc.end(), compare_by_priority);
    int p_id, b_time, p_prior;
    times.push_back(0);
    for (int i = 0; i < proc.size(); i++)
    {
        p_id = proc[i].id;
        b_time = proc[i].burst;
        p_prior = proc[i].priority;

        // Checking for RR
        if (i + 1 < proc.size() && proc[i + 1].priority == p_prior)
        {
            while (i < proc.size())
            {
                processes.push({proc[i].id, proc[i].burst});
                if (i + 1 < proc.size() && p_prior != proc[i + 1].priority)
                    break;

                i++;
            }
            RoundRobin(proc);
        }
        else
        {
            total_time += b_time;
            times.pb(total_time);
            process_no.pb(p_id);
        }
    }
    // Turnaround finaL VALUES
    sort(proc.begin(), proc.end(), compare_by_id);
    for (int i = 0; i < process_no.size(); i++)
        proc[process_no[i]].turn = times[i + 1];
}

void RoundRobin(vector<process> &proc)
{
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
        times.push_back(total_time);
        process_no.push_back(p_id);
    }
}

void print_table(vector<process> &proc)
{
    cout << "---------------Table--------------" << nl;
    cout << "Process\tPriority\tBurst\tTurnAround\tWaiting" << nl;

    for (int i = 0; i < proc.size(); i++)
        proc[i].wait = proc[i].turn - proc[i].burst;

    for (auto x : proc)
        cout << "P" << x.id << "\t\t\t" << x.priority << "\t\t" << x.burst << "\t\t" << x.turn << "\t\t\t" << x.wait << nl;
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
    // Generating Process
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
    // Generating upper and lower line
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
5 3
5 3
1 1
10 2
8 2
4 2

Sample Output:
PRIORITY WITH ROUND ROBIN SCHEDULING ALGORITHM IMPLEMENTATION:

---------------Table--------------
Process	Priority	Burst	TurnAround	Waiting
P0			3		5		28			23
P1			1		1		1			0
P2			2		10		23			13
P3			2		8		22			14
P4			2		4		17			13

---------------Average values--------------

Average Turn around time = 18.2
Average Waiting time = 12.6

---------------GANT CHART--------------
------------------------------------------------------------------------------------------
| P1 |   P2   |   P3   |   P4   |   P2   |   P3   | P4 |   P2   |  P3  | P2 |     P0     |
------------------------------------------------------------------------------------------
0    1        4        7        10       13       16   17       20     22   23           28


*/