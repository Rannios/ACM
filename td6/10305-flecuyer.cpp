#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include <list>

using namespace std;

// 10305 - Ordering Tasks


int topologise(const vector<list<int>> &adj, list<int> dependances, vector<int> &topo, int task, int height)
{
    int h_max = 0;
    if(topo[task] == 0)
    {
        h_max = height;
        topo[task] = height;
        while(!dependances.empty())
        {
            int child = dependances.front();
            h_max = max(h_max, topologise(adj, adj[child], topo, child, height+1));
            dependances.pop_front();
        }
    }
    return h_max;
}

int min_key(const vector<int> &t)
{
    int j=0;
    for(int i=1; i<t.size(); i++)
        if(t[i] < t[j]) { j=i; }

    return j;
}

int main()
{
    int n, m;
    while(cin >> n >> m && n)
    {
        vector<list<int>> adj(n);
        vector<int> deg_in(n, 0);
        vector<int> deg_out(n, 0);
        vector<int> topo(n, 0);
        for(int i=0; i<m; i++) // creation de la matrice d'adjacence
        {
            int tmp1, tmp2;
            cin >> tmp1 >> tmp2;
            (adj[tmp1-1]).push_back(tmp2-1);
            deg_in[tmp2-1]++; deg_out[tmp1-1]++;
        }

        int height = 0;
        for(int i=0; i<n; i++)
        {
            if(deg_in[i] == 0)
                height = topologise(adj, adj[i], topo, i, height+1);
        }

        for(int i=0; i<n; i++)
        {
            int j = min_key(topo);
            cout << (j+1) << endl;
            topo[j] = n+10;
        }
        cout << endl;
    }

    return 0;
}
