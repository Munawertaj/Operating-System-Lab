#include <bits/stdc++.h>

using namespace std;

// File Name Format: "F:\\C++ Codes\\Operating System Lab\\x.txt"

int main()
{
    string operation;
    cin >> operation;
    cin.ignore();
    if (operation == "Create")
    {
        string name;
        getline(cin, name);
        ofstream newFile(name.c_str());
        newFile << "File is created\n";
        newFile.close();
    }
    else if (operation == "Rename")
    {
        string oldname, newname;
        getline(cin, oldname);
        getline(cin, newname);
        int mark = rename(oldname.c_str(), newname.c_str());
        if (mark) 
        {
            cout << "Error renaming file!";
        }
        else cout << "File successfully renamed";
    }
    else if (operation == "Delete")
    {
        string fileName;
        getline(cin, fileName);
        int mark = remove(fileName.c_str());
        if (mark) 
        {
            cout << "Couldn't delete file!";
        }
        else cout << "File successfully deleted";
    }
    else if (operation == "Copy")
    {
        string from, to;
        getline(cin, from);
        getline(cin, to);
        ifstream sourceFile(from.c_str(), ios::binary);
        ofstream destinationFile(to.c_str(), ios::binary);
        string line;
        if (sourceFile and destinationFile)
        {
            while (getline(sourceFile, line))
            {
                destinationFile << line << "\n";
            }
            cout << "File successfully copied";
        }
        else cout << "Couldn't copy file!";
    }
    else if (operation == "Move")
    {
        string from, to;
        getline(cin, from);
        getline(cin, to);
        ifstream sourceFile(from.c_str(), ios::binary);
        ofstream destinationFile(to.c_str(), ios::binary);
        string line;
        if (sourceFile and destinationFile)
        {
            while (getline(sourceFile, line))
            {
                destinationFile << line << "\n";
            }
            remove(from.c_str());
            cout << "File successfully moved";
        }
        else cout << "Couldn't move file!";
    }
    else cout << "Invalid operation!";
}