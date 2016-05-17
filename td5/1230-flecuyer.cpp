#include <iostream>
#include <string>

using namespace std;

long exp(long x, const long y, const long n)
{
    if(y == 0) return 1;
    else
    {
        x = x%n;
        long tmp = exp(x, y/2, n);
        tmp = (tmp*tmp)%n;
        if(y%2)
            return (tmp*x)%n;
        else
            return tmp%n;
    }
}

int main()
{
    long x, y, n;
    cin >> x; // number of sets (useless)
    while(cin >> x && x > 0)
    {
        cin >> y >> n;
        cout << exp(x, y, n) << endl;
    }
    return 0;
}
