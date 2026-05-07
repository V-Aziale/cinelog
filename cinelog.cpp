// cinelog - watchlist tracker
// add file saving later, for now everything resets on close

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Entry
{
    string title;
    string status;
    int rating;
    // add more genre and type later
};

vector<Entry> entries;

void listAll()
{
    if (entries.size() == 0)
    {
        cout << "nothing here yet\n";
        return;
    }

    for (int i = 0; i < entries.size(); i++)
    {
        cout << i << ". " << entries[i].title << " | " << entries[i].status << " | " << entries[i].rating << "/10\n";
    }
}

void addEntry()
{
    Entry e;

    cout << "title: ";
    cin.ignore();
    getline(cin, e.title);

    cout << "status (watching / completed / dropped): ";
    getline(cin, e.status);

    cout << "rating (0-10): ";
    cin >> e.rating;

    entries.push_back(e);
    cout << "added!\n";
}

void deleteEntry()
{
    // crashes if you type a wrong number, fix later
    cout << "which number to delete? ";
    int idx;
    cin >> idx;

    entries.erase(entries.begin() + idx);
    cout << "deleted\n";
}

// To do: add edit, search, stats, file saving

int main()
{
    cout << "== cinelog ==\n";

    int choice = -1;

    while (choice != 0)
    {
        cout << "\n1. list\n";
        cout << "2. add\n";
        cout << "3. delete\n";
        cout << "0. quit\n";
        cout << "choice: ";
        cin >> choice;

        if (choice == 1)
            listAll();
        else if (choice == 2)
            addEntry();
        else if (choice == 3)
            deleteEntry();
        else if (choice == 0)
            cout << "bye\n";
        else
            cout << "invalid\n";
    }

    return 0;
}