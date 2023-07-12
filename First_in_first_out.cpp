#include <bits/stdc++.h>
using namespace std;

int total; // Total number of frames
vector<int> frames;
int index = 0;

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

void FIFO(int page)
{
    frames[index] = page;
    index = (index + 1) % total;
}

int main()
{

    cin >> total;

    for (int i = 0; i < total; i++)
        frames.push_back(-1);

    int page, page_fault = 0;
    while (cin >> page)
    {
        cout << page << "--> ";
        if (!check(page)) // FIFO will be applied
        {
            FIFO(page);
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