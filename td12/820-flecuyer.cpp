#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <tuple>

#define INF 100000

using namespace std;

// 820 - Internet Bandwidth


typedef pair<int,int> pii;
typedef vector<int> vec;
typedef vector<vec> matrix;

vector<pii> augmenting_path(const matrix &R, int s, int t, const matrix &f)
{
    list<int> BFS; BFS.push_back(s);
    vector<bool> visited(f.size(), false);
    vector<pii> pred(f.size()); pred[s].second = INF;
    while(!visited[t] && !BFS.empty())
    {
        int x = BFS.front();  BFS.pop_front();
        visited[x] = true;
        for(int y=0; y<f.size(); y++)
        {
            if(visited[y]) continue;
            else if(R[x][y] > 0 && f[x][y] < R[x][y])
            {
                pred[y].first = + x;
                pred[y].second = + min(pred[x].second, R[x][y] - f[x][y]);
                BFS.push_back(y);
            }
            else if(R[y][x] > 0 && f[y][x] > 0)
            {
                pred[y].first = -(x+1); // to avoid x=-0
                pred[y].second = min(pred[x].second, f[y][x]);
                BFS.push_back(y);
            }
        }
    }
    return pred;
}

matrix EdmondsKarp(const matrix &R, int s, int t)
{
    matrix f(R.size(), vec(R.size(), 0));
    while(1)
    {
        vector<pii> path = augmenting_path(R, s, t, f);
        int x = t, augment = path[t].second;
        if(!augment) break;
        while(x != s)
        {
            int y = x;
            x = path[y].first;
            if(x >= 0)  f[x][y] += augment;
            else        f[y][x=-x-1] -= augment;
        }
    }
    return f;
}


int main()
{
    int n, id = 0;
    while(cin >> n && n > 0 )
    {
        int s, t, c; 
        cin >> s >> t >> c; s--; t--;
        matrix mat(n, vec(n, 0));
        while(c-- > 0)
        {
            int u, v, w;
            cin >> u >> v >> w;
            mat[u-1][v-1] += w;
            mat[v-1][u-1] += w;
        }

        matrix flot = EdmondsKarp(mat, s, t);
        int bandwidth = 0;
        for(int i=0; i<n; i++)
            bandwidth += flot[s][i];

        cout << "Network " << ++id << "\nThe bandwidth is " << bandwidth << "." << endl << endl;
    }

    return 0;
}