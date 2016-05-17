#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <cmath>
#include <tuple>
#include <algorithm>

#define INF 100000

using namespace std;

// make money


/*
    L'idée était d'implémenter une version modifiée de Floyd-Warshall, avec des chemins multiplicatifs,
    pour trouver la meilleure conversion cyclique.
    Mais j'ai abandonné quand vous avez parlé des histoires d'ordre lexicographique et tout, ça avait
    l'air trop compliqué !
*/
    
typedef pair<double, int> pid; // pair of double (conversion rate) and int (number of consersions)
typedef vector<pid> vid; // vector of (double, int)
typedef vector<vid> mid; // matrix of (double, int)


int main()
{
    int n;
    while(cin >> n)
    {
        mid conversion(n+1, vid(n));
        for(int i=0; i<n; i++)
        {
        	conversion[i][i] = make_pair(1, 0);
        	for(int j=0; j<n; j++)
        	{
        		if(i != j)
        		{
        			double rate; cin >> rate;
        			conversion[i][j] = make_pair(rate, 1);
        		}
        	}
        }

        for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
        	printf("%d,%d: %f, %d\n", i, j, conversion[i][j].first, conversion[i][j].second);
        }

        for(int k=0; k<n; k++)
        for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
        	double old_rate = conversion[i][j].first;
        	double new_rate = conversion[i][k].first * conversion[k][j].first;
        	int old_path = conversion[i][j].second;
        	int new_path = conversion[i][k].second + conversion[k][i].second;

          	if(new_rate >= old_rate)
        	{
        		new_path = min(new_path, old_path);
        		printf("floyd: %d,%d,%d: %f,%d\n", i,k,j, new_rate, new_path);
        	}
        	else
        	{
        		new_rate = old_rate;
        		new_path = old_path;
        	}

        	conversion[i][j] = make_pair(new_rate, new_path);
        }

        int lengthMin(100000+n);
        double validMin(-1);
        for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
        	if(conversion[i][j].first >= 1.01)
        	{
        		printf("mieux: %d,%d: %f,%d\n", i, j, conversion[i][j].first, conversion[i][j].second);
        		lengthMin = min(lengthMin, conversion[i][j].second);
        		validMin = conversion[i][j].first;
        	}
        }

        cout << lengthMin << endl;
    }

    return 0;
}