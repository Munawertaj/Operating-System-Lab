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

int num, quantam, total = 0;
double turn_around = 0, waiting = 0;
vii tat(100), bt(100);
vii times, process_no;
queue<pii> process;

void RoundRobin();
void print_table();
void Average();
void gant_chart();

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> num >> quantam;
    int b;
    for (int i = 1; i <= num; i++)
    {
        cin >> b;
        process.push({i, b});
        bt[i] = b;
    }

    cout << "ROUND ROBIN SCHEDULING ALGORITHM IMPLEMENTATION:" << nl << nl;
    RoundRobin();
    print_table();
    Average();
    gant_chart();
}

void RoundRobin()
{
    pii temp;
    int p_num, b_time;
    times.pb(0);
    while (!process.empty())
    {
        temp = process.front();
        process.pop();
        p_num = temp.ff;
        b_time = temp.ss;

        if (b_time <= quantam)
            total += b_time;
        else
        {
            total += quantam;
            b_time -= quantam;
            process.push({p_num, b_time});
        }
        tat[p_num] = total;
        times.pb(total);
        process_no.pb(p_num);
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
