// CineLog - Media Watchlist Tracker

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Entry
{
    string title, type, genre, status;
    int rating;
};

vector<Entry> entries;

// ================================
//         HELPERS
// ================================

void divider() { cout << "  ----------------------------------------\n"; }

void header(string txt)
{
    cout << "\n  ========================================\n";
    cout << "    " << txt << "\n";
    cout << "  ========================================\n";
}

void clearBuffer() { cin.ignore(1000, '\n'); }

bool badInput()
{
    if (cin.fail())
    {
        cin.clear();
        clearBuffer();
        return true;
    }
    return false;
}

string pickStatus()
{
    int p;
    do
    {
        cout << "  1. Watching\n"
             << "  2. Completed\n"
             << "  3. Dropped\n"
             << "  4. Plan to Watch\n"
             << "  5. On Hold\n"
             << "  Pick: ";
        cin >> p;
        if (badInput() || p < 1 || p > 5)
            cout << "  Invalid. Try again.\n";
        else
            break;
    } while (true);
    clearBuffer();

    if (p == 1)
        return "Watching";
    if (p == 2)
        return "Completed";
    if (p == 3)
        return "Dropped";
    if (p == 4)
        return "Plan to Watch";
    return "On Hold";
}

string pickType()
{
    int p;
    do
    {
        cout << "  1. Movie\n"
             << "  2. Anime\n"
             << "  3. TV Show\n"
             << "  4. Asian Drama\n"
             << "  5. Documentary\n"
             << "  Pick: ";
        cin >> p;
        if (badInput() || p < 1 || p > 5)
            cout << "  Invalid. Try again.\n";
        else
            break;
    } while (true);
    clearBuffer();

    if (p == 1)
        return "Movie";
    if (p == 2)
        return "Anime";
    if (p == 3)
        return "TV Show";
    if (p == 4)
        return "Asian Drama";
    return "Documentary";
}

// ================================
//         FILE HANDLING
// ================================

void saveData()
{
    ofstream f("watchlog.txt");
    for (auto &e : entries)
        f << e.title << "\n"
          << e.type << "\n"
          << e.genre << "\n"
          << e.status << "\n"
          << e.rating << "\n---\n";
    f.close();
}

void loadData()
{
    ifstream f("watchlog.txt");
    if (!f)
        return;

    entries.clear();
    string line;

    while (getline(f, line))
    {
        if (line == "---")
            continue;

        Entry e;
        e.title = line;
        getline(f, e.type);
        getline(f, e.genre);
        getline(f, e.status);

        string r;
        getline(f, r);
        e.rating = stoi(r);

        getline(f, line); 
        entries.push_back(e);
    }

    f.close();
}

// ================================
//         DISPLAY
// ================================

void printEntry(int i, Entry &e)
{
    cout << "  [" << i << "] " << e.title << "\n"
         << "      Type   : " << e.type << "\n"
         << "      Genre  : " << e.genre << "\n"
         << "      Status : " << e.status << "\n"
         << "      Rating : " << e.rating << "/10\n";
    divider();
}

void printList()
{
    if (entries.empty())
    {
        cout << "  Nothing here yet.\n";
        return;
    }
    divider();
    for (int i = 0; i < entries.size(); i++)
        printEntry(i, entries[i]);
}

void listAll()
{
    header("WATCHLIST");
    if (entries.empty())
    {
        cout << "  Nothing here yet.\n";
        return;
    }
    for (int i = 0; i < entries.size(); i++)
        printEntry(i, entries[i]);
}

// ================================
//         ADD
// ================================

