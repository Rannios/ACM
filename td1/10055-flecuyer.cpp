#include <iostream>
#include <string>

using namespace std;

int main()
{
    long army1(0), army2(0);
    while(cin >> army1 >> army2)
    {
        cout << max(army1 - army2, army2 - army1) << endl;
    }
    return 0;
}
