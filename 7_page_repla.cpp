#include <bits/stdc++.h>
using namespace std;

// FCFS Page Replacement
void FCFS(vector<int> pages, int capacity)
{
    unordered_set<int> memory;
    queue<int> order;
    int faults = 0;

    for (int page : pages)
    {
        if (memory.find(page) == memory.end())
        {
            faults++;
            if (memory.size() == capacity)
            {
                int old = order.front();
                order.pop();
                memory.erase(old);
            }
            memory.insert(page);
            order.push(page);
        }
    }

    cout << "FCFS Page Faults: " << faults << endl;
}

// LRU Page Replacement
void LRU(vector<int> pages, int capacity)
{
    unordered_set<int> memory;
    unordered_map<int, int> recent;
    int faults = 0;

    for (int i = 0; i < pages.size(); i++)
    {
        int page = pages[i];

        if (memory.find(page) == memory.end())
        {
            faults++;
            if (memory.size() == capacity)
            {
                int lru = pages[i];
                int least = i;
                for (int memPage : memory)
                {
                    if (recent[memPage] < least)
                    {
                        least = recent[memPage];
                        lru = memPage;
                    }
                }
                memory.erase(lru);
            }
            memory.insert(page);
        }
        recent[page] = i;
    }

    cout << "LRU Page Faults: " << faults << endl;
}

// Optimal Page Replacement
void Optimal(vector<int> pages, int capacity)
{
    unordered_set<int> memory;
    int faults = 0;

    for (int i = 0; i < pages.size(); ++i)
    {
        int page = pages[i];

        if (memory.find(page) == memory.end())
        {
            faults++;
            if (memory.size() == capacity)
            {
                int farthest = i, val = -1;

                for (int memPage : memory)
                {
                    int j;
                    for (j = i + 1; j < pages.size(); ++j)
                    {
                        if (pages[j] == memPage)
                            break;
                    }
                    if (j > farthest)
                    {
                        farthest = j;
                        val = memPage;
                    }
                }

                if (val != -1)
                    memory.erase(val);
                else
                    memory.erase(memory.begin());
            }
            memory.insert(page);
        }
    }

    cout << "Optimal Page Faults: " << faults << endl;
}

int main()
{
    int n, capacity;
    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter the page reference string:\n";
    for (int i = 0; i < n; ++i)
        cin >> pages[i];

    cout << "Enter frame capacity: ";
    cin >> capacity;

    cout << "\nChoose Replacement Algorithm:\n";
    cout << "1. FCFS\n2. LRU\n3. Optimal\nEnter choice: ";
    int choice;

    cin >> choice;

    switch (choice)
    {
    case 1:
        FCFS(pages, capacity);
        break;
    case 2:
        LRU(pages, capacity);
        break;
    case 3:
        Optimal(pages, capacity);
        break;
    default:
        cout << "Invalid choice\n";
    }

    return 0;
}


/*
12
7 0 1 2 0 3 0 4 2 3 0 3
3
*/