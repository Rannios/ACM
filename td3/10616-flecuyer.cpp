#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

/*
    Dynamic Programming

    s(i, j, k) = number of ways to have a sum of i numbers among the first j numbers that is k modulus D

    s(0, j, 0) = 1
    s(0, j, k>0) = 0
    s(i>j, k) = 0 // impossible to take i numbers
    s(i>0, j>0, k>0) = s(i, j-1, k) + s(i-1, j-1, k-N[j] % D)
*/


// On va créer une map qui contient les valeurs déjà calculées de la fonction s
typedef tuple<int,int,int> sArgs; // en étiquette, un triplet (i, j, k)
typedef pair<bool,int> sReturn; // en valeur, un doublet (b, v), ou b=true si s(i,j,k) est déjà calculé, auquel cas v=s(i,j,k)
typedef map<sArgs, sReturn> sMap;


int s(const vector<int> &numbers, const int D, sMap &save, int i, int j, int k)
{
    sArgs arg = make_tuple(i,j,k);
    sReturn ret = save[arg];
    if( get<0>(ret) ) return get<1>(ret);
    else
    {
        int r;
        if(k == 0 && i == 0) r = 1;
        else if(i<=0) r = 0;
        else if(i>j) r = 0;
        else
        {
            int term1 = s(numbers, D, save, i, j-1, k);
            int term2 = s(numbers, D, save, i-1, j-1, (D+k-(numbers[j-1]%D))%D);
            r = term1 + term2;
        }

        save[arg] = make_pair(true, r);
        return r;
    }
}

int main()
{
    int N, Q, idSet(0);

    while(cin >> N >> Q && N != 0 && Q != 0) // for each set
    {
        idSet ++;

        cout << "SET "<< idSet <<":"<<endl;

        vector<int> numbers(N);
        for(int i=0; i<N; i++)
            cin >> numbers[i];

        for(int qi=0; qi<Q; qi++)
        {
            sMap save;
            cout << "QUERY "<< qi+1 <<": ";

            int D, M;
            cin >> D >> M;

            cout << s(numbers, D, save, M, N, 0) << endl;
        }
    }

    return 0;
}
