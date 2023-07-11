#include <bits/stdc++.h>
using namespace std;

int used_count[100] = {0};
vector<int> frames;

bool check(int page)
{
    for (auto x : frames)
    {
        if (x == page)
            return true;
    }
    return false;
}

void print()
{
    for (auto x : frames)
    {
        if (x == -1)
            cout << "- ";
        else
            cout << x << " ";
    }
}

void LFU(int page)
{
    for (int i = 0; i < frames.size(); i++)
    {
        if (frames[i] == -1)
        {
            frames[i] = page;
            return;
        }
    }
    int value = 100;
    int temp;
    for (auto x : frames)
    {
        if (used_count[x] < value)
        {
            value = used_count[x];
            temp = x;
        }
    }
    for (int i = 0; i < frames.size(); i++)
    {
        if (frames[i] == temp)
        {
            frames[i] = page;
            return;
        }
    }
}

int main()
{
    int total; // Total number of frames
    cin >> total;

    for (int i = 0; i < total; i++)
        frames.push_back(-1);

    int page, index = 0, page_fault = 0, time = 1;

    while (cin >> page)
    {
        used_count[page]++;
        cout << page << "--> ";

        if (!check(page))
        {
            LFU(page);
            print();
            page_fault++;
        }
        cout << endl;
    }
    cout << "\nTotal number of page fault = " << page_fault << endl;

    return 0;
}

/*
Sample input:
3
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
*/