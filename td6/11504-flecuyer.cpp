#include <iostream>
#include <vector>
#include <list>

using namespace std;

// 11504 - Dominos


typedef pair<int, int> pii;

bool new_visit(const vector<list<int>> &adj, list<int> children, vector<bool> &visited, vector<int> &topo, int vertex)
{
    if(visited[vertex])
        return false;
    else
    {
        visited[vertex] = true;
        while(!children.empty())
        {
            int child = children.front(); children.pop_front();
            new_visit(adj, adj[child], visited, topo, child);
        }
        topo.push_back(vertex);
        return true;
    }
}


int main()
{
    int c, n, m;
    cin >> c;
    while(c-- > 0 && cin >> n >> m)
    {
        vector<list<int>> adj(n);
        vector<bool> visited(n, false);
        vector<bool> revisited(n, false);
        vector<int> topo(n);

        while(m-- > 0)
        {
            int x, y;
            cin >> x >> y;
            (adj[x-1]).push_back(y-1);
        }

        for(int x=0; x<n; x++)
            new_visit(adj, adj[x], visited, topo, x);

        vector<int> retopo;
        for(int i=topo.size()-1; i>0; i--)
            retopo.push_back(topo[i]);

        int crucial(0);
        for(int i=0; i<n; i++)
            crucial += new_visit(adj, adj[ retopo[i] ], revisited, retopo, retopo[i]);

        cout << crucial << endl;
    }

    return 0;
}
