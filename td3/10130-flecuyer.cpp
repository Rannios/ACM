#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

/*
    Dynamic Programming

    v(i, m) = maximal value when the first i objects can be bought and the maximal weight is m

    v(0, j) = 0
    v(i, j<=0) = 0
    v(i>0, j>0) = max( v(i-1, j-W[i]) + P[i] ; v(i-1, j) )
*/

int main()
{
    int T, N, G;
    cin >> T; // number of cases
    while(T > 0)
    {
        T --;

        cin >> N; // number of objects
        vector<int> P(N+1,0), W(N+1,0);
        for(int i=1; i<N+1; i++)
        {
            cin >> P[i] >> W[i]; // price and weight of each object
        }

        cin >> G; // number of family members
        vector<int> MW(G,0);
        int maxMW(0);
        for(int j=0; j<G; j++)
        {
            cin >> MW[j]; // maximal weight of each family member
            maxMW = max(maxMW, MW[j]);
        }

        vector<vector<int>> v(N+1);
        for(int j=0; j<=maxMW; j++) // v(0, j) = 0
            (v[0]).push_back(0);
        for(int i=1; i<=N; i++)
        {
            (v[i]).push_back(0); // v(i, 0) = 0
            for(int j=1; j<=maxMW; j++)
            {
                int obj_i_bought = (j - W[i] < 0) ? 0 : (v[i-1][ j - W[i] ] + P[i]);
                int obj_i_useless = v[i-1][j];

                (v[i]).push_back( max(obj_i_bought, obj_i_useless) );
            }
        }
        int totalValue(0);
        for(int j=0; j<G; j++)
            totalValue += v[N][MW[j]];

        cout << totalValue << endl;
    }

    return 0;
}
