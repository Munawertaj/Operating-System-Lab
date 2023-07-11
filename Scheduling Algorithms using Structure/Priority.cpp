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

int num;
double total_time = 0, turn_around = 0, waiting = 0;
vii bt(100), tat(100), pt(100);
vii times, process_no;
vector<pair<int, pair<int, int>>> process;

void print_table();
void gant_chart();
void FCFS();
void Average();

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    // taking inputs
    cin >> num;
    int prior, brst;

    for (int i = 1; i <= num; i++)
    {
        cin >> prior >> brst;
        process.pb({prior, {i, brst}});
        bt[i] = brst;
        pt[i] = prior;
    }
    SORT(process);

    cout << "PRIORITY SCHEDULING ALGORITHM IMPLEMENTATION:" << nl << nl;
    FCFS();
    print_table();
    Average();
    gant_chart();

    return 0;
}

void FCFS()
{
    times.pb(0);
    int pri, prc, brs;
    for (int i = 0; i < process.size(); i++)
    {
        pri = process[i].ff;
        prc = process[i].ss.ff;
        brs = process[i].ss.ss;

        total_time += brs;
        tat[prc] = total_time;
        times.pb(total_time);
        process_no.pb(prc);
    }
}

void print_table()
{
    cout << "---------------Table--------------" << nl;
    cout << "Process\tPriority\tBurst\tTurnAround\tWaiting" << nl;
    for (int i = 1; i <= num; i++)
        cout << "P" << i << "\t\t" << pt[i] << "\t\t\t" << bt[i] << "\t\t" << tat[i] << "\t\t\t" << tat[i] - bt[i] << nl;
    cout << nl;
}

void Average()
{
    cout << "---------------Average values--------------" << nl;
    for (int i = 1; i <= num; i++)
    {
        turn_around += tat[i];
        waiting += tat[i] - bt[i];
    }
    cout << "Average Turn around time = " << turn_around / num << nl;
    cout << "Average Waiting time = " << waiting / num << nl;
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
Sample input:
5
10 3
1 1
2 4
1 5
5 2
*/