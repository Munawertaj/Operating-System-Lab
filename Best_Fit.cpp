#include <bits/stdc++.h>
using namespace std;

int main()
{
    int num_of_holes;
    cin >> num_of_holes;
    vector<int> holes(num_of_holes);
    for (int i = 0; i < num_of_holes; i++)
        cin >> holes[i];

    int memory_size;
    cin >> memory_size;

    sort(holes.begin(), holes.end());
    for (int i = 0; i < num_of_holes; i++)
    {
        if (holes[i] >= memory_size)
        {
            cout << "The process is allocated to " << holes[i] << "MB memory hole...";
            return 0;
        }
    }
    cout << "No suitable memory hole is available!!!!!";
}

/*

Input:
7
12 3 5 32 43 29 7
27

*/