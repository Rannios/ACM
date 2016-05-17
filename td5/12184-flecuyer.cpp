#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;

long long pgcd(long long a, long long b)
{
    if(b == 0) return a;
    else return pgcd(b, a%b);
}

int main()
{
    int t, c;
    cin >> t;
    while(t-- > 0 && cin >> c)
    {
        long long rep(0), maxResult(0);
        for(int i=0; i<c; i++)
        {
            long long tmp, total(0);
            for(int j=0; j<9; j++) // a1, ..., a9
            {
                cin >> tmp;
                total += tmp;
            }
            cin >> tmp;
            total -= tmp; // a10

            rep = pgcd(total, rep);
            maxResult = max(maxResult, tmp);
        }


        if(rep <= 1 || maxResult >= rep) cout << "impossible" << endl;
        else cout << rep << endl;
    }

    return 0;
}
