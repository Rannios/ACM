#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <tuple>

#define INF 1000000

using namespace std;

// 11506 - Angry Programmer


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

int vIn(int v) { return 2*(v-1); }
int vOut(int v) { return 2*(v-1)+1; }
int main()
{
	int M, W;
	while(cin >> M >> W && (M || W))
	{
		matrix vertices(2*M, vec(2*M, 0));

		for(int i=0; i<M-2; i++)
		{
			int v, c;
			cin >> v >> c;
			vertices[vIn(v)][vOut(v)] = c; // cost to break computer v
		}

		for(int i=0; i<W; i++)
		{
			int u,v,c;
			cin >> u >> v >> c;
			vertices[vOut(v)][vIn(u)] = c; // cost to cut wire (u,v)
			vertices[vOut(u)][vIn(v)] = c;
		}

		matrix max_flow = EdmondsKarp(vertices, vOut(1), vIn(M));
		int total_flow = 0;
		for(int i=1; i<=M; i++)
			total_flow += max_flow[vOut(1)][vIn(i)];

		cout << total_flow << endl;
	}
	
	return 0;
}