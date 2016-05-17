#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <cmath>
#include <tuple>
#include <algorithm>

#define INF 1000000

using namespace std;

// gazon


typedef pair<double, double> pdd;

class Sprinkler
{
	public:
		int p, r;
		double left;
		double right;

		Sprinkler(const int ww, const int position, const int rayon): p(position), r(rayon)
		{
			
			double w = 0.5*ww; // necessite de prendre le rayon et pas le diametre de la pelouse
			double intersect(-INF);
			if(rayon < w)
			{
				this->left = -INF; this->right = -INF;
			}
			else
			{
				intersect = sqrt(rayon*rayon - w*w); // intersection between the circle and the upper border of the garden (Pythagore rpz)
				this->left = position - intersect;
				this->right = position + intersect;
			}
		}

		bool intersect(const Sprinkler* s)
		{
			if(s->left <= this->left && s->right >= this->left)
				return true;
			if(s->right >= this->right && s->left <= this->right)
				return true;
			if(s->left >= this->left && s->right <= this->right)
				return true;
			return false;
		}

		pdd interval()
		{
			return make_pair(this->left, this->right);
		}
};

typedef vector<Sprinkler> vS; // vector of sprinklers
typedef vector<vector<int>> mi; // matrix of int


int main()
{
    int n, l, w;
    while(cin >> n >> l >> w)
    {
        vS spr;
        Sprinkler debut(w, -1, 0);	debut.right = 0; 	debut.left = 0; 	// arroseur 0, fictif, correspondant au début du gazon
        Sprinkler fin(w, l+1, 0);	fin.right = l; 		fin.left = l;		// arroseur fictif n+1 correspondant à la fin du gazon
        
        spr.push_back(debut); 
        for(int i=0; i<n; i++) 												// création d'un graphe d'intervalles où chaque arroseur
        {																	// est donné avec ses intersections des bords du gazon
        	int pos(0), rayon(0);	cin >> pos >> rayon;					// à gauche et à droite
        	spr.push_back( Sprinkler(w, pos, rayon) );
        }
        spr.push_back(fin); 


        mi adj(n+2, vector<int>(n+2));
        for(int i=0; i<n+2; i++)
        for(int j=0; j<n+2; j++)
	    	adj[i][j] = spr[i].intersect(&spr[j]) ? 0 : INF;

       	/*
       		Pour trouver le plus court chemin entre les arroseurs (fictifs) 0 et n+1,
       		j'ai fait Floyd car je n'avais pas le temps de mettre en place Dijkstra
       		Mais du coup ça met bcp trop longtemps, mais normalement ça passe avec Dijkstra.
       	*/
        for(int k=0; k<n+2; k++)
        for(int i=0; i<n+2; i++)
        for(int j=0; j<n+2; j++)
        {
        	adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j] + 1);
        }

        cout << ((adj[0][n+1] < INF) ? adj[0][n+1] : -1) << endl;
    }

    return 0;
}