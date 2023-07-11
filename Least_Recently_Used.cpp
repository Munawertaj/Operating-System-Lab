#include <bits/stdc++.h>
using namespace std;

int last_update[100] = {0};
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

void LRU(int page)
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
        if (last_update[x] < value)
        {
            value = last_update[x];
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
        last_update[page] = time++;
        cout << page << "--> ";

        if (!check(page))
        {
            LRU(page);
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