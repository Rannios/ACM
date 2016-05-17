#include <iostream>
#include <iomanip>
#include <vector>
#include <list>

#define INF 1000000000

using namespace std;

// 10557 - XYZZY


class Edge
{
	public:
		int w;
		int u;
		int v;

		Edge(int origin, int destination, int weight) :
			w(weight),
			u(origin),
			v(destination) {}
};

int Bellman_Ford(const vector<Edge> &E, vector<int> &energies, int iter)
{
	if(!iter)
		return 0;

	for(int i=0; i<E.size(); i++)
	{
		Edge e = E[i];
		if(energies[e.u] > 0)
			energies[e.v] = max(energies[e.v], energies[e.u] + e.w);
	}

	return Bellman_Ford(E, energies, iter-1);
}

bool DFS(vector<list<int>> &adj, int vertex, const int goal)
{
	if(vertex == goal)
		return true;

	while(!adj[vertex].empty())
	{
		int child = adj[vertex].front();
		adj[vertex].pop_front();
		if(DFS(adj, child, goal))
			return true;
	}

	return false;
}

int main()
{
	int n;
	while(cin >> n && n >= 0)
	{
		vector<Edge> E;
		vector<list<int>> adj(n);

		for(int u=0; u<n; u++)
		{
			int energy, doorways;
			cin >> energy >> doorways;
			for(int i=0; i<doorways; i++)
			{
				int v;	cin >> v;
				E.push_back(Edge(u, v-1, energy));
				adj[u].push_back(v-1);
			}
		}

		vector<int> energies(n, -INF);
		energies[0] = 100;
		Bellman_Ford(E, energies, n);

		
		int in_cycle = -1;
		for(int i=0; i<E.size() && in_cycle < 0; i++)
		{
			Edge e = E[i];
			if(energies[e.u] + e.w > energies[e.v] && energies[e.v] > 0)
				in_cycle = e.v;			
		}

		if(energies[n-1] > 0)
			cout << "winnable" << endl;
		else if(in_cycle >= 0 && DFS(adj, in_cycle, n-1))
			cout << "winnable" << endl;
		else 
			cout << "hopeless" << endl;
	}

	return 0;
}