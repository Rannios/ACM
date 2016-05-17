#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include <list>
#include <queue>
#include <utility>

using namespace std;

// 11631 - Dark roads


typedef pair<int, int> pii;

int main()
{
    int m, n;
    while(cin >> m >> n && m && n)
    {
        int total_km(0);
        vector<list<pii>> adj(m);
        for(int i=0; i<n; i++)
        {
            int x, y, z;
            cin >> x >> y >> z;
            (adj[x]).push_back(make_pair(y, z));
            (adj[y]).push_back(make_pair(x, z));
            total_km += z;
        }

        priority_queue<pii> remaining;
        remaining.push(make_pair(0, 0));
        for(int i=1; i<m; i++)
        {
            remaining.push(make_pair(-total_km-1, i));
        }

        vector<int> cost(m, total_km+1);
        cost[0] = 0;
        vector<bool> chosen(m, false);
        chosen[0] = true;

        while(!remaining.empty())
        {
            int t = (remaining.top()).second;
            remaining.pop();
            chosen[t] = true;

            while(!(adj[t]).empty())
            {
                pii edge = (adj[t]).front();
                int u = edge.first;
                if(!chosen[u] && cost[u] > edge.second)
                {
                    cost[u] = edge.second;
                    remaining.push(make_pair(-edge.second, u));
                }
                (adj[t]).pop_front();
            }
        }

        long long total_cost(0);
        for(int i=0; i<m; i++)
            total_cost += cost[i];

        cout << total_km - total_cost << endl;
    }

    return 0;
}
