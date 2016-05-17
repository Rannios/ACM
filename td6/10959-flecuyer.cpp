#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include <list>

using namespace std;

// 10959 - The Party, Part I


void update_giovanni(vector<list<int>> &adj, list<int> neighborhood, vector<int> &degs, int dancer, int degree)
{
    if(degree < degs[dancer])
    {
        degs[dancer] = degree;
        while(!neighborhood.empty())
        {
            int partner = neighborhood.front();
            update_giovanni(adj, adj[partner], degs, partner, degree+1);
            neighborhood.pop_front();
        }
    }
}

int main()
{
    int c, P, D;
    cin >> c;
    while(c-- > 0 && cin >> P >> D)
    {
        vector<list<int>> adj(P);
        for(int i=0; i<D; i++) // creation de la matrice d'adjacence
        {
            int tmp1, tmp2;
            cin >> tmp1 >> tmp2;
            (adj[tmp1]).push_back(tmp2);
            (adj[tmp2]).push_back(tmp1);
        }

        vector<int> giovanni(P, P+1);
        update_giovanni(adj, adj[0], giovanni, 0, 0);

        for(int i=1; i<P; i++)
            cout << giovanni[i] << endl;
        if(c) cout << endl;
    }

    return 0;
}
