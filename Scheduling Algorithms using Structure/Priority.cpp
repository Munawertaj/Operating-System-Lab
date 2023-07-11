/*
Problem : PRIORITY SCHEDULING
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

int num;
vii times, process_no;

void Priority_Scheduling(vector<process> &proc);
void print_table(vector<process> &proc);
void Average(vector<process> &proc);
void gant_chart();

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    // taking inputs
    cin >> num;
    vector<process> proc(num);
    int prior, brst;

    for (int i = 0; i < num; i++)
    {
        cin >> brst >> prior;
        proc[i].id = i;
        proc[i].burst = brst;
        proc[i].priority = prior;
    }

    cout << "PRIORITY SCHEDULING ALGORITHM IMPLEMENTATION:" << nl << nl;
    Priority_Scheduling(proc);
    print_table(proc);
    Average(proc);
    gant_chart();

    return 0;
}

void Priority_Scheduling(vector<process> &proc)
{
    sort(proc.begin(), proc.end(), compare_by_priority);
    times.pb(0);
    int prc, brs, total_time = 0;

    for (int i = 0; i < proc.size(); i++)
    {
        prc = proc[i].id;
        brs = proc[i].burst;

        total_time += brs;
        proc[i].turn = total_time;
        times.pb(total_time);
        process_no.pb(prc);
    }
}

void print_table(vector<process> &proc)
{
    cout << "---------------Table--------------" << nl;
    cout << "Process\tPriority\tBurst\tTurnAround\tWaiting" << nl;

    sort(proc.begin(), proc.end(), compare_by_id);
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
5
10 3
1 1
2 4
1 5
5 2

Sample Output:
PRIORITY SCHEDULING ALGORITHM IMPLEMENTATION:

---------------Table--------------
Process	Priority	Burst	TurnAround	Waiting
P0			3		10		16			6
P1			1		1		1			0
P2			4		2		18			16
P3			5		1		19			18
P4			2		5		6			1

---------------Average values--------------

Average Turn around time = 12
Average Waiting time = 8.2

---------------GANT CHART--------------
------------------------------------------------------
| P1 |     P4     |          P0          |  P2  | P3 |
------------------------------------------------------
0    1            6                      16     18   19

*/