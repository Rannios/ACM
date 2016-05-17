#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

// naive check of primality
bool is_prime(const vector<ll> &primes, const ll &p)
{
    ll s = sqrt(p);
    for(int i=0; i<primes.size() && primes[i]<=s; i++)
        if(p%(primes[i]) == 0) return false;

    return true;
}

// Let us calculate the powers of prime numbers
void powers_of(vector<ll> &almostPrimes, const ll &maxi, const ll &p)
{
    ll power = p;
    while(maxi >= (power*=p))
        almostPrimes.push_back(power);
}

int main()
{
    int N;
    long long l, h;
    cin >> N;

    vector<ll> primes;
    vector<ll> almostPrimes;

    ll sqrMaxi = 1000000;
    ll maxi = sqrMaxi * sqrMaxi;

    primes.push_back(2);
    powers_of(almostPrimes, maxi, 2);

    for(ll i=3; i<=sqrMaxi; i+=2)
    {
        if(is_prime(primes, i))
        {
            primes.push_back(i);
            powers_of(almostPrimes, maxi, i);
        }
    }

    sort(almostPrimes.begin(), almostPrimes.end());

    while(N-- > 0 && cin >> l >> h)
    {
        ll sum(0);
        for(ll i=0; i<almostPrimes.size(); i++)
        {
            if(almostPrimes[i] > h)
                break;
            else if(almostPrimes[i] >= l)
                sum++;
        }

        cout << sum << endl;
    }

    return 0;
}
