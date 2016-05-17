#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
    Dynamic Programming

    for all i belonging to [0, number of coins-1]
    for all a natural integer (the amount of money)

    let us define :
    C(0, 0) = 1
    C(0, a!=0) = 0
    C(i>0, 0) = 1
    C(i>0, a<0) = 0
    C(i>0, a>0) = C(i-1, a) + C(i, a-coin[i])
*/

int main()
{
    vector<int> coins{0,1,5,10,25,50};

    int a;
    while(cin >> a)
    {
        long long comb(1);

        vector<vector<long long>> C(coins.size());

        (C[0]).push_back(1); // C(0,0) = 1
        for(int j=1; j<=a; j++)
            (C[0]).push_back(0); // C(0, a!=0) = 0

        for(int i=1; i < C.size(); i++)
        {
            (C[i]).push_back(1); // C(i>0, 0) = 1

            for(int j=1; j<=a; j++)
            {
                long long coin_i_useless = C[i-1][j];
                long long coin_i_used = (j-coins[i] < 0)? 0 : C[i][ j-coins[i] ]; // C(i>0, a<0) = 0

                (C[i]).push_back(coin_i_useless + coin_i_used);
            }
        }

        comb = C[coins.size()-1][a];

        if(comb == 1) cout << "There is only 1 way";
        else cout << "There are " << comb << " ways";

        cout << " to produce " << a << " cents change." << endl;
    }

    return 0;
}
