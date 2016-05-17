#include <iostream>
#include <sstream>
#include <cmath>
#include <tuple>

using namespace std;


typedef tuple<long, long, long, long> matrix; // "à l'arrache" implementation of 2x2 matrix

matrix fois(matrix A, matrix B) // 2x2 matix multiplication "à l'arrache"
{
    return make_tuple( get<0>(A)*get<0>(B)+get<1>(A)*get<2>(B), get<0>(A)*get<1>(B)+get<1>(A)*get<3>(B),get<2>(A)*get<0>(B)+get<3>(A)*get<2>(B), get<2>(A)*get<1>(B)+get<3>(A)*get<3>(B) );
}

matrix modulo(matrix M, int mod)
{
    return make_tuple( get<0>(M) % mod, get<1>(M) % mod, get<2>(M) % mod, get<3>(M) % mod );
}

matrix puissance(matrix M, const long n, const long mod) // fast exponentiation
{
    if(n == 0) return make_tuple(1,0,0,1);
    else
    {
        M = modulo(M, mod);
        matrix tmp = puissance(M, n/2, mod);
        tmp = fois(tmp, tmp);
        tmp = modulo(tmp, mod);
        if(n%2)
            return modulo(fois(tmp, M), mod);
        else
            return modulo(tmp, mod);
    }
}

int main()
{
    long n; int m;

    while(cin >> n >> m)
    {
        int mod = pow(2, m); // <= 1'048'576 = 2^20

        matrix F = make_tuple(1,1,1,0);

        F = puissance(F, n, mod);

        cout << get<1>(F) << endl;
    }

    return 0;
}
