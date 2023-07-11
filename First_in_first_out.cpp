#include <bits/stdc++.h>
using namespace std;

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

int main()
{
    int total; // Total number of frames
    cin >> total;

    for (int i = 0; i < total; i++)
        frames.push_back(-1);

    int page, index = 0, page_fault = 0;
    while (cin >> page)
    {
        cout << page << "--> ";
        if (!check(page)) // FIFO will be applied
        {
            frames[index] = page;
            index = (index + 1) % total;
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