#include <iostream>
#include <iomanip>
#include <vector>

#define INF 999

using namespace std;

// 821 - Page Hopping


int main()
{
	int n(100), a, b, c(0);
	while(cin >> a >> b && a > 0 && b > 0)
	{
		c++;
		vector<vector<int>> adj(n, vector<int>(n, INF));

		do
			adj[a-1][b-1] = 1;
		while(cin >> a >> b && a > 0 && b > 0);

		for(int k=0; k<n; k++) // Floyd again
		for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

		double sum(0);
		int by(0);
		for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
		{
			if(i!=j && adj[i][j] < INF)
			{
				sum += adj[i][j];
				by ++;
			}
		}

		cout << "Case " << c <<": average length between pages = ";
		cout << fixed << setprecision(3) << sum / by;
		cout << " clicks" << endl;
	}

	return 0;
}