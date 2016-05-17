#include <iostream>
#include <iomanip>
#include <vector>

#define INF 1000000000

using namespace std;

// 1112 - Mice and Maze


int main()
{
	int c, N, E, T, M;
	cin >> c;
	while(c-- > 0 && cin >> N >> E >> T >> M)
	{
		vector<vector<int>> adj(N, vector<int>(N, INF));
		for(int i=0; i<N; i++)
			adj[i][i] = 0;

		while(M--)
		{
			int a, b, t;
			cin >> a >> b >> t;
			adj[a-1][b-1] = min(t, adj[a-1][b-1]);
		}

		// Disjkstra, ca marche pas
		// Floyd O(N³) with N<100 so N³<10⁶
		for(int k=0; k<N; k++)
		for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

		int accessible(0);
		for(int i=0; i<N; i++)
			accessible += (adj[i][E-1] <= T);

		cout << accessible << endl;
		if(c > 0) cout << endl;
	}

	return 0;
}