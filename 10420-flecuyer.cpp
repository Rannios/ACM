#include <iostream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

int main()
{
    int n;
    cin >> n;   cin.ignore();
    map<string, int> countries;
    string country("none");
    string line;

    while(n > 0 && getline(cin, line))
    {
        n--;
        istringstream l(line);
        l >> country;
        countries[country] ++;
    }

    //for(auto& x:countries)
    //    cout << x.first << x.second << endl;
    for(map<string,int>::iterator it=countries.begin();it!=countries.end();++it)
        cout << it->first << " " << it->second << endl;

    return 0;
}