void addEntry()
{
    header("ADD ENTRY");

    Entry e;

    do
    {
        cout << "  Title  : ";
        getline(cin, e.title);
        if (e.title.empty())
            cout << "  Title cannot be empty. Try again.\n";
    } while (e.title.empty());

    cout << "  Type   :\n";
    e.type = pickType();

    do
    {
        cout << "  Genre  : ";
        getline(cin, e.genre);
        if (e.genre.empty())
            cout << "  Genre cannot be empty. Try again.\n";
    } while (e.genre.empty());

    cout << "  Status :\n";
    e.status = pickStatus();

    do
    {
        cout << "  Rating (0-10): ";
        cin >> e.rating;
        if (badInput() || e.rating < 0 || e.rating > 10)
            cout << "  Invalid. Must be between 0 and 10. Try again.\n";
        else
            break;
    } while (true);

    entries.push_back(e);
    saveData();
    cout << "\n  Entry added!\n";
}

// ================================
//         EDIT
// ================================

void editEntry()
{
    header("EDIT ENTRY");
    if (entries.empty())
    {
        cout << "  Nothing to edit.\n";
        return;
    }

    printList();

    int idx;
    do
    {
        cout << "  Which number to edit? ";
        cin >> idx;
        if (badInput() || idx < 0 || idx >= entries.size())
            cout << "  Invalid. Try again.\n";
        else
            break;
    } while (true);
    clearBuffer();

    auto &e = entries[idx];
    cout << "\n  Editing: " << e.title << "\n";
    divider();

    int field;
    do
    {
        cout << "  What do you want to edit?\n"
             << "  1. Title   (current: " << e.title << ")\n"
             << "  2. Type    (current: " << e.type << ")\n"
             << "  3. Genre   (current: " << e.genre << ")\n"
             << "  4. Status  (current: " << e.status << ")\n"
             << "  5. Rating  (current: " << e.rating << "/10)\n"
             << "  Pick: ";
        cin >> field;
        if (badInput() || field < 1 || field > 5)
            cout << "  Invalid. Try again.\n";
        else
            break;
    } while (true);
    clearBuffer();

    if (field == 1)
    {
        string newTitle;
        do
        {
            cout << "  New Title: ";
            getline(cin, newTitle);
            if (newTitle.empty())
                cout << "  Title cannot be empty. Try again.\n";
        } while (newTitle.empty());
        e.title = newTitle;
    }
    else if (field == 2)
    {
        cout << "  New Type:\n";
        e.type = pickType();
    }
    else if (field == 3)
    {
        string newGenre;
        do
        {
            cout << "  New Genre: ";
            getline(cin, newGenre);
            if (newGenre.empty())
                cout << "  Genre cannot be empty. Try again.\n";
        } while (newGenre.empty());
        e.genre = newGenre;
    }
    else if (field == 4)
    {
        cout << "  New Status:\n";
        e.status = pickStatus();
    }
    else if (field == 5)
    {
        do
        {
            cout << "  New Rating (0-10): ";
            cin >> e.rating;
            if (badInput() || e.rating < 0 || e.rating > 10)
                cout << "  Invalid. Must be between 0 and 10. Try again.\n";
            else
                break;
        } while (true);
    }

    saveData();
    cout << "\n  Updated!\n";
}

// ================================
//         DELETE
// ================================

void deleteEntry()
{
    header("DELETE ENTRY");
    if (entries.empty())
    {
        cout << "  Nothing to delete.\n";
        return;
    }

    printList();

    int idx;
    do
    {
        cout << "  Which number to delete? ";
        cin >> idx;
        if (badInput() || idx < 0 || idx >= entries.size())
            cout << "  Invalid. Try again.\n";
        else
            break;
    } while (true);
    clearBuffer();

    string confirm;
    do
    {
        cout << "  Delete \"" << entries[idx].title << "\"? (yes/no): ";
        getline(cin, confirm);
        for (auto &ch : confirm)
            ch = tolower(ch);
        if (confirm != "yes" && confirm != "no")
            cout << "  Invalid. Type yes or no.\n";
    } while (confirm != "yes" && confirm != "no");

    if (confirm == "yes")
    {
        entries.erase(entries.begin() + idx);
        saveData();
        cout << "  Deleted.\n";
    }
    else
    {
        cout << "  Cancelled.\n";
    }
}

