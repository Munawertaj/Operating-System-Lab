/*
Problem : SHORTEST REMAINING TIME FIRST SCHEDULING
Author: Tareq Munawer Taj
CSE, Rajshahi University
*/
#include <bits/stdc++.h>
#define pb push_back
#define pii pair<int, int>
#define vii vector<int>
#define SORT(v) sort(v.begin(), v.end())
#define ff first
#define ss second
#define nl "\n"
using namespace std;

int num;
double total_time = 0, turn_around = 0, waiting = 0;
vii bt(100), tat(100), wt(100), at(100), rt(100), ct(100);
vii times, process_no;
vector<pii> process(100);
vii check(100, 0);

bool remaining();
void SRTF();
void calculate_time();
void print_table();
void Average();
void gant_chart();

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    // taking inputs
    cin >> num;
    int arrival, brst;

    for (int i = 1; i <= num; i++)
    {
        cin >> arrival >> brst;
        process[i] = {arrival, brst};
        bt[i] = brst;
        at[i] = arrival;
        rt[i] = brst;
    }

    cout << "SHORTEST REMAINING TIME FIRST SCHEDULING ALGORITHM IMPLEMENTATION:" << nl << nl;
    SRTF();
    calculate_time();
    print_table();
    Average();
    gant_chart();

    return 0;
}

bool remaining()
{
    for (int i = 1; i <= num; i++)
    {
        if (rt[i] > 0)
            return true;
    }
    return false;
}

void SRTF()
{
    vector<pii> ready_queue;
    total_time = 0;
    int prc, rem;
    int x = 1;
    while (remaining())
    {
        for (int i = 1; i <= num; i++)
        {
            if (process[i].ff <= total_time && check[i] == 0)
            {
                ready_queue.pb({rt[i], i});
                check[i] = 1;
            }
        }
        SORT(ready_queue);
        if (ready_queue.size() == 0)
        {
            total_time++;
            continue;
        }
        else
        {
            int i = 0;
            while (ready_queue[i].ff == 0)
                i++;

            prc = ready_queue[i].ss;
            rt[prc]--;
            ready_queue[i].ff--;
            if (process_no.size() == 0 || process_no.back() != prc)
            {
                times.pb(total_time);
                process_no.pb(prc);
            }
            total_time++;
        }
    }
    times.pb(total_time);
}

void calculate_time()
{
    // Completion Time
    for (int i = 0; i < process_no.size(); i++)
        ct[process_no[i]] = times[i + 1];

    // Turn around time = Completion Time - Arrival Time
    // Waiting time = Turn around time - Burst time
    for (int i = 1; i <= num; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
}

void print_table()
{
    cout << "---------------Table--------------" << nl;
    cout << "Process\tArrival\tBurst\tCompletion\tTurnAround\tWaiting" << nl;
    for (int i = 1; i <= num; i++)
        cout << "P" << i << "\t\t" << at[i] << "\t\t" << bt[i] << "\t\t" << ct[i] << "\t\t\t" << tat[i] << "\t\t\t" << wt[i] << nl;
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