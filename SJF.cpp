/*
Problem : SHORTEST JOB FIRST
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

int num;
double total_time = 0, turn_around = 0, waiting = 0;
vii tat(100, 0), bt(100);
vii times, process_no;
vector<pii> process(100);

void print_table();
void gant_chart();
void SJF();
void Average();

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    // taking inputs
    cin >> num;
    int brst;
    for (int i = 1; i <= num; i++)
    {
        cin >> brst;
        process[i] = {brst, i};
        bt[i] = brst;
    }

    cout << "SHORTEST JOB FIRST SCHEDULING ALGORITHM IMPLEMENTATION:" << nl << nl;
    SJF();
    print_table();
    Average();
    gant_chart();

    return 0;
}

void SJF()
{
    sort(process.begin() + 1, process.begin() + num + 1);
    
    times.pb(0);
    for (int i = 1; i <= num; i++)
    {
        total_time += process[i].ff;
        tat[process[i].ss] = total_time;
        times.pb(total_time);
        process_no.pb(process[i].ss);
    }
}

void print_table()
{
    cout << "---------------Table--------------" << nl;
    cout << "Process\tBurst\tTurnAround\tWaiting" << nl;
    for (int i = 1; i <= num; i++)
        cout << "P" << i << "\t\t" << bt[i] << "\t\t" << tat[i] << "\t\t\t" << tat[i] - bt[i] << nl;
    cout << nl;
}

void Average()
{
    cout << "---------------Average values--------------" << nl;
    for (int i = 1; i <= num; i++)
    {
        turn_around += tat[i];
        waiting += (tat[i] - bt[i]);
    }
    cout << nl << "Average Turn around time = " << turn_around / num << nl;
    cout << "Average Waiting time = " << waiting / num << nl;
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
SHORTEST JOB FIRST SCHEDULING ALGORITHM IMPLEMENTATION:

---------------Table--------------
Process	Burst	TurnAround	Waiting
P1		2		2			0
P2		5		14			9
P3		3		5			2
P4		7		21			14
P5		4		9			5

---------------Average values--------------

Average Turn around time = 10.2
Average Waiting time = 6

---------------GANT CHART--------------
----------------------------------------------------------
|  P1  |   P3   |    P5    |     P2     |       P4       |
----------------------------------------------------------
0      2        5          9            14               21

*/