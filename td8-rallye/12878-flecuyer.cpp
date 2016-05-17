#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <cmath>
#include <tuple>
#include <algorithm>
#include <queue>

#define INF 1000000000

using namespace std;

// 12878 - Flowery Trails


typedef pair<int, int> pii;
typedef vector<vector<pii>> matrix;

void update_dist(const matrix &a, vector<int> &d, priority_queue<pii> &q, vector<list<int>> &prede, int s1, int s2)
{
	int new_dist = d[s1] + a[s1][s2].first;
	if(new_dist < d[s2])
	{
		d[s2] = new_dist;
		list<int> new_prede;
		new_prede.push_back(s1);
		prede[s2] = new_prede;
		q.push( make_pair(-new_dist, s2) );
	}
	else if(d[s2] == new_dist)
	{
		prede[s2].push_back(s1);
	}
}


int flower(const matrix &a, vector<list<int>> &predes, vector<bool> &visited, int vertex)
{
	if(vertex == 0)
		return 0;
	else if(visited[vertex])
		return 0;
	else
	{
		visited[vertex] = true;
		//cout << "lol "<<vertex<<endl;
		int total(0);
		while(!predes[vertex].empty())
		{
			int p = predes[vertex].front(); predes[vertex].pop_front();
			//cout << "\t -- "<<p<<" : "<< a[vertex][p].second << " :" << endl;
			total += a[vertex][p].second + flower(a, predes, visited, p);
		}
		return total;
	}
}

int main()
{
	int P, T;
	while(cin >> P >> T)
	{
		matrix adj(P, vector<pii>(P, make_pair(INF,0)));
		for(int i=0; i<T; i++)
		{
			int p1, p2, l;
			cin >> p1 >> p2 >> l;
			
			if(l <= adj[p1][p2].first)
			{
				int min_dist(l), flower_dist(l);
				if(l == adj[p1][p2].first) { flower_dist += adj[p1][p2].second; }
				
				adj[p1][p2] = make_pair( min_dist, flower_dist );
				adj[p2][p1] = make_pair( min_dist, flower_dist );
			}
			
			//cout << "f:" << adj[p1][p2].second << endl;
		}

		priority_queue<pii> q;
		q.push( make_pair(0,0) );
		
		vector<int> dist(P, INF);
		dist[0]= 0;
		
		vector<bool> visited(P, false);
		vector<list<int>> prede(P);
		
		int s;
		//while( (s=index_min_true(q, visited)) >= 0)
		for(int i=0; i<P; i++)
		{
			s = q.top().second; q.pop();
			for(int t=0; t<P; t++)
			{
				update_dist(adj, dist, q, prede, s, t);
			}
		}
		
		vector<bool> visited2(P, false);
		int total_flower = flower(adj, prede, visited2, P-1);
		cout << total_flower*2 << endl;
	}
	return 0;
}
