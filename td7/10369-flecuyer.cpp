#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <cmath>
#include <tuple>
#include <algorithm>

#define INF 100000

using namespace std;

// 10369 - Arctic Network

/*
	We have to find the minimum spanning forest with P-S connected components.
	Let us use Kruskal's algorithm with Union-Find structure. Then we only have
	to modify it in order to stop when P-S components have been connected.
	It gives us the minimum spanning forest, which is also the minimum
	bottleneck spanning forest.
*/

typedef vector<vector<double>> matrix;
typedef pair< double, pair<int,int> > edge;
typedef pair<int,int> outpost;

class UFset
{
	public:
		UFset* parent;
		int card;
		int id;
		UFset(int num) : parent(NULL), card(1), id(num) {  }
		void setParent(UFset *p)
		{
			this->parent = p;
		}
		UFset* find()
		{
			if(this->parent == NULL) { return this; }
			else { return this->parent->find();}
		}
		UFset* unionn(UFset *y)
		{
			if(this->card > y->card)
				return y->unionn(this);
			else
			{
				UFset *xRoot = this->find(), *yRoot = y->find();
				yRoot->card += xRoot->card;
				xRoot->setParent(yRoot);
				return yRoot;
			}
		}
};

double geoDistance(const outpost &a, const outpost &b)
{
	double dx(a.first - b.first), dy(a.second - b.second);
	return sqrt(dx*dx + dy*dy);
}

edge make_edge(const int outpost1, const int outpost2, const double &dist)
{
	return make_pair(dist, make_pair(outpost1, outpost2));
}

int main()
{
    int N, S, P;
    cin >> N;
    while(N-- > 0 && cin >> S >> P)
    {
        matrix adj(P, vector<double>(P, 0));
        vector<outpost> posts;
        

        for(int i=0; i<P; i++)
        {
            int x, y;
            cin >> x >> y;
            outpost tmp(make_pair(x, y));
            posts.push_back(tmp);
        }
        
        vector<edge> edges;
        for(int i=0; i<P; i++)
        for(int j=i+1; j<P; j++)
        {
			double d = geoDistance(posts[i], posts[j]);
			adj[i][j] = d; adj[j][i] = d;
			edges.push_back(make_edge(i, j, d));
			edges.push_back(make_edge(j, i, d));
		}
		
		list<edge> A;
		vector<UFset> sets; 
		for(int i=0; i<P; i++)
		{
			UFset tmp(i);
			sets.push_back(tmp);
		}

		int components(P);
		double max_dist(0.0);
		
		sort(edges.begin(), edges.end());
		for(int k=0; k<edges.size() && components > S; k++)
		{
			edge e = edges[k];
			int u(e.second.first), v(e.second.second);
			if(sets[u].find() != sets[v].find())
			{
				sets[u].unionn(&sets[v]);
				A.push_back(e);
				max_dist = max(max_dist, e.first);
				components--;
			}
		}

        cout << fixed << setprecision(2) << max_dist << endl;
    }

    return 0;
}