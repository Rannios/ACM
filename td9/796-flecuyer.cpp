#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <tuple>
#include <queue>
#include <algorithm>

#define INF 100000000

using namespace std;

// 796 - Critical Links


typedef pair<int, int> pii;

int dfs( // a lot of parameters
		const vector<vector<int>> &adj,
		vector<int> &dfs_num,
		vector<int> &dfs_low,
		int parent,
		int vertex,
		int timer,
		vector<pii> &bridges )
{
	if(dfs_num[vertex])
		return dfs_num[vertex];

	dfs_num[vertex] = timer;
	int dlow = timer;
	for(int i=0; i<adj[vertex].size(); i++)
	{
		int neighbor = adj[vertex][i];
		if(neighbor == parent)	continue;
		else
		{
			bool already = (dfs_num[neighbor] > 0);
			int nextVal = dfs(adj, dfs_num, dfs_low, vertex, neighbor, timer + 1, bridges);

			if(!already && nextVal > dfs_num[vertex])
				bridges.push_back(make_pair(min(vertex, neighbor), max(vertex, neighbor)));

			dlow = min(dlow, nextVal);
		}		
	}

	dfs_low[vertex] = dlow;
	return dlow;
}


int main()
{
	int N;
	while(cin >> N)
	{
		vector<vector<int>> adj(N);
		for(int i=0; i<N; i++)
		{
			int vertex, nb_neighbor;
			scanf("%d (%d)", &vertex, &nb_neighbor);

			while(nb_neighbor-- > 0)
			{
				int neighbor;
				cin >> neighbor;
				adj[vertex].push_back(neighbor);
			}
		}

		vector<int> dfs_num(N, 0);
		vector<int> dfs_low(N, 0);
		vector<pii> bridges;

		for(int i=0; i<N; i++)
        	dfs(adj, dfs_num, dfs_low, -1, i, 1, bridges);

		sort(bridges.begin(), bridges.end());
        cout << bridges.size() << " critical links" << endl;

     	for(int i=0; i<bridges.size(); i++)
          	cout << bridges[i].first << " - " << bridges[i].second << endl;
        cout << endl;
	}

	return 0;
}