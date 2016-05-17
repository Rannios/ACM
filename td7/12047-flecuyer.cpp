#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <tuple>
#include <queue>

#define INF 100000000

using namespace std;

// 12047 - Highest Paid Toll


typedef pair<int, int> pii;

class Edge
{
	public:
		int w, u, v;

		Edge(int origin, int destination, int weight) :
			w(weight),
			u(origin),
			v(destination) {}
};


int Dijkstra(vector<list<Edge>> &adj, vector<int> &distances, vector<bool> &visited, priority_queue<pii> &Q)
{
	while(!Q.empty())
	{
		int u = Q.top().second;	Q.pop();
		if(visited[u])
			continue;
		visited[u] = true;

		while(!adj[u].empty())
		{
			Edge e = adj[u].front(); adj[u].pop_front();
			if(distances[e.v] > distances[u] + e.w)
			{
				distances[e.v] = distances[u] + e.w;
				Q.push( make_pair(-distances[e.v], e.v) );
			}
		}
	}
}

int main()
{
	int testcases;
	cin >> testcases;
	while(testcases-- > 0)
	{
		int N, M, s, t, p;
		cin >> N >> M >> s >> t >> p;	s--; t--;
		vector<Edge> E;
		vector<list<Edge>> adj(N), coadj(N);

		for(int i=0; i<M; i++)
		{
			int u, v, c;
			cin >> u >> v >> c;	u--; v--;
			if(c > p)	continue;
			E.push_back(Edge(u, v, c));
			adj[u].push_back(Edge(u, v, c));
			coadj[v].push_back(Edge(v, u, c));
		}

	
		vector<int> accessibility(N, INF);		accessibility[s] = 0;
		vector<bool> visited(N, false);
		priority_queue<pii> Q;					Q.push(make_pair(0, s));

		Dijkstra(adj, accessibility, visited, Q);


		vector<int> coaccessibility(N, INF);	coaccessibility[t] = 0;
		vector<bool> covisited(N, false);
		Q.push(make_pair(0, t));

		Dijkstra(coadj, coaccessibility, covisited, Q);
		

		int maxToll = -1;
		for(int i=0; i<E.size(); i++)
		{
			Edge e = E[i];
			int path_cost = accessibility[e.u] + e.w + coaccessibility[e.v];
			if(path_cost <= p && e.w > maxToll)
				maxToll = e.w;		
		}

		cout << maxToll << endl;
	}

	return 0;
}