#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include <list>

using namespace std;

// 11396 - Claw Decomposition


bool parity_ok(const vector<list<int>> &adj, list<int> neighborhood, vector<int> &parities, int vertex, int parity)
{
    if(parities[vertex] < 0)
    {
        bool good = true;
        parities[vertex] = parity;
        while(!neighborhood.empty())
        {
            int next = neighborhood.front();
            good = good && parity_ok(adj, adj[next], parities, next, (parity+1)%2);
            neighborhood.pop_front();
        }
        return good;
    }
    else
        return (parities[vertex] == parity);
}

int main()
{
    int V;
    while(cin >> V && V)
    {
        int a, b;
        vector<list<int>> adj(V);
        while(cin >> a >> b && a && b)
        {
            (adj[a-1]).push_back(b-1);
            (adj[b-1]).push_back(a-1);
        }

        vector<int> parities(V, -1);
        if(parity_ok(adj, adj[0], parities, 0, 0))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}
