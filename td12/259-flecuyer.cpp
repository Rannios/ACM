#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <tuple>
#include <string>

#define INF 1000000
#define debug(msg) { cout << msg << endl; fflush(stdout); }
#define N 26+10+2

using namespace std;

// 259 - Software Allocation


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

char charoftask(int t) { return t + 64; }
int taskofchar(char c) { return c - 64; }
int main()
{
	string s;
	while(getline(cin, s) && s.size() > 1)
	{
		matrix vertices(N, vec(N, 0));
			
		for(int c=27; c<N-1; c++) // tous les ordinateurs peuvent accomplir une tache maximum
			vertices[c][N-1] = 1;

		int total = 0;
		do
		{
			int task = taskofchar(s[0]);
			total += (vertices[0][task] = s[1] - 48); // la tache Task doit être accomplie un certain nombre de fois
			for(int cursor = 3; s[cursor] != ';'; cursor++)
				vertices[task][s[cursor] - 48 + 27] = 1; // elle peut être faite une fois par l'ordi s[cursor]
		} while(getline(cin, s) && s.size() > 1);


		matrix max_flow = EdmondsKarp(vertices, 0, N-1); // calcul du flot max pouvant transiter dans ce réseau
		int total_flow = 0;
		for(int c=27; c<N-1; c++)
			total_flow += max_flow[c][N-1];

		if(total_flow < total) // si toutes les taches ne peuvent être exécutées
			cout << "!" << endl;
		else
		{
			for(int c=27; c<37 || (cout << endl && 0); c++)
				for(int t=1; t<=26 || (cout << "_" && 0) ; t++)
					if(max_flow[t][c] && cout << charoftask(t))
						break;
		}
	}

	return 0;
}
