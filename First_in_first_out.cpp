#include <bits/stdc++.h>
using namespace std;

bool check(int page, vector<int> frames)
{
    for (auto x : frames)
    {
        if (x == page)
            return true;
    }
    return false;
}

void print(vector<int> frames)
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

    vector<int> page_frames(total, -1), reference_string;
    int page;
    while (cin >> page)
        reference_string.push_back(page);

    int index = 0, page_fault = 0;
    for (int i = 0; i < reference_string.size(); i++)
    {
        page = reference_string[i];
        cout << page << "--> ";

        if (!check(page, page_frames)) // FIFO will be applied
        {
            page_frames[index] = page;
            index = (index + 1) % total;
            print(page_frames);
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