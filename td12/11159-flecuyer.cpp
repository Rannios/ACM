#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <tuple>

#define INF 1000000

using namespace std;

// 11159 - Factors and Multiples


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
			if(x >= 0)	f[x][y] += augment;
			else		f[y][x=-x-1] -= augment;
		}
	}
	return f;
}


int main()
{
	int T;
	cin >> T;
	for(int t=1; t<=T; t++)
	{
		int n, m, tmp;
		vec A, B;
		cin >> n;
		for(int i=0; i<n && cin >> tmp; i++)
			A.push_back(tmp);
		
		cin >> m;
		matrix adj(n+m+2, vec(n+m+2, 0));
		
		for(int i=0; i<n; i++)
			adj[0][1+i] = 1;

		for(int j=0; j<m && cin >> tmp; j++)
		{
			B.push_back(tmp);
			for(int i=0; i<n; i++)
			{
				if(tmp == 0 || (A[i] && tmp % A[i] == 0)) // multiple of A[i]
					adj[1+i][1+n+j] = 1;
			}
			adj[1+n+j][adj.size()-1] = 1;
		}

		matrix max_flow = EdmondsKarp(adj, 0, adj.size()-1);
		int total_flow = 0;
		for(int i=0; i<n; i++)
			total_flow += max_flow[0][1+i];

		cout << "Case "<< t <<": "<<total_flow << endl;
	}
	return 0;
}