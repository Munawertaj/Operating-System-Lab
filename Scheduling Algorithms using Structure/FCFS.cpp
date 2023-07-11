/*
Problem : FIRST COME FIRST SERVE
Author: Tareq Munawer Taj
CSE, Rajshahi University
*/
#include <bits/stdc++.h>
#define pb push_back
#define vii vector<int>
#define nl "\n"
using namespace std;

struct process
{
    int id, burst, turn, wait;
};

int num;
vii times, process_no;

void FCFS(vector<process> &proc);
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

    int bt;
    for (int i = 0; i < num; i++)
    {
        cin >> bt;
        proc[i].id = i;
        proc[i].burst = bt;
    }

    cout << "FIRST COME FIRST SERVE SCHEDULING ALGORITHM IMPLEMENTATION:" << nl << nl;
    FCFS(proc);
    print_table(proc);
    Average(proc);
    gant_chart();

    return 0;
}

void FCFS(vector<process> &proc)
{
    int total_time = 0;
    times.pb(0);
    for (int i = 0; i < proc.size(); i++)
    {
        total_time += proc[i].burst;
        proc[i].turn = total_time;
        times.pb(total_time);
        process_no.pb(proc[i].id);
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
5
2 5 3 7 4

Sample Output:
FIRST COME FIRST SERVE SCHEDULING ALGORITHM IMPLEMENTATION:

---------------Table--------------
Process	Burst	TurnAround	Waiting
P0		2		2			0
P1		5		7			2
P2		3		10			7
P3		7		17			10
P4		4		21			17

---------------Average values--------------

Average Turn around time = 11.4
Average Waiting time = 7.2

---------------GANT CHART--------------
----------------------------------------------------------
|  P0  |     P1     |   P2   |       P3       |    P4    |
----------------------------------------------------------
0      2            7        10               17         21

*/