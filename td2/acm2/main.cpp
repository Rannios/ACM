#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

typedef vector<int> intVect;

bool test_capacity(int c, int n, int m, intVect &vessel)
{
    cout << " capacite " << c <<endl;
    int j=0;
    for(int i=0; i<m; i++)
    {
        int ctmp = 0;
        while(ctmp + vessel[j] <= c) // fill this container with the vessel j
        {
            cout << " vaisselle" << j <<":"<<vessel[j]<<", ctmp:"<<ctmp<<endl;
            ctmp += vessel[j];
            j++;
        }
    }
    cout << (j >= n) << endl;
    return (j >= n); // true if every vessel has a container
}

int main()
{
    int n; // number of vaissels
    int m; // number of containers

    while(cin >> n >> m) // for each case
    {
        intVect vessel(n);
        int minCapacity = 0; // total volume of vessels
        int maxVaissel = 0;

        for(int i=0; i<n; i++) // for each capacity
        {
            cin >> vessel[i];
            minCapacity += vessel[i];
            maxVaissel = max(maxVaissel, vessel[i]);
        }

        if(n <= m) // particular case where there are less vessels than containers
        {
            cout << maxVaissel << endl;
        }

        intVect cursors(m); // positions of cursors
        // initially, the (m-1) first containsers receive each one vessel
        // and the last container receive all the remaining vessels
        for(int i=0; i<m-1; i++) { cursors[i] = i; }
        cursors[m-1] = n-1;

        int lowerBound(0), upperBound(minCapacity);
        int current;

        while(lowerBound != upperBound)
        {
            current = (lowerBound + upperBound) / 2;
            if(test_capacity(current, n, m, vessel))
            {
                lowerBound = current;
            }
            else
            {
                upperBound = current;
            }
        }

        cout << current << endl;
    }

    return 0;
}