// ================================
//         SEARCH
// ================================

void searchEntries()
{
    header("SEARCH");

    string q;
    do
    {
        cout << "  Keyword: ";
        getline(cin, q);
        if (q.empty())
            cout << "  Keyword cannot be empty. Try again.\n";
    } while (q.empty());

    for (auto &ch : q)
        ch = tolower(ch);

    bool found = false;
    for (int i = 0; i < entries.size(); i++)
    {
        string t = entries[i].title;
        for (auto &ch : t)
            ch = tolower(ch);

        if (t.find(q) != string::npos)
        {
            printEntry(i, entries[i]);
            found = true;
        }
    }

    if (!found)
        cout << "  No results for \"" << q << "\"\n";
}

// ================================
//         FILTER
// ================================

void filterByStatus()
{
    header("FILTER BY STATUS");
    cout << "  Filter by:\n";
    string s = pickStatus();
    divider();

    bool found = false;
    for (int i = 0; i < entries.size(); i++)
    {
        if (entries[i].status == s)
        {
            printEntry(i, entries[i]);
            found = true;
        }
    }

    if (!found)
        cout << "  No entries with status \"" << s << "\"\n";
}

// ================================
//         STATS
// ================================

void showStats()
{
    header("STATS");
    if (entries.empty())
    {
        cout << "  No entries yet.\n";
        return;
    }

    int watching = 0, completed = 0, dropped = 0, planTo = 0, onHold = 0;
    int total = 0, ratedCount = 0;

    for (auto &e : entries)
    {
        if (e.status == "Watching")
            watching++;
        else if (e.status == "Completed")
            completed++;
        else if (e.status == "Dropped")
            dropped++;
        else if (e.status == "Plan to Watch")
            planTo++;
        else if (e.status == "On Hold")
            onHold++;

        if (e.rating > 0)
        {
            total += e.rating;
            ratedCount++;
        }
    }

    cout << "  Total Entries  : " << entries.size() << "\n";
    divider();
    cout << "  Watching       : " << watching << "\n"
         << "  Completed      : " << completed << "\n"
         << "  Dropped        : " << dropped << "\n"
         << "  Plan to Watch  : " << planTo << "\n"
         << "  On Hold        : " << onHold << "\n";
    divider();

    if (ratedCount > 0)
    {
        cout << fixed << setprecision(2);
        cout << "  Average Rating : " << (double)total / ratedCount
             << "/10 (from " << ratedCount << " rated entries)\n";
        cout << defaultfloat; 
    }
    else
    {
        cout << "  No ratings yet.\n";
    }
}

// ================================
//         MAIN
// ================================

int main()
{
    loadData();

    cout << "\n  ========================================\n"
         << "            C I N E L O G               \n"
         << "       Media Watchlist Tracker           \n"
         << "  ========================================\n";

    int choice = -1;
    while (choice != 0)
    {
        cout << "\n  ---- MENU ----\n"
             << "  1. View Watchlist\n"
             << "  2. Add Entry\n"
             << "  3. Edit Entry\n"
             << "  4. Delete Entry\n"
             << "  5. Search\n"
             << "  6. Filter by Status\n"
             << "  7. Stats\n"
             << "  0. Quit\n"
             << "  Choice: ";
        cin >> choice;
        if (badInput())
        {
            cout << "  Invalid choice.\n";
            continue;
        }
        clearBuffer();

        if (choice == 1)
            listAll();
        else if (choice == 2)
            addEntry();
        else if (choice == 3)
            editEntry();
        else if (choice == 4)
            deleteEntry();
        else if (choice == 5)
            searchEntries();
        else if (choice == 6)
            filterByStatus();
        else if (choice == 7)
            showStats();
        else if (choice == 0)
            cout << "\n  Goodbye!\n";
        else
            cout << "  Invalid choice.\n";
    }

    return 0;
}
